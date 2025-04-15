#ifndef CANNY_UTILS_H
#define CANNY_UTILS_H

#include <opencv2/core.hpp>

// Declaration of the onTrackbarChange function
void onTrackbarChange(int, void*);

// Declaration of initialization function
void initializeCanny(const cv::Mat& input);

void applyHoughLines(const cv::Mat& edgeImage, const cv::Mat& original);

void detectRoadSign(const cv::Mat& input);

#endif // CANNY_UTILS_H
