#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Intermediate/Test2.jpg",CV_LOAD_IMAGE_COLOR);
    int rs = img.rows,cs= img.cols;
    vector<Mat> channel(3);
    split(img,channel);
    Mat dst;
    merge(channel,dst);
    imshow("r",channel[2]);
    imshow("g",channel[1]);
    imshow("b",channel[0]);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}
