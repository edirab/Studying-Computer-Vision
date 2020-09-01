// cuda-test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
//#include "opencv2/core/cuda/common.hpp"

using namespace std;
using namespace cv;
using namespace cv::cuda;

int main(int argc, char* argv[])
{
	try
	{
		cv::Mat src_host = cv::imread("file.jpg", cv::IMREAD_GRAYSCALE);
		cv::cuda::GpuMat dst, src;
		src.upload(src_host);

		cv::cuda::threshold(src, dst, 128.0, 255.0, cv::THRESH_BINARY);

		cv::Mat result_host;
		dst.download(result_host);

		cv::imshow("Result", result_host);
		cv::waitKey();
	}
	catch (const cv::Exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}
	return 0;
}

