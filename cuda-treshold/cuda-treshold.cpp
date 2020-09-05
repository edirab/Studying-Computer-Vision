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
	//try
	//{
	//	cv::Mat src_host = cv::imread("file.jpg", cv::IMREAD_GRAYSCALE);
	//	cv::cuda::GpuMat dst, src;
	//	src.upload(src_host);

	//	cv::cuda::threshold(src, dst, 128.0, 255.0, cv::THRESH_BINARY);

	//	cv::Mat result_host;
	//	dst.download(result_host);

	//	cv::imshow("Result", result_host);
	//	cv::waitKey();
	//}
	//catch (const cv::Exception& ex)
	//{
	//	std::cout << "Error: " << ex.what() << std::endl;
	//}

	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	bool stop = false;
	double rate = cap.get(cv::CAP_PROP_FPS);
	int delay = 1000 / rate;

	Mat frame, frame_canny;
	GpuMat gpu_frame, gpu_dst;

	while (!stop) {

		cap.read(frame);
		gpu_frame.upload(frame);
		//cuda::CannyEdgeDetector(gpu_frame, gpu_dst, 35, 200, 3);
		gpu_dst.download(frame_canny);

		imshow("frame", frame);
		imshow("frame Canny", frame_canny);

		// Ждём нажатия на кнопку
		int key = cv::waitKey(delay);
		if (key == 27) // Если это 0x27, т.е. ESC
			stop = true; // Выходим
	}

	return 0;
}

