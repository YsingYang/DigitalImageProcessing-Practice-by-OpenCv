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
    int maxB=0,maxG=0,maxR=0;
    vector<int> Hist_B = cal_histogram_rgb(img,maxB,0);
    vector<int> Hist_G = cal_histogram_rgb(img,maxG,1);
    vector<int> Hist_R = cal_histogram_rgb(img,maxR,2);
    imshow("ori",img);
    Mat Eq_G  =Equalized_R(img,Hist_G,1);
    imshow("img.G",Eq_G);
    Mat Eq_R = Equalized_R(img,Hist_R,2);
    imshow("img.r",Eq_R);
    Mat Eq_B = Equalized_R(img,Hist_B,0);
    imshow("img.b",Eq_B);
    //imwrite("CV_RGB/rgb_Equalized.jpg",img);
    imwrite("CV_RGB/Eq_G.jpg",Eq_G);
    imwrite("CV_RGB/Eq_B.jpg",Eq_B);
    imwrite("CV_RGB/Eq_R.jpg",Eq_R);
    waitKey(0);
    return 1;
}
