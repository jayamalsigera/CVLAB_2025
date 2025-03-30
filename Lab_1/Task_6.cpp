#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat maxFilter(const cv::Mat& input, int kernelSize)
cv::Mat minFilter(const cv::Mat& input, int kernelSize)

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./filter_demo <image_path>\n";
        return 1;
    }

    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "ERROR: Could not load image.\n";
        return 1;
    }

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Averaging filter
    cv::Mat avgFiltered;
    cv::blur(gray, avgFiltered, cv::Size(5, 5));

    // Sobel filter
    cv::Mat sobelX, sobelY, sobelFiltered;
    cv::Sobel(gray, sobelX, CV_16S, 1, 0, 3);
    cv::Sobel(gray, sobelY, CV_16S, 0, 1, 3);
    cv::Mat absX, absY;
    cv::convertScaleAbs(sobelX, absX);
    cv::convertScaleAbs(sobelY, absY);
    cv::addWeighted(absX, 0.5, absY, 0.5, 0, sobelFiltered);

    // Max and Min filters
    int kernelSize = 3;
    cv::Mat maxFiltered = maxFilter(gray, kernelSize);
    cv::Mat minFiltered = minFilter(gray, kernelSize);

    // Display all
    cv::imshow("Original", img);
    cv::imshow("Grayscale", gray);
    cv::imshow("Averaging Filter", avgFiltered);
    cv::imshow("Sobel Filter", sobelFiltered);
    cv::imshow("Max Filter", maxFiltered);
    cv::imshow("Min Filter", minFiltered);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

// Custom max filter
cv::Mat maxFilter(const cv::Mat& input, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be odd.\n";
        return input.clone();
    }

    cv::Mat output = input.clone();
    int radius = kernelSize / 2;

    for (int y = radius; y < input.rows - radius; ++y) {
        for (int x = radius; x < input.cols - radius; ++x) {
            uchar maxVal = 0;
            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    maxVal = std::max(maxVal, input.at<uchar>(y + ky, x + kx));
                }
            }
            output.at<uchar>(y, x) = maxVal;
        }
    }
    return output;
}

// Custom min filter
cv::Mat minFilter(const cv::Mat& input, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "ERROR: Kernel size must be odd.\n";
        return input.clone();
    }

    cv::Mat output = input.clone();
    int radius = kernelSize / 2;

    for (int y = radius; y < input.rows - radius; ++y) {
        for (int x = radius; x < input.cols - radius; ++x) {
            uchar minVal = 255;
            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    minVal = std::min(minVal, input.at<uchar>(y + ky, x + kx));
                }
            }
            output.at<uchar>(y, x) = minVal;
        }
    }
    return output;
}