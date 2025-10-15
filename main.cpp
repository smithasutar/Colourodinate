#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string detectUndertone(const Mat& face) {
    // Convert to YCrCb (better for skin analysis)
    Mat ycrcb;
    cvtColor(face, ycrcb, COLOR_BGR2YCrCb);

    // Compute mean color
    Scalar avg = mean(ycrcb);
    double Y = avg[0], Cr = avg[1], Cb = avg[2];

    cout << "Y: " << Y << "  Cr: " << Cr << "  Cb: " << Cb << endl;

    // Simple rule-based classification
    if (Cr > Cb + 5)
        return "Warm Undertone";
    else if (Cb > Cr + 5)
        return "Cool Undertone";
    else
        return "Neutral Undertone";
}

int main() {
    // Load face cascade
    CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        cout << "Error loading face cascade!" << endl;
        return -1;
    }

    // Read image
    Mat img = imread("test5.jpg");
    if (img.empty()) {
        cout << "Failed to load image!" << endl;
        return -1;
    }

    // Convert to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, gray);

    // Detect faces
    vector<Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 4, 0, Size(100, 100));

    if (faces.empty()) {
        cout << "No face detected!" << endl;
        return 0;
    }

    for (size_t i = 0; i < faces.size(); i++) {
        // Draw rectangle
        rectangle(img, faces[i], Scalar(255, 0, 0), 2);

        // Crop face region
        Mat face = img(faces[i]);

        // Detect undertone
        string tone = detectUndertone(face);

        // Display result on image
        putText(img, tone, Point(faces[i].x, faces[i].y - 10),
                FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0), 2);
    }

    // Show final result
    imshow("Face Detection and Undertone", img);
    waitKey(0);
    return 0;
}
