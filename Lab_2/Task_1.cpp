#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	// Check if image path is provided
	if(argc < 2){
		std::cerr << "ERROR: Provide path to img file" << std::endl;
		return 1;
	}
	
	// Read the image from the given file path
	cv::Mat img = cv::imread(argv[1]);
	
	// Check if image was loaded successfully
	if(img.empty()){
		std::cerr << "ERROR: Check file path/name" << std::endl;
		return 1;
	}
	
	// Display the original image in a window
	cv::namedWindow("Original");
	cv::imshow("LOriginal", img);
	cv::waitKey(0);
	
	// Convert the image to grayscale
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	
	// Show the grayscale image in a separate window
	cv::namedWindow("Grayscale_Image");
	cv::imshow("Grayscale_Image", gray);

	// Save the grayscale image to a file
	cv::imwrite("Garden_grayscale.jpg", gray);

    // Wait for a key press
	cv::waitKey(0);
	// Close all OpenCV windows
	cv::destroyAllWindows();

	return 0;
}
