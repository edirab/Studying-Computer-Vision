
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;


int main(int argc, char *argv[]) {

	// Load input video
	VideoCapture input_cap("E:/University/10sem/Системы технич зрения/studying-computer-vision/Retinex/video/retinex-sample3.mp4");
	if (!input_cap.isOpened())
	{
		std::cout << "!!! Input video could not be opened" << std::endl;
		return -1;
	}

	// Setup output video
	cv::VideoWriter output_cap("testo.avi",
		//input_cap.get(CAP_PROP_FOURCC),
		VideoWriter::fourcc('D', 'I', 'V', 'X'),
		input_cap.get(CAP_PROP_FPS),
		cv::Size(input_cap.get(CAP_PROP_FRAME_WIDTH),
			input_cap.get(CAP_PROP_FRAME_HEIGHT)));

	if (!output_cap.isOpened())
	{
		std::cout << "!!! Output video could not be opened" << std::endl;
		return -1;
	}


	// Loop to read from input and write to output
	cv::Mat frame;

	while (true)
	{
		if (!input_cap.read(frame))
			break;

		output_cap.write(frame);
	}

	input_cap.release();
	output_cap.release();

	return 0;
}