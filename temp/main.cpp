#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*void main() {
	string path = "chando.jpg";
	Mat	img = imread(path);
	imshow("Frame", img);
	waitKey(0);
}*/

int main() {
	// Try different camera indices (0, 1, 2)
	VideoCapture video(0);  // Start with camera 0 (default webcam)
	
	// Check if camera opened successfully
	if (!video.isOpened()) {
		cout << "Error: Could not open camera. Trying camera index 1..." << endl;
		video.open(1);
		if (!video.isOpened()) {
			cout << "Error: Could not open camera. Trying camera index 2..." << endl;
			video.open(2);
			if (!video.isOpened()) {
				cout << "Error: Could not open any camera!" << endl;
				return -1;
			}
		}
	}
	
	CascadeClassifier facedetect;
	Mat img;
	
	// Check if cascade file loads successfully
	if (!facedetect.load("haarcascade_frontalface_default.xml")) {
		cout << "Error: Could not load cascade classifier file!" << endl;
		return -1;
	}
	
	cout << "Face detection started! Press 'q' to quit." << endl;
	
	while (true) {
		video.read(img);
		
		// Check if frame was read successfully
		if (img.empty()) {
			cout << "Error: Could not read frame from camera!" << endl;
			break;
		}

		vector<Rect> faces;
		facedetect.detectMultiScale(img, faces, 1.3, 5);

		cout << "Faces detected: " << faces.size() << endl;

		for (int i = 0; i < faces.size(); i++) {
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
		}
		
		// Draw info box and text
		if (faces.size() > 0) {
			rectangle(img, Point(0,0), Point(250,70), Scalar(50, 50, 255), FILLED);
			putText(img, to_string(faces.size())+" Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
		}
		
		imshow("Face Detection", img);
		
		// Check for 'q' key press to exit
		char key = waitKey(1);
		if (key == 'q' || key == 27) {  // 'q' or ESC key
			cout << "Exiting..." << endl;
			break;
		}
	}
	
	// Clean up
	video.release();
	destroyAllWindows();
	return 0;
}