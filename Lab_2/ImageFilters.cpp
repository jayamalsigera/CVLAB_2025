#include "ImageFilters.h"
#include <iostream>

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

cv::Mat maxFilter(const cv::Mat& input, int kernelSize) {
    return applyFilter(input, kernelSize, true);
}

cv::Mat minFilter(const cv::Mat& input, int kernelSize) {
    return applyFilter(input, kernelSize, false);
}

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

cv::Mat gaussianFilter(const cv::Mat& input, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be an odd number." << std::endl;
        return input.clone();
    }

    cv::Mat output;
    cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), 0);
    return output;
}

void plotHistogram(const cv::Mat& grayscaleImage, int bins) {
    if (grayscaleImage.channels() != 1) {
        std::cerr << "ERROR: Histogram requires a grayscale image." << std::endl;
        return;
    }

    int histSize[] = { bins };
    float range[] = { 0, 256 }; // [0, 256)
    const float* histRange[] = { range };

    cv::Mat hist;
    cv::calcHist(&grayscaleImage, 1, 0, cv::Mat(), hist, 1, histSize, histRange);

    // Normalize for visualization
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / bins);
    cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(255));

    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);

    for (int i = 1; i < bins; i++) {
        cv::line(histImage,
                 cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
                 cv::Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
                 cv::Scalar(0), 2);
    }

    std::string windowName = "Histogram (" + std::to_string(bins) + " bins)";
    cv::imshow(windowName, histImage);
}

cv::Mat equalizeHistogram(const cv::Mat& grayscaleImage) {
    if (grayscaleImage.channels() != 1) {
        std::cerr << "ERROR: Histogram equalization requires a grayscale image." << std::endl;
        return grayscaleImage.clone();
    }

    cv::Mat equalized;
    cv::equalizeHist(grayscaleImage, equalized);
    return equalized;
}
