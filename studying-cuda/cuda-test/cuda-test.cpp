/* cuda-test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

	Example:	https://gist.github.com/codebudo/d55f1d61f5d299e71f8f96145907805d

	Параметры подопытного видео:
	- FullHD
	- 30 fps
	- 31 sec
*/

//#define __CUDACC_VER_MAJOR__ 11
//#define __CUDACC__

//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"

#include <iostream>
#include <chrono>

#include <opencv2/opencv.hpp>

#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>

#include <opencv2/cudawarping.hpp>
//#include <opencv2/cudev/expr/deriv.hpp>

using namespace std;
//using namespace cv;
using cv::Mat;
using cv::VideoCapture;
using namespace cv::cuda;

#if defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
|| defined(WIN64)    || defined(_WIN64) || defined(__WIN64__) 
	#define VIDEO_PATH "E:/University/studying-computer-vision/studying-cuda/cuda-test/with.mp4"
#else
	#define VIDEO_PATH "./with.mp4"
#endif




void test_1() {

	Mat h_array1 = Mat::ones(1024, 1024, CV_32FC2);
	Mat h_array2 = Mat::ones(1024, 1024, CV_32FC2);
	Mat h_array3 = Mat::zeros(1024, 1024, CV_32FC2);
	Mat h_result;
	GpuMat d_array1, d_array2, d_array3, d_result;

	d_array1.upload(h_array1);
	d_array2.upload(h_array2);

	const clock_t begin_time = clock();
	cv::cuda::gemm(d_array1, d_array2, 1.0, d_array3, 0.0, d_result);
	cout << "Time elapsed: " << (float(clock() - begin_time) / CLOCKS_PER_SEC) << " sec" << endl;

	d_result.download(h_result);
}

/*
	Исследуем операцию "resize" с параметом масштабирования как в библиотеке FindROI

	*** GPU: Processed 915 in 4094 ms
	*** GPU: Processed 915 in 4106 ms

	*** CPU: Processed 915 in 3603 ms
	*** CPU: Processed 915 in 3583 ms
	*** CPU: Processed 915 in 3579 ms

*/
void test_resize(bool use_gpu = true) {

	int frame_counter = 0;
	int scale_factor = 4;

	Mat frame_in, frame_out;

	cv::cuda::GpuMat frame_in_gpu;
	cv::cuda::GpuMat frame_out_gpu;

	VideoCapture cap(VIDEO_PATH);

	if (!cap.isOpened()) {
		cout << "Error opening file\n";
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	
	while (1) {
	
		cap.read(frame_in);
		if (frame_in.empty()) {
			break;
		}

		if (use_gpu) {
			frame_in_gpu.upload(frame_in);
			cv::cuda::resize(frame_in_gpu, frame_out_gpu, cv::Size(frame_in_gpu.cols / scale_factor, frame_in_gpu.rows / scale_factor), 0, 0, cv::INTER_LINEAR);
			frame_out_gpu.download(frame_out);
		}
		else {
			cv::resize(frame_in, frame_out, cv::Size(frame_in.cols / scale_factor, frame_in.rows / scale_factor), 0, 0, cv::INTER_LINEAR);
		}
		cout << "\t" << frame_counter++ << "\n";
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	int dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	if (use_gpu) {
		cout << "*** GPU: Processed " << frame_counter << " in " << dur << " ms" << "\n";
	}
	else {
		cout << "*** CPU: Processed " << frame_counter << " in " << dur << " ms" << "\n";
	}
	
}


/*
	*** GPU: Processed 915 in 4274 ms
	*** GPU: Processed 915 in 4189 ms
	*** GPU: Processed 915 in 4159 ms

	*** CPU: Processed 915 in 3649 ms
	*** CPU: Processed 915 in 3652 ms
	*** CPU: Processed 915 in 3712 ms
*/
void test_resize_2(bool use_gpu = true) {

	int frame_counter = 0;
	int scale_factor = 4;

	Mat frame_in, frame_out, frame_gray, frame_grad_x, frame_grad_y;

	cv::cuda::GpuMat frame_in_gpu;
	cv::cuda::GpuMat frame_out_gpu;
	cv::cuda::GpuMat frame_gray_gpu;
	cv::cuda::GpuMat frame_grad_x_gpu;
	cv::cuda::GpuMat frame_grad_y_gpu;

	VideoCapture cap(VIDEO_PATH);

	if (!cap.isOpened()) {
		cout << "Error opening file\n";
	}

	auto t1 = std::chrono::high_resolution_clock::now();

	while (1) {

		cap.read(frame_in);
		if (frame_in.empty()) {
			break;
		}

		if (use_gpu) {
			frame_in_gpu.upload(frame_in);
			cv::cuda::resize(frame_in_gpu, frame_out_gpu, cv::Size(frame_in_gpu.cols / scale_factor, frame_in_gpu.rows / scale_factor), 0, 0, cv::INTER_LINEAR);
			cv::cuda::cvtColor(frame_out_gpu, frame_gray_gpu, cv::COLOR_BGR2GRAY);
			//cv::cudev::sobelX_();

			frame_gray_gpu.download(frame_out);
		}
		else {
			cv::resize(frame_in, frame_out, cv::Size(frame_in.cols / scale_factor, frame_in.rows / scale_factor), 0, 0, cv::INTER_LINEAR);
			cv::cvtColor(frame_out, frame_gray, cv::COLOR_BGR2GRAY);

			Sobel(frame_gray, frame_grad_x, CV_32F, 1, 0, -1, -1, 0, cv::BORDER_DEFAULT);
			Sobel(frame_gray, frame_grad_y, CV_32F, 0, 1, -1, -1, 0, cv::BORDER_DEFAULT);
		}
		cout << "\t" << frame_counter++ << "\n";
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	int dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	if (use_gpu) {
		cout << "*** GPU: Processed " << frame_counter << " frames in " << dur << " ms" << "\n";
	}
	else {
		cout << "*** CPU: Processed " << frame_counter << " frames in " << dur << " ms" << "\n";
	}

}

int main() {

	//test_1();
	test_resize_2(true);

	return 0;
}

