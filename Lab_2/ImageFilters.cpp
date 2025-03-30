#include "ImageFilters.h"
#include <iostream>
    
// Common function to apply either max or min filter
cv::Mat applyFilter(const cv::Mat& input, int kernelSize, bool isMax)
{
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be an odd number." << std::endl;
        return input.clone();
    }

    cv::Mat output = input.clone();
    int radius = kernelSize / 2;

    for (int y = radius; y < input.rows - radius; ++y) {
        for (int x = radius; x < input.cols - radius; ++x) {
            for (int c = 0; c < input.channels(); ++c) {
                uchar extremeVal = isMax ? 0 : 255;
                for (int ky = -radius; ky <= radius; ++ky) {
                    for (int kx = -radius; kx <= radius; ++kx) {
                        uchar val = input.at<cv::Vec3b>(y + ky, x + kx)[c];
                        if (isMax)
                            extremeVal = std::max(extremeVal, val);
                        else
                            extremeVal = std::min(extremeVal, val);
                    }
                }
                output.at<cv::Vec3b>(y, x)[c] = extremeVal;
            }
        }
    }
    return output;
}

// Max filter using applyFilter
cv::Mat maxFilter(const cv::Mat& input, int kernelSize) {
    return applyFilter(input, kernelSize, true);
}

// Min filter using applyFilter
cv::Mat minFilter(const cv::Mat& input, int kernelSize) {
    return applyFilter(input, kernelSize, false);
}

// Median filter implementation
cv::Mat medianFilter(const cv::Mat& input, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be an odd number." << std::endl;
        return input.clone();
    }

    cv::Mat output = input.clone();
    int radius = kernelSize / 2;

    for (int y = radius; y < input.rows - radius; ++y) {
        for (int x = radius; x < input.cols - radius; ++x) {
            for (int c = 0; c < input.channels(); ++c) {
                std::vector<uchar> neighborhood;
                for (int ky = -radius; ky <= radius; ++ky) {
                    for (int kx = -radius; kx <= radius; ++kx) {
                        neighborhood.push_back(input.at<cv::Vec3b>(y + ky, x + kx)[c]);
                    }
                }
                std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size()/2, neighborhood.end());
                output.at<cv::Vec3b>(y, x)[c] = neighborhood[neighborhood.size()/2];
            }
        }
    }
    return output;
}

// Gaussian blur using OpenCV
cv::Mat gaussianFilter(const cv::Mat& input, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be an odd number." << std::endl;
        return input.clone();
    }

    cv::Mat output;
    cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), 0);
    return output;
}

// Plot grayscale histogram
void plotHistogram(const cv::Mat& grayImg, int bins, const std::string& windowName) {
    int histSize[] = { bins };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };

    cv::Mat hist;
    cv::calcHist(&grayImg, 1, 0, cv::Mat(), hist, 1, histSize, ranges);

    int hist_w = 512; 
    int hist_h = 300; 
    int bin_w = cvRound((double) hist_w / bins);

    cv::Mat histImage(hist_h + 40, hist_w + 60, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::normalize(hist, hist, 0, hist_h, cv::NORM_MINMAX);

    int offsetX = 30, offsetY = 20;

    cv::line(histImage, {offsetX, offsetY}, {offsetX, hist_h + offsetY}, cv::Scalar(0, 0, 0), 1);
    cv::line(histImage, {offsetX, hist_h + offsetY}, {hist_w + offsetX, hist_h + offsetY}, cv::Scalar(0, 0, 0), 1);

    for (int i = 1; i < bins; i++) {
        cv::line(histImage,
            {offsetX + bin_w * (i - 1), hist_h + offsetY - cvRound(hist.at<float>(i - 1))},
            {offsetX + bin_w * i, hist_h + offsetY - cvRound(hist.at<float>(i))},
            cv::Scalar(0, 0, 255), 2);
    }

    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, histImage);
}

