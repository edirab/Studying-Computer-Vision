
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>

using cv::Mat;

int scale_factor = 4;

int main()
{
	Mat frame;
	cv::cuda::GpuMat frame_gpu;

	frame = cv::imread("C:/cat.jpg");

	frame_gpu.upload(frame);
	cv::cuda::resize(frame_gpu, frame_gpu, cv::Size(frame_gpu.cols / scale_factor, frame_gpu.rows / scale_factor), 0, 0, cv::INTER_LINEAR);
	frame_gpu.download(frame);

	if (!frame.empty()) {

		cv::imshow("Frame", frame);
		cv::waitKey(0);
	}
	else {
		std::cout << "Img is empty\n";

	}



    return 0;
}


