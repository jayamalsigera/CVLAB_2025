#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

cv::Mat checkImg (cv::Mat img)

int main(int argc, char** argv)
{
	
	if(argc<2){
		std::cerr << "ERROR: Provide path to img file" << std::endl;
		return 1;
	}
	
	cv::Mat img = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
	
	if(img.empty()){
		std::cerr << "ERROR: Check file path/name" << std::endl;
		return 1;
		
	}
	
	cv::Mat checkImg (cv::Mat img)
	
	std::cout << "Number of Channels: " << img.channels() << std::endl;
	
	cv::namedWindow("Lab_1_T1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Lab_1_T1", img);	
	cv::waitKey(0);
	
	char wKey = cv::waitKey(0);
	std::cout << wKey << std::endl;
	
	return 0;

}

cv::Mat checkImg(cv::Mat img) {
    if (img.channels() == 3) {
        std::vector<cv::Mat> channels(3);
        cv::split(img, channels);
        
        // Set the first channel (Blue) to zero
        channels[0] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
        
        cv::merge(channels, img);
        std::cout << "Blue channel set to 0. Missing color: Blue.\n";
    } else {
        std::cout << "The image does not have 3 channels. No modifications applied.\n";
    }
    return img;
}
