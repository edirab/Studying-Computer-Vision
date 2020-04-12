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

int filterSize = 7;

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
  cv::Mat gaus, median, boxed;
  cv::boxFilter(srcGrey,boxed,-1, cv::Size(filterSize,filterSize));
  cv::medianBlur(srcGrey, median, filterSize);
  cv::GaussianBlur(srcGrey, gaus, cv::Size(filterSize,filterSize),3);
  cv::imshow ("Gaussian filter", gaus);
  cv::imshow ("Box filter", boxed);
  cv::imshow ("Median filter", median);

  cv::imwrite ("Gaussian.jpg", gaus);
  cv::imwrite ("Box.jpg", boxed);
  cv::imwrite ("Median.jpg", median);
  cv::waitKey();

}

void adaptiveTreshold( int, void* )
{
    cv::adaptiveThreshold(srcGrey, binary, 255, type, cv::THRESH_BINARY, sizeValue*2+3, constValue-11);
    cv::medianBlur(binary, binary, 5);
    cv::imshow( window_name, binary );
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
    cv::GaussianBlur(newGreyScale,newGreyScale,cv::Size(5,5),3);
    return newGreyScale;
}

