#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "CannyUtils.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "ERROR: Provide path to image file" << std::endl;
        return 1;
    }

    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "ERROR: Unable to load image." << std::endl;
        return 1;
    }

    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original", img);

    // Initialize Canny edge detection UI and logic
    // initializeCanny(img);
    // detectRoadSign(img);

    cv::Mat hsv, mask;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // HSV thresholds for light blue sky
    cv::inRange(hsv, cv::Scalar(90, 30, 150), cv::Scalar(140, 160, 255), mask);

    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1, -1), 1);
    cv::morphologyEx(mask, mask, cv::MORPH_DILATE, cv::Mat(), cv::Point(-1, -1), 1);

    cv::imshow("Sky Mask - HSV Thresholding", mask);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
