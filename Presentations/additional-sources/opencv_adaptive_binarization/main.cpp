#include <iostream>
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <stdio.h>

char* window_name = "Threshold Demo";
char* trackbar_type = "Type: \n 0: Mean \n 1: Gausian";
char* trackbar_size = "Size: \n 3 \n 5 \n 7 \n 9 \n 11 \n 15 \n 17 \n 19";
char* trackbar_const = "const";
int maxConst = 21;
int maxSize = 7;
int maxType = 1;

int sizeValue = 2, constValue = 11;

void adaptiveTreshold( int, void* );
cv::Mat brightnessEnch (cv::Mat& greyScale);
enum binariztionType {mean = cv::ADAPTIVE_THRESH_MEAN_C, gausian = cv::ADAPTIVE_THRESH_GAUSSIAN_C};
int type = mean;
cv::Mat srcGrey, binary;

int main( )
{
  /// Load an image
  cv::Mat src = cv::imread( "Iznos_sample.jpg", 1 );
  cv::imshow ("Original", src);

  /// Convert the image to Grey
  cvtColor( src, srcGrey, CV_BGR2GRAY );
  srcGrey = brightnessEnch(srcGrey);

  /// Create a window to display results
  cv::namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  cv::createTrackbar( trackbar_type,
                  window_name, &type,
                  maxType, adaptiveTreshold );
  cv::createTrackbar( trackbar_size,
                  window_name, &sizeValue,
                  maxSize, adaptiveTreshold );
  cv::createTrackbar( trackbar_const,
                  window_name, &constValue,
                  maxConst, adaptiveTreshold );
  adaptiveTreshold( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = cv::waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}

void adaptiveTreshold( int, void* )
{
    cv::adaptiveThreshold(srcGrey, binary, 255, type, cv::THRESH_BINARY, sizeValue*2+3, constValue-11);
    cv::imshow( window_name, binary );
}

