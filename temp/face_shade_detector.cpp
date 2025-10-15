#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace cv;

// Shade categories based on Fitzpatrick scale and common foundation shades
struct ShadeInfo {
    string name;
    string undertone;
    string description;
    Scalar color;
    int fitzpatrick_scale;
};

class FaceShadeDetector {
private:
    CascadeClassifier face_cascade;
    vector<ShadeInfo> shade_database;
    
public:
    FaceShadeDetector() {
        initializeShadeDatabase();
    }
    
    void initializeShadeDatabase() {
        // Initialize shade database with common foundation shades
        shade_database = {
            {"Fair Light", "Cool", "Very fair with pink undertones", Scalar(255, 220, 200), 1},
            {"Fair", "Neutral", "Fair with neutral undertones", Scalar(255, 210, 190), 1},
            {"Fair Medium", "Warm", "Fair with yellow undertones", Scalar(250, 200, 170), 2},
            {"Light", "Cool", "Light with pink undertones", Scalar(240, 190, 160), 2},
            {"Light", "Neutral", "Light with neutral undertones", Scalar(235, 185, 155), 2},
            {"Light", "Warm", "Light with yellow undertones", Scalar(230, 180, 150), 2},
            {"Light Medium", "Cool", "Light medium with pink undertones", Scalar(220, 170, 140), 3},
            {"Light Medium", "Neutral", "Light medium with neutral undertones", Scalar(215, 165, 135), 3},
            {"Light Medium", "Warm", "Light medium with yellow undertones", Scalar(210, 160, 130), 3},
            {"Medium", "Cool", "Medium with pink undertones", Scalar(200, 150, 120), 3},
            {"Medium", "Neutral", "Medium with neutral undertones", Scalar(195, 145, 115), 3},
            {"Medium", "Warm", "Medium with yellow undertones", Scalar(190, 140, 110), 3},
            {"Medium Deep", "Cool", "Medium deep with pink undertones", Scalar(180, 130, 100), 4},
            {"Medium Deep", "Neutral", "Medium deep with neutral undertones", Scalar(175, 125, 95), 4},
            {"Medium Deep", "Warm", "Medium deep with yellow undertones", Scalar(170, 120, 90), 4},
            {"Deep", "Cool", "Deep with pink undertones", Scalar(160, 110, 80), 5},
            {"Deep", "Neutral", "Deep with neutral undertones", Scalar(155, 105, 75), 5},
            {"Deep", "Warm", "Deep with yellow undertones", Scalar(150, 100, 70), 5},
            {"Very Deep", "Cool", "Very deep with pink undertones", Scalar(140, 90, 60), 6},
            {"Very Deep", "Neutral", "Very deep with neutral undertones", Scalar(135, 85, 55), 6},
            {"Very Deep", "Warm", "Very deep with yellow undertones", Scalar(130, 80, 50), 6}
        };
    }
    
    bool loadCascade() {
        return face_cascade.load("haarcascade_frontalface_default.xml");
    }
    
    // Analyze skin tone from face region
    ShadeInfo analyzeSkinTone(const Mat& face_roi) {
        // Convert to different color spaces for better analysis
        Mat hsv, lab, yuv;
        cvtColor(face_roi, hsv, COLOR_BGR2HSV);
        cvtColor(face_roi, lab, COLOR_BGR2Lab);
        cvtColor(face_roi, yuv, COLOR_BGR2YUV);
        
        // Calculate average color in different regions
        Rect center_region(face_roi.cols/4, face_roi.rows/4, face_roi.cols/2, face_roi.rows/2);
        Mat center_face = face_roi(center_region);
        
        // Get average BGR values
        Scalar avg_color = mean(center_face);
        Vec3b avg_bgr(avg_color[0], avg_color[1], avg_color[2]);
        
        // Calculate skin tone characteristics
        double brightness = (avg_bgr[0] + avg_bgr[1] + avg_bgr[2]) / 3.0;
        double red_green_ratio = avg_bgr[2] / (avg_bgr[1] + 1); // Avoid division by zero
        double blue_ratio = avg_bgr[0] / (avg_bgr[2] + 1);
        
        // Determine undertone
        string undertone = determineUndertone(avg_bgr, red_green_ratio, blue_ratio);
        
        // Find closest shade match
        ShadeInfo best_match = findClosestShade(avg_bgr, brightness, undertone);
        
        return best_match;
    }
    
