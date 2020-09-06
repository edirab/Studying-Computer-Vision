// 
//
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;


void various_detectors() {

	cv::Mat src = cv::imread("E:/University/10sem/Системы технич зрения/Gauss_2/sample.jpg", 1);
	cv::Mat imageWithKeypoints;

	cv::Ptr<cv::FeatureDetector> detector;
	cv::Ptr<cv::DescriptorExtractor> extractor;
	cv::BFMatcher matcher;

	//detector = cv::FastFeatureDetector::create();
	//detector = cv::xfeatures2d::SURF::create();
	detector = cv::xfeatures2d::SIFT::create();

	std::vector<cv::KeyPoint>keys1;
	detector->detect(src, keys1);
	cv::drawKeypoints(src, keys1, imageWithKeypoints);

	imshow("Key points", imageWithKeypoints);

	//imwrite("fast.jpg", imageWithKeypoints);
	//imwrite("surf.jpg", imageWithKeypoints);
	//imwrite("sift.jpg", imageWithKeypoints);
	waitKey(0);
}


int open_video() {

	cv::Mat src;

	cv::VideoCapture cap("E:/University/10sem/Системы технич зрения/Gauss_2/sample_mpg.avi");
	if (!cap.isOpened())
		return -1;
	bool stop = false;
	// Определим частоту кадров на видео
	double rate = cap.get(cv::CAP_PROP_FPS);
	// Рассчитаем задержку в миллисекундах
	int delay = 1000 / rate;

	cout << "Frame rate of video is " << rate << endl;
	while (!stop)
	{
		// Проверяем доступность кадра
		bool result = cap.grab();
		// Если он готов, считываем
		if (result)
			cap >> src;
		else
			continue;
		cv::imshow("Original", src);
		// Ждём нажатия на кнопку
		int key = cv::waitKey(delay);
		if (key == 27) // Если это 0x27, т.е. ESC
			stop = true; // Выходим
	}
	return 0;
}

void brisk_test() {

	cv::Ptr<cv::FeatureDetector> detector;
	cv::Ptr<cv::DescriptorExtractor> extractor;
	cv::BFMatcher matcher;

	vector<cv::KeyPoint>keys1, keys2;
	vector<cv::DMatch> matches;

	Mat descr1, descr2, img_matches;
	
	Mat src = cv::imread("E:/University/10sem/Системы технич зрения/Gauss_2/sample.jpg", 1);
	Mat src2(src);

	detector = cv::BRISK::create();
	extractor = cv::BRISK::create();

	detector->detect(src, keys1);
	detector->detect(src2, keys2);

	extractor->compute(src, keys1, descr1);
	extractor->compute(src2, keys2, descr2);

	matcher.match(descr1, descr2, matches);

	cv::drawMatches(src, keys1, src2, keys2, matches, img_matches);

	cv::imshow("matches", img_matches);
	waitKey(0);
}

int main(int argc, char* argv[]) {
	
	//test();
	//open_video();
	brisk_test();
	
	return 0;
}

