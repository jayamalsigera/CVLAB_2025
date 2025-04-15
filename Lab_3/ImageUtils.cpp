#include "ImageUtils.h"
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* img = static_cast<cv::Mat*>(userdata);

        if (x >= 0 && x < img->cols && y >= 0 && y < img->rows) {
            cv::Vec3b color = img->at<cv::Vec3b>(y, x);
            std::cout << "Pixel at (" << x << ", " << y << ") - BGR: ["
                      << (int)color[0] << ", "
                      << (int)color[1] << ", "
                      << (int)color[2] << "]" << std::endl;
        }
    }
}


void onMouseMean(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* img = static_cast<cv::Mat*>(userdata);

        if (x >= 0 && x < img->cols && y >= 0 && y < img->rows) {
            int halfSize = 4; // Half of 9 is 4
            int x_start = std::max(x - halfSize, 0);
            int y_start = std::max(y - halfSize, 0);
            int x_end = std::min(x + halfSize + 1, img->cols);
            int y_end = std::min(y + halfSize + 1, img->rows);

            // Define ROI around the clicked point
            cv::Rect roi(x_start, y_start, x_end - x_start, y_end - y_start);
            cv::Mat region = (*img)(roi);

            // Compute mean BGR values
            cv::Scalar mean = cv::mean(region);

            std::cout << "Clicked at (" << x << ", " << y << ") - Mean BGR in 9x9 neighborhood: ["
                      << mean[0] << ", " << mean[1] << ", " << mean[2] << "]" << std::endl;
        }
    }
}

void onMouseSegment(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* img = static_cast<cv::Mat*>(userdata);

        if (x >= 0 && x < img->cols && y >= 0 && y < img->rows) {
            int halfSize = 4;  // 9x9 region around the clicked point
            int x_start = std::max(x - halfSize, 0);
            int y_start = std::max(y - halfSize, 0);
            int x_end = std::min(x + halfSize + 1, img->cols);
            int y_end = std::min(y + halfSize + 1, img->rows);

            cv::Rect roi(x_start, y_start, x_end - x_start, y_end - y_start);
            cv::Mat region = (*img)(roi);

            // Calculate the mean BGR color in the 9x9 region
            cv::Scalar meanBGR = cv::mean(region);

            std::cout << "Clicked at (" << x << ", " << y << ") - Mean BGR in 9x9 neighborhood: ["
                      << meanBGR[0] << ", " << meanBGR[1] << ", " << meanBGR[2] << "]" << std::endl;

            // threshold
            const int T = 60;

            // Create a mask (single channel, black background)
            cv::Mat mask = cv::Mat::zeros(img->size(), CV_8UC1);

            for (int row = 0; row < img->rows; ++row) {
                for (int col = 0; col < img->cols; ++col) {
                    cv::Vec3b pixel = img->at<cv::Vec3b>(row, col);

                    bool isSimilar =
                        std::abs(pixel[0] - meanBGR[0]) <= T &&
                        std::abs(pixel[1] - meanBGR[1]) <= T &&
                        std::abs(pixel[2] - meanBGR[2]) <= T;

                    if (isSimilar) {
                        mask.at<uchar>(row, col) = 255;  // white pixel
                    }
                }
            }

            // Show the mask
            cv::imshow("T-Shirt Mask", mask);
        }
    }
}

