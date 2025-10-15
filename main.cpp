#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "OpenCV test running..." << std::endl;
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty()) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }
    cv::imshow("Test", img);
    cv::waitKey(0);
    return 0;
}
