#include "CannyUtils.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

cv::Mat img_original, gray, edges;
int lowerThresh = 500;
int upperThresh = 850;
int houghThresh = 80;

bool computeIntersection(const cv::Point2f& a1, const cv::Point2f& a2,
    const cv::Point2f& b1, const cv::Point2f& b2,
    cv::Point2f& intersection)
{
float d = (a1.x - a2.x) * (b1.y - b2.y) - (a1.y - a2.y) * (b1.x - b2.x);
if (std::abs(d) < 1e-6) return false;

float px = ((a1.x * a2.y - a1.y * a2.x) * (b1.x - b2.x) -
(a1.x - a2.x) * (b1.x * b2.y - b1.y * b2.x)) / d;

float py = ((a1.x * a2.y - a1.y * a2.x) * (b1.y - b2.y) -
(a1.y - a2.y) * (b1.x * b2.y - b1.y * b2.x)) / d;

intersection = cv::Point2f(px, py);
return true;
}


// Function to apply Hough Transform and draw on the original image
void applyHoughLines(const cv::Mat& edgeImage, const cv::Mat& original)
{
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edgeImage, lines, 1, CV_PI / 180, houghThresh);  // Controlled by trackbar

    cv::Mat output = original.clone();
    cv::Point2f pts[4];

    if (lines.size() >= 2) {
        for (int i = 0; i < 2; ++i) {
            float rho = lines[i][0];
            float theta = lines[i][1];

            double a = std::cos(theta), b = std::sin(theta);
            double x0 = a * rho, y0 = b * rho;
            cv::Point pt1, pt2;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            // cv::line(output, pt1, pt2, cv::Scalar(0, 0, 255), 1);

            pts[i * 2]     = pt2;  // bottom
            pts[i * 2 + 1] = pt1;  // top
        }

    }

    cv::Point2f intersection;
    if (computeIntersection(pts[0], pts[1], pts[2], pts[3], intersection)) {
        // Replace top points with the intersection point
        pts[1] = intersection;
        pts[2] = intersection;

        // Fill triangle
        std::vector<cv::Point> polygon = {
            cv::Point(pts[0]),  // bottom left
            cv::Point(pts[3]),  // bottom right
            cv::Point(intersection)  // top point
        };
        cv::fillConvexPoly(output, polygon, cv::Scalar(0, 0, 255), cv::LINE_AA);
    }

    // Show both outputs
    cv::imshow("Canny Edge", edges);
    cv::imshow("Hough Overlay", output);
    
}

void onTrackbarChange(int, void*)
{
    cv::Canny(gray, edges, lowerThresh, upperThresh);
    applyHoughLines(edges, img_original);
}

void initializeCanny(const cv::Mat& input)
{
    img_original = input.clone();
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original", input);

    cv::namedWindow("Canny Edge", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Hough Overlay", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("Lower Threshold", "Canny Edge", &lowerThresh, 1500, onTrackbarChange);
    cv::createTrackbar("Upper Threshold", "Canny Edge", &upperThresh, 1500, onTrackbarChange);
    cv::createTrackbar("Hough Threshold", "Hough Overlay", &houghThresh, 1200, onTrackbarChange);

    onTrackbarChange(0, 0);
}


void detectRoadSign(const cv::Mat& input)
{
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(
        gray, circles, cv::HOUGH_GRADIENT,
        1,               // dp = 1 (accumulator res = input res)
        gray.rows / 8,   // minDist between circles
        1000,            // param1 = Canny upper threshold
        10,              // param2 = center detection threshold
        1, 500           // min and max radius in pixels
    );

    cv::Mat output = input.clone();
    for (const auto& c : circles) {
        cv::Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);

        // Draw circle center
        cv::circle(output, center, 2, cv::Scalar(0, 255, 0), radius);
        // Draw circle outline
        cv::circle(output, center, radius, cv::Scalar(0, 0, 255), 1);
    }

    cv::imshow("Detected Road Sign", output);

}
