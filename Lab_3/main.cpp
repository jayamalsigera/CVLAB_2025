
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageUtils.h"

int main(int argc, char** argv)
{
    // Check if image path is provided
    if (argc < 2) {
        std::cerr << "ERROR: Provide path to image file" << std::endl;
        return 1;
    }

    // Read the image
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "ERROR: Unable to load image. Check file path/name." << std::endl;
        return 1;
    }

    // Create a window and set the mouse callback
    cv::namedWindow("Image");
    // cv::setMouseCallback("Image", onMouse, &img);
    // cv::setMouseCallback("Image", onMouseMean, &img);
    // cv::setMouseCallback("Image", onMouseSegment, &img);
    // cv::setMouseCallback("Image", onMouseSegmentHSV, &img);
    cv::setMouseCallback("Image", onMouseChangeColor, &img);

    // Show the image
    cv::imshow("Image", img);

    // Wait for user to press a key
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}