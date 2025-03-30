#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageFilters.h" // Assuming plotHistogram() is defined there

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "ERROR: Provide path to img file" << std::endl;
        return 1;
    }

    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "ERROR: Check file path/name" << std::endl;
        return 1;
    }

    cv::imshow("Original Image", img);
    cv::waitKey(0);

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Grayscale Image", gray);
    cv::imwrite("Garden_grayscale.jpg", gray);
    cv::waitKey(0);

    // Equalize
    cv::Mat equalized;
    cv::equalizeHist(gray, equalized);
    cv::imshow("Equalized Image", equalized);
    cv::imwrite("Garden_equalized.jpg", equalized);
    cv::waitKey(0);

    // Show histograms with different bin sizes
    plotHistogram(equalized, 16, "Equalized Histogram - 16 bins");
    plotHistogram(equalized, 64, "Equalized Histogram - 64 bins");
    plotHistogram(equalized, 256, "Equalized Histogram - 256 bins");

    // Wait for a key press
	cv::waitKey(0);
	// Close all OpenCV windows
	cv::destroyAllWindows();
    
    return 0;
}