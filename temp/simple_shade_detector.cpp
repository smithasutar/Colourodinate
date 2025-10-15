#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main() {
    // Load face cascade
    CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        cout << "Error: Could not load face cascade!" << endl;
        return -1;
    }
    
    // Initialize camera
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera!" << endl;
        return -1;
    }
    
    cout << "Simple Face Shade Detector Started!" << endl;
    cout << "Press 'q' to quit" << endl;
    
    Mat frame;
    
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        
        // Convert to grayscale for face detection
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);
        
        // Detect faces
        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.3, 5);
        
        for (size_t i = 0; i < faces.size(); i++) {
            // Draw face rectangle
            rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
            
            // Analyze skin tone in face region
            Mat face_roi = frame(faces[i]);
            Scalar avg_color = mean(face_roi);
            
            // Simple shade classification based on brightness
            string shade_name;
            string undertone;
            
            double brightness = (avg_color[0] + avg_color[1] + avg_color[2]) / 3.0;
            double red_green_ratio = avg_color[2] / (avg_color[1] + 1);
            
            // Determine undertone
            if (red_green_ratio > 1.1) {
                undertone = "Warm";
            } else if (red_green_ratio < 0.9) {
                undertone = "Cool";
            } else {
                undertone = "Neutral";
            }
            
            // Determine shade based on brightness
            if (brightness > 200) {
                shade_name = "Fair";
            } else if (brightness > 180) {
                shade_name = "Light";
            } else if (brightness > 160) {
                shade_name = "Light Medium";
            } else if (brightness > 140) {
                shade_name = "Medium";
            } else if (brightness > 120) {
                shade_name = "Medium Deep";
            } else if (brightness > 100) {
                shade_name = "Deep";
            } else {
                shade_name = "Very Deep";
            }
            
            // Display shade information
            string info = shade_name + " (" + undertone + ")";
            Point text_pos(faces[i].x, faces[i].y - 10);
            if (text_pos.y < 0) text_pos.y = faces[i].y + faces[i].height + 20;
            
            // Background rectangle
            rectangle(frame, text_pos, Point(text_pos.x + 200, text_pos.y + 30), 
                     Scalar(50, 50, 50), FILLED);
            
            // Shade text
            putText(frame, info, Point(text_pos.x + 5, text_pos.y + 20), 
                    FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);
            
            // Color swatch
            rectangle(frame, Point(text_pos.x + 150, text_pos.y + 5), 
                     Point(text_pos.x + 190, text_pos.y + 25), avg_color, FILLED);
        }
        
        // Display face count
        string face_count = "Faces: " + to_string(faces.size());
        putText(frame, face_count, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        
        // Show frame
        imshow("Simple Shade Detector", frame);
        
        // Check for exit
        char key = waitKey(1);
        if (key == 'q' || key == 27) {
            cout << "Exiting..." << endl;
            break;
        }
    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}
