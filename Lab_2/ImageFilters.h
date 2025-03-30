#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>

cv::Mat applyFilter(const cv::Mat& input, int kernelSize, bool isMax);

// max filter
cv::Mat maxFilter(const cv::Mat& input, int kernelSize);

// min filter
cv::Mat minFilter(const cv::Mat& input, int kernelSize);

// median filter
cv::Mat medianFilter(const cv::Mat& input, int kernelSize);

// Gaussian blur
cv::Mat gaussianFilter(const cv::Mat& input, int kernelSize);

// histogram of a grayscale image
void plotHistogram(const cv::Mat& grayImg, int bins, const std::string& windowName);

// histogram equalization 
cv::Mat equalizeHistogram(const cv::Mat& grayscaleImage);

#endif
