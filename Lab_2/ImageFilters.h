#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/opencv.hpp>

cv::Mat maxFilter(const cv::Mat& input, int kernelSize);
cv::Mat minFilter(const cv::Mat& input, int kernelSize);
cv::Mat medianFilter(const cv::Mat& input, int kernelSize);
cv::Mat gaussianFilter(const cv::Mat& input, int kernelSize);
void plotHistogram(const cv::Mat& grayscaleImage, int bins);
cv::Mat equalizeHistogram(const cv::Mat& grayscaleImage);

#endif
