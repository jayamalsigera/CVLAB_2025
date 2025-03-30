#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main() {
    // Create 256x256 grayscale images
    cv::Mat verticalGradient(256, 256, CV_8UC1);
    cv::Mat horizontalGradient(256, 256, CV_8UC1);

    // Fill vertical gradient (increasing top to bottom)
    for (int y = 0; y < verticalGradient.rows; y++) {
        uchar value = static_cast<uchar>(y);
        for (int x = 0; x < verticalGradient.cols; x++) {
            verticalGradient.at<uchar>(y, x) = value;
        }
    }

    // Fill horizontal gradient (increasing left to right)
    for (int y = 0; y < horizontalGradient.rows; y++) {
        for (int x = 0; x < horizontalGradient.cols; x++) {
            uchar value = static_cast<uchar>(x);
            horizontalGradient.at<uchar>(y, x) = value;
        }
    }

    // Create 300x300 grayscale images for chessboards
    cv::Mat chessboard20(300, 300, CV_8UC1, cv::Scalar(0));
    cv::Mat chessboard50(300, 300, CV_8UC1, cv::Scalar(0));

    // Fill chessboard with 20px squares
    int squareSize20 = 20;
    for (int y = 0; y < 300; y++) {
        for (int x = 0; x < 300; x++) {
            int squareY = y / squareSize20;
            int squareX = x / squareSize20;
            if ((squareX + squareY) % 2 == 0) {
                chessboard20.at<uchar>(y, x) = 255;
            }
        }
    }

    // Fill chessboard with 50px squares
    int squareSize50 = 50;
    for (int y = 0; y < 300; y++) {
        for (int x = 0; x < 300; x++) {
            int squareY = y / squareSize50;
            int squareX = x / squareSize50;
            if ((squareX + squareY) % 2 == 0) {
                chessboard50.at<uchar>(y, x) = 255;
            }
        }
    }

    // Show all images
    cv::imshow("Vertical Gradient", verticalGradient);
    cv::imshow("Horizontal Gradient", horizontalGradient);
    cv::imshow("Chessboard 20px", chessboard20);
    cv::imshow("Chessboard 50px", chessboard50);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
