#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// Function to check and extract individual channels if the image has 3 channels
void checkAndShowChannels(const cv::Mat& img);

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "ERROR: Provide path to image file\n";
        return 1;
    }

    // Load image in unchanged format (preserves channels)
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_UNCHANGED);

    if (img.empty()) {
        std::cerr << "ERROR: Could not load image. Check path or file name.\n";
        return 1;
    }

    std::cout << "Number of Channels: " << img.channels() << std::endl;

    cv::imshow("Original Image", img);

    // Call the function to check and show channels if 3-channel image
    checkAndShowChannels(img);

    // Wait for key press before closing
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

void checkAndShowChannels(const cv::Mat& img) {
    if (img.channels() == 3) {
        std::vector<cv::Mat> channels(3);
        cv::split(img, channels); // Split into B, G, R

        // Display each channel as a grayscale image
        cv::imshow("Blue Channel", channels[0]);
        cv::imshow("Green Channel", channels[1]);
        cv::imshow("Red Channel", channels[2]);

        std::cout << "Three channels extracted and displayed separately (B, G, R).\n";
    } else {
        std::cout << "The image does not have 3 channels. No channels to split.\n";
    }
}