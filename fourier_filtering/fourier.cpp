// Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

void CalcFFT(Mat input, Mat &complex);
void CalcIFFT(Mat complex, Mat &output);
void fftshift(const Mat& inputImg, Mat& outputImg);
Mat MakeHPF(Size size, int D, int n, float high_h_v_TB, float low_h_v_TB);


string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

int main()
{
	//VideoCapture cap("../../Retinex/video/retinex-sample3.mp4");

	VideoCapture cap("E:/University/10sem/Системы технич зрения/studying-computer-vision/Retinex/video/retinex-sample3.mp4");
	//VideoCapture cap("retinex-sample3.mp4");
	//VideoCapture cap("testo.avi");

	//if (!cap.isOpened())
	//	cout << "!!! Input video could not be opened" << endl;
	//	return -1;

	VideoWriter video("retinex-fourier.avi", 
						VideoWriter::fourcc('D', 'I', 'V', 'X'), 
						cap.get(CAP_PROP_FPS),
						//Size(1280, 720));
						Size(1270, 710));

	if (!video.isOpened())
	{
		cout << "!!! Output video could not be opened" << endl;
		return -1;
	}

	bool stop = false;
	Mat img_in;
	int frame_no = 1;

	while (true) {

		cap.read(img_in); // imread(, IMREAD_COLOR);

		if (img_in.empty()) //check whether the image is loaded or not
		{
			cout << "ERROR : New frame cannot be loaded..!!" << endl;
			break;
		}

		//if (frame_no == 30) {
		//	break;
		//}

		Mat img_hsv, img_gray;
		Mat hsv_array[3];
		//Rect roi(0, 0, hsv_array[2].cols - 10, hsv_array[2].rows - 10);
		Rect roi(0, 0, img_in.cols - 10, img_in.rows - 10);

		int high_h_v_TB = 120;
		int low_h_v_TB = 80;
		int D = 10;// radius of band pass filter parameter
		int order = 2;

		cvtColor(img_in, img_hsv, COLOR_BGR2HSV);
		split(img_hsv, hsv_array);

		bool debug = true;
		debug = false;

		if (debug) {
			//imshow("Blue", img_in[0]);
			cvtColor(img_hsv, img_gray, COLOR_BGR2GRAY);
			imshow("Original", img_in);
			imshow("HSV", img_hsv);
			imshow("gray", img_gray);

			waitKey(0);
		}

		Mat imgMagn, imgPhase, imgOut, imgComplex;

		CalcFFT(hsv_array[2], imgComplex);
		fftshift(imgComplex, imgComplex);

		Mat filter = MakeHPF(imgComplex.size(), D, order, high_h_v_TB, low_h_v_TB);

		mulSpectrums(imgComplex, filter, imgComplex, 0);
		fftshift(imgComplex, imgComplex);
		CalcIFFT(imgComplex, imgOut);


		imgOut = imgOut(roi);
		normalize(imgOut, imgOut, 0, 1, NORM_MINMAX);
		imgOut.convertTo(imgOut, CV_8UC1, 255, 0);

		if (debug) {
			imshow("Transformed Val channel", imgOut);
			cout << type2str(imgOut.type()) << "\n";
			waitKey(0);
		}
		//imgOut.convertTo(imgOut, CV_8UC1);
		//cout << type2str(imgOut.type()) << "\n\n";

		vector<Mat> hsv_cropped;
		Mat img_merged;

		hsv_cropped.push_back(hsv_array[0](roi));
		hsv_cropped.push_back(hsv_array[1](roi));
		hsv_cropped.push_back(imgOut);

		if (debug) {
			cout << type2str(hsv_cropped[0].type()) << "\n";
			cout << type2str(hsv_cropped[1].type()) << "\n";
			cout << type2str(hsv_cropped[2].type()) << "\n";
		}

		//merge()
		merge(hsv_cropped, img_merged);
		cvtColor(img_merged, img_merged, COLOR_HSV2BGR);
		
		if (debug) {
			imshow("Final", img_merged);
			waitKey(0);
		}

		video.write(img_merged);
		// Ждём нажатия на кнопку
		//int key = cv::waitKey();
		//if (key == 27) // Если это 0x27, т.е. ESC
		//	stop = true; // Выходим
		cout << "Frame # " << frame_no++ << "\n";
	}
	cap.release();
	video.release();
	
	// Closes all the windows	
	//destroyAllWindows();
	return 0;
}


void CalcFFT(Mat input, Mat &complex)
{
	int padRows = getOptimalDFTSize(input.rows);
	int padCols = getOptimalDFTSize(input.cols);
	// Преобразование Фурье эффективно считается не дял всех размеров
	Mat imgIn, padded, imgComplex;
	input.convertTo(imgIn, CV_32F);
	imgIn += 1; // Чтобы мои значения были больше 1
	log(imgIn, imgIn); // логарифмирование - вместо умножения получили сложение
	copyMakeBorder(imgIn, padded, 0, padRows - imgIn.rows, 0, padCols - imgIn.cols, BORDER_CONSTANT);
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	merge(planes, 2, imgComplex);
	dft(imgComplex, complex, DFT_SCALE);
}
void CalcIFFT(Mat complex, Mat &output)
{
	dft(complex, output, DFT_INVERSE | DFT_REAL_OUTPUT);
	exp(output, output); // мы до этого в логарифмическом масштабе работали
}


void fftshift(const Mat& inputImg, Mat& outputImg)
{
	outputImg = inputImg.clone();
	int cx = outputImg.cols / 2;
	int cy = outputImg.rows / 2;
	Mat q0(outputImg, Rect(0, 0, cx, cy));
	Mat q1(outputImg, Rect(cx, 0, cx, cy));
	Mat q2(outputImg, Rect(0, cy, cx, cy));
	Mat q3(outputImg, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}


Mat MakeHPF(Size size, int D, int n, float high_h_v_TB, float low_h_v_TB)
{
	Mat filter(size, CV_32F);
	Point centre = Point(filter.rows / 2, filter.cols / 2);
	double radius;
	float upper = (high_h_v_TB * 0.01);
	float lower = (low_h_v_TB * 0.01);
	for (int i = 0; i < filter.rows; i++)
	{
		for (int j = 0; j < filter.cols; j++)
		{
			radius = (double)sqrt(pow((i - centre.x), 2.0) + pow((double)(j - centre.y), 2.0));
			filter.at<float>(i, j) = \
				((upper - lower) * (1 / (1 + pow((double)(D / radius), (double)(2 * n))))) + lower;
		}
	}
	Mat planes[2] = { Mat_<float>(filter.clone()), Mat::zeros(filter.size(), CV_32F) };
	merge(planes, 2, filter);
	normalize(planes[0], planes[0], 0, 1, NORM_MINMAX);
	//imshow("Filter", planes[0]);

	return filter;
}