void onMouseSegmentHSV(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* img_bgr = static_cast<cv::Mat*>(userdata);

        if (x >= 0 && x < img_bgr->cols && y >= 0 && y < img_bgr->rows) {
            int halfSize = 4;
            int x_start = std::max(x - halfSize, 0);
            int y_start = std::max(y - halfSize, 0);
            int x_end = std::min(x + halfSize + 1, img_bgr->cols);
            int y_end = std::min(y + halfSize + 1, img_bgr->rows);

            // Get 9x9 region in BGR
            cv::Rect roi(x_start, y_start, x_end - x_start, y_end - y_start);
            cv::Mat region_bgr = (*img_bgr)(roi);

            // Convert 9x9 region to HSV
            cv::Mat region_hsv;
            cv::cvtColor(region_bgr, region_hsv, cv::COLOR_BGR2HSV);

            // Compute mean HSV in the region
            cv::Scalar meanHSV = cv::mean(region_hsv);
            std::cout << "Clicked at (" << x << ", " << y << ") - Mean HSV: ["
                      << meanHSV[0] << ", " << meanHSV[1] << ", " << meanHSV[2] << "]" << std::endl;

            // Convert the full image to HSV
            cv::Mat img_hsv;
            cv::cvtColor(*img_bgr, img_hsv, cv::COLOR_BGR2HSV);

            // Define thresholds
            int T_H = 50;  // hue threshold
            int T_S = 60;  // saturation threshold
            int T_V = 70;  // value threshold

            // Create output mask
            cv::Mat mask = cv::Mat::zeros(img_bgr->size(), CV_8UC1);

            for (int row = 0; row < img_hsv.rows; ++row) {
                for (int col = 0; col < img_hsv.cols; ++col) {
                    cv::Vec3b pixel = img_hsv.at<cv::Vec3b>(row, col);

                    int H_diff = std::abs(pixel[0] - meanHSV[0]);
                    int S_diff = std::abs(pixel[1] - meanHSV[1]);
                    int V_diff = std::abs(pixel[2] - meanHSV[2]);

                    // Handle hue wrap-around (e.g., H=0 and H=179 are close)
                    H_diff = std::min(H_diff, 180 - H_diff);

                    if (H_diff <= T_H && S_diff <= T_S && V_diff <= T_V) {
                        mask.at<uchar>(row, col) = 255;
                    }
                }
            }

            // Show the mask
            cv::imshow("HSV T-Shirt Mask", mask);
        }
    }
}

void onMouseChangeColor(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat* img_bgr = static_cast<cv::Mat*>(userdata);

        if (x >= 0 && x < img_bgr->cols && y >= 0 && y < img_bgr->rows) {
            int halfSize = 4;
            int x_start = std::max(x - halfSize, 0);
            int y_start = std::max(y - halfSize, 0);
            int x_end = std::min(x + halfSize + 1, img_bgr->cols);
            int y_end = std::min(y + halfSize + 1, img_bgr->rows);

            // Get 9x9 region in BGR and convert to HSV
            cv::Rect roi(x_start, y_start, x_end - x_start, y_end - y_start);
            cv::Mat region_bgr = (*img_bgr)(roi);
            cv::Mat region_hsv;
            cv::cvtColor(region_bgr, region_hsv, cv::COLOR_BGR2HSV);
            cv::Scalar meanHSV = cv::mean(region_hsv);

            std::cout << "Clicked at (" << x << ", " << y << ") - Mean HSV: ["
                      << meanHSV[0] << ", " << meanHSV[1] << ", " << meanHSV[2] << "]" << std::endl;

            // Convert full image to HSV
            cv::Mat img_hsv;
            cv::cvtColor(*img_bgr, img_hsv, cv::COLOR_BGR2HSV);

            // Thresholds for similarity
            const int T_H = 10;
            const int T_S = 60;
            const int T_V = 80;

            // Create mask
            cv::Mat mask = cv::Mat::zeros(img_bgr->size(), CV_8UC1);
            for (int row = 0; row < img_hsv.rows; ++row) {
                for (int col = 0; col < img_hsv.cols; ++col) {
                    cv::Vec3b hsvPixel = img_hsv.at<cv::Vec3b>(row, col);
                    int hDiff = std::abs(hsvPixel[0] - meanHSV[0]);
                    hDiff = std::min(hDiff, 180 - hDiff); // circular hue
                    int sDiff = std::abs(hsvPixel[1] - meanHSV[1]);
                    int vDiff = std::abs(hsvPixel[2] - meanHSV[2]);

                    if (hDiff <= T_H && sDiff <= T_S && vDiff <= T_V) {
                        mask.at<uchar>(row, col) = 255;
                    }
                }
            }

            // Create recolored image
            cv::Mat recolored = img_bgr->clone();
            cv::Vec3b newColor(92, 37, 201);  // BGR

            for (int row = 0; row < recolored.rows; ++row) {
                for (int col = 0; col < recolored.cols; ++col) {
                    if (mask.at<uchar>(row, col) == 255) {
                        recolored.at<cv::Vec3b>(row, col) = newColor;
                    }
                }
            }

            // Show both the mask and the recolored image
            cv::imshow("HSV T-Shirt Mask", mask);
            cv::imshow("Recolored T-Shirts", recolored);
        }
    }
}