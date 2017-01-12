#include<stdio.h>
#include<iostream>
//#include<opencv.hpp>
#include<opencv/cv.h>

using namespace std;
using namespace cv;

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  Mat src, dst;
  //const char* imagename = "myImage.jpg";
  char* source_window = "Source image";
  char* equalized_window = "Equalized Image";

  /// 加载源图像
  src = imread( argv[1], 1 );
  //src = imread( imagename );

  if( !src.data )
    { cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
      return -1;}

  /// 转为灰度图
  cvtColor( src, src, CV_BGR2GRAY );

  /// 应用直方图均衡化
  equalizeHist( src, dst );

  /// 显示结果
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );//original image, create windows to show image
  namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );//equalized_image

  imshow( source_window, src );//imshow(windows,matrix_image)
  imshow( equalized_window, dst );

  /// 等待用户按键退出程序
  waitKey(0);

  return 0;
}
