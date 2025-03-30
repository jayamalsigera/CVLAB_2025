#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageFilters.h"

int main(int argc, char** argv)
{
    if(argc < 2){
        std::cerr << "ERROR: Provide path to image file" << std::endl;
        return 1;
    }

    cv::Mat img = cv::imread(argv[1]);

    if(img.empty()){
        std::cerr << "ERROR: Image cannot be loaded. Check file path." << std::endl;
        return 1;
    }

    int kernelSize;
    std::cout << "Enter kernel size (odd number): ";
    std::cin >> kernelSize;

    cv::Mat maxFiltered = maxFilter(img, kernelSize);
    cv::Mat minFiltered = minFilter(img, kernelSize);
    cv::Mat medianFiltered = medianFilter(img, kernelSize);
    cv::Mat gaussianFiltered = gaussianFilter(img, kernelSize);

    cv::imshow("Original", img);
    cv::imshow("Max Filtered", maxFiltered);
    cv::imshow("Min Filtered", minFiltered);
    cv::imshow("Median Filtered", medianFiltered);
    cv::imshow("Gaussian Filtered", gaussianFiltered);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
