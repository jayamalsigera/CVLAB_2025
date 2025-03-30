#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageFilters.h"


int main(int argc, char** argv)
{
	// Check if image path is provided
	if(argc < 2){
		std::cerr << "ERROR: Provide path to img file" << std::endl;
		return 1;
	}
	
	// Read the image from the given file path
	cv::Mat img = cv::imread(argv[1]);
	
	// Check if image was loaded successfully
	if(img.empty()){
		std::cerr << "ERROR: Check file path/name" << std::endl;
		return 1;
	}

    // Get the kernel size from the user (should be an odd number)
    int kernelSize;
    std::cout << "Enter kernel size (odd number): ";
    std::cin >> kernelSize;

    // Apply max and min filters using the given kernel size
    cv::Mat maxFiltered = maxFilter(img, kernelSize);
    cv::Mat minFiltered = minFilter(img, kernelSize);
    // Apply median filter using the given kernel size
    cv::Mat medianFiltered = medianFilter(img, kernelSize);
    // Apply gaussian filter using the given kernel size
    cv::Mat gaussianFiltered = gaussianFilter(img, kernelSize);

    // Display the original and filtered images in separate windows
    cv::imshow("Original", img);
    cv::imshow("Max Filtered", maxFiltered);
    cv::imshow("Min Filtered", minFiltered);
    cv::imshow("Median Filtered", medianFiltered);
    cv::imshow("Gaussian Filtered", gaussianFiltered);

    // Wait for a key press
	cv::waitKey(0);
	// Close all OpenCV windows
	cv::destroyAllWindows();

    return 0;
}