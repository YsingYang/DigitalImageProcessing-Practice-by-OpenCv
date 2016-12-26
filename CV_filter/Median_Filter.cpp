
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Histogram.h"
#include "CV_helper/Filter.h"

using namespace std;
using namespace cv;
//mask = 1/9[[1,1,1].[1.1.1],[1,1,1]]
int main(){
    Mat src1 = imread("CV_filter/Median.jpg");
    int msize;
    imshow("img",src1);
    Mat src2 = median_MF(src1,msize,msize);
    imshow("MMF",src2);
    //imwrite("CV_filter/Median_hist.jpg",histgraph2);
   // imwrite("CV_filter/MedianFilter_image.jpg",src2);
    waitKey(0);
    return 1;
}
