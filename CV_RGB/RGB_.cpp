#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"CV_helper/Histogram.h"

using namespace std;
using namespace cv;

int main(){
    Mat img  = imread("CV_RGB/82.png",CV_LOAD_IMAGE_COLOR);
    int maxR=0,maxG=0,maxB=0;
    vector<int> Hist_R = cal_histogram_rgb(img,maxR,0);
    vector<int> Hist_G = cal_histogram_rgb(img,maxG,1);
    vector<int> Hist_B = cal_histogram_rgb(img,maxB,2);
    imshow("ori",img);
    Equalized(img,Hist_G,1);
    Equalized(img,Hist_B,2);
    Equalized(img,Hist_R,0);
    imshow("rgb",img);
    imwrite("CV_RGB/rgb_Equalized.jpg",img);
    waitKey(0);
    return 1;
}
