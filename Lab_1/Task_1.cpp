#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	
	if(argc<2){
		std::cerr << "ERROR: Provide path to img file" << std::endl;
		return 1;
	}
	
	cv::Mat img = cv::imread(argv[1]);
	
	if(img.empty()){
		std::cerr << "ERROR: Check file path/name" << std::endl;
		return 1;
		
	}
	
	cv::namedWindow("Lab_1_T1");
	cv::imshow("Lab_1_T1", img);
	cv::waitKey(0);
	
	cv::destroyAllWindows();

	return 0;

}
