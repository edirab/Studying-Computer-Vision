#include <iostream>
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );
cv::Mat brightnessEnch (cv::Mat& greyScale);

/**
 * @function main
 */
int main( )
{
  /// Load an image
  src = imread( "Iznos_sample.jpg", 1 );

  /// Convert the image to Gray
  cvtColor( src, src_gray, CV_BGR2GRAY );
  src_gray = brightnessEnch(src_gray);

  imshow ("Original",src_gray);

  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  /* 0: Binary                      cv::THRESH_BINARY
     1: Binary Inverted             cv::THRESH_BINARY_INV
     2: Threshold Truncated         cv::THRESH_TRUNC
     3: Threshold to Zero           cv::THRESH_TOZERO
     4: Threshold to Zero Inverted  cv::THRESH_TOZERO_INV
   */

  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type | cv::THRESH_OTSU);

  imshow( window_name, dst );
 }

cv::Mat brightnessEnch (cv::Mat& greyScale)
{
    double minValue, maxValue;
    cv::minMaxLoc(greyScale, &minValue, &maxValue);
    double deltaStep = 255./(maxValue - minValue), value=minValue;
    cv::Mat lookUpTable (1, 256, CV_8U);
    cv::Mat newGreyScale;
    for (int i=0; i<255; i++)
    {
        if (i<minValue)
            lookUpTable.at<unsigned char>(i) = minValue;
        if ( i>=minValue && i<maxValue)
        {
            value += deltaStep;
            lookUpTable.at<unsigned char>(i) = (unsigned char) value;
        }
        if (i>=maxValue)
            lookUpTable.at<unsigned char>(i) = maxValue;
    }
    cv::LUT(greyScale, lookUpTable, newGreyScale);
//    cv::GaussianBlur(newGreyScale,newGreyScale,cv::Size(5,5),3);
    return newGreyScale;
}
