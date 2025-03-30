#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

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
	
	std::cout << "Number of Channels: " << img.channels() << std::endl;
	
	cv::namedWindow("Lab_1_T1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Lab_1_T1", img);	
	cv::waitKey(0);
	
	int wKey = cv::waitKey(0);
	std::cout << wKey << std::endl;

	cv::destroyAllWindows();
	
	return 0;

}