    string determineUndertone(const Vec3b& avg_color, double red_green_ratio, double blue_ratio) {
        // Analyze undertone based on color ratios
        if (red_green_ratio > 1.1 && blue_ratio < 0.8) {
            return "Warm"; // Yellow/olive undertones
        } else if (red_green_ratio < 0.9 && blue_ratio > 0.9) {
            return "Cool"; // Pink/red undertones
        } else {
            return "Neutral"; // Balanced undertones
        }
    }
    
    ShadeInfo findClosestShade(const Vec3b& skin_color, double brightness, const string& undertone) {
        double min_distance = DBL_MAX;
        ShadeInfo best_match = shade_database[0];
        
        for (const auto& shade : shade_database) {
            // Filter by undertone first
            if (shade.undertone != undertone) continue;
            
            // Calculate color distance
            double distance = calculateColorDistance(skin_color, shade.color);
            
            if (distance < min_distance) {
                min_distance = distance;
                best_match = shade;
            }
        }
        
        return best_match;
    }
    
    double calculateColorDistance(const Vec3b& color1, const Scalar& color2) {
        // Calculate Euclidean distance in RGB space
        double b_diff = color1[0] - color2[0];
        double g_diff = color1[1] - color2[1];
        double r_diff = color1[2] - color2[2];
        
        return sqrt(b_diff*b_diff + g_diff*g_diff + r_diff*r_diff);
    }
    
    void drawShadeInfo(Mat& img, const ShadeInfo& shade, const Rect& face_rect) {
        // Create info box
        Point info_pos(face_rect.x, face_rect.y - 10);
        if (info_pos.y < 0) info_pos.y = face_rect.y + face_rect.height + 20;
        
        // Background rectangle
        rectangle(img, info_pos, Point(info_pos.x + 300, info_pos.y + 80), 
                 Scalar(50, 50, 50), FILLED);
        
        // Shade name
        putText(img, "Shade: " + shade.name, 
                Point(info_pos.x + 10, info_pos.y + 20), 
                FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
        
        // Undertone
        putText(img, "Undertone: " + shade.undertone, 
                Point(info_pos.x + 10, info_pos.y + 40), 
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(200, 200, 200), 1);
        
        // Description
        putText(img, shade.description, 
                Point(info_pos.x + 10, info_pos.y + 60), 
                FONT_HERSHEY_SIMPLEX, 0.4, Scalar(180, 180, 180), 1);
        
        // Color swatch
        rectangle(img, Point(info_pos.x + 250, info_pos.y + 10), 
                 Point(info_pos.x + 290, info_pos.y + 50), shade.color, FILLED);
        rectangle(img, Point(info_pos.x + 250, info_pos.y + 10), 
                 Point(info_pos.x + 290, info_pos.y + 50), Scalar(255, 255, 255), 2);
    }
    
    void processFrame(Mat& img) {
        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);
        
        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.3, 5);
        
        for (size_t i = 0; i < faces.size(); i++) {
            // Draw face rectangle
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 2);
            
            // Extract face region for analysis
            Mat face_roi = img(faces[i]);
            
            // Analyze skin tone
            ShadeInfo detected_shade = analyzeSkinTone(face_roi);
            
            // Draw shade information
            drawShadeInfo(img, detected_shade, faces[i]);
        }
        
        // Draw face count
        string face_count = "Faces detected: " + to_string(faces.size());
        putText(img, face_count, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    }
};

int main() {
    FaceShadeDetector detector;
    
    // Load face cascade
    if (!detector.loadCascade()) {
        cout << "Error: Could not load face cascade classifier!" << endl;
        return -1;
    }
    
    // Initialize camera
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera!" << endl;
        return -1;
    }
    
    cout << "Face Shade Detector Started!" << endl;
    cout << "Press 'q' to quit, 's' to save current frame" << endl;
    
    Mat frame;
    int frame_count = 0;
    
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        
        // Process frame for shade detection
        detector.processFrame(frame);
        
        // Display frame
        imshow("Face Shade Detector", frame);
        
        char key = waitKey(1);
        if (key == 'q' || key == 27) {
            cout << "Exiting..." << endl;
            break;
        } else if (key == 's') {
            string filename = "shade_detection_" + to_string(frame_count++) + ".jpg";
            imwrite(filename, frame);
            cout << "Frame saved as: " << filename << endl;
        }
    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}
