
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<CV_helper/Histogram.h>

using namespace std;
using namespace  cv;

 int main(){
    Mat img  = imread("CV_RGB/82.png",CV_LOAD_IMAGE_COLOR);
    int maxR=0,maxG=0,maxB=0;
    vector<int> Hist_R = cal_histogram_rgb(img,maxR,0);
    vector<int> Hist_G = cal_histogram_rgb(img,maxG,1);
    vector<int> Hist_B = cal_histogram_rgb(img,maxB,2);//计算三个直方图
    Mat HO1 =out_Histogram(Hist_R,maxR);
    imshow("HO1",HO1);
    imwrite("CV_RGB/original_R.jpg",HO1);

    Mat HO2 = out_Histogram(Hist_G,maxG);
    imshow("HO2",HO2);
    imwrite("CV_RGB/original_G.jpg",HO2);

    Mat HO3 = out_Histogram(Hist_B,maxB);
    imshow("Ho3",HO3);
    imwrite("CV_RGB/original_B.jpg",HO3);

    vector<int> Hist_Aver(256);
    for(int i=0;i<256;++i){
            Hist_Aver[i] =(Hist_B[i] +Hist_G[i]+ Hist_R[i])/3;
    }
    Equalized(img,Hist_Aver,0);
    Equalized(img,Hist_Aver,1);
    Equalized(img,Hist_Aver,2);
    int max1=0,max2=0,max3=0;
    vector<int> cal_H1 = cal_histogram_rgb(img,max1,0);
    Mat HH1 = out_Histogram(cal_H1,max1);
    imshow("ori",HH1);
    imwrite("CV_RGB/Equalized_R.jpg",HH1);

    vector<int> cal_H2 = cal_histogram_rgb(img,max2,1);
    Mat HH2  = out_Histogram(cal_H2,max2);
    imshow("cal_H2",HH2);
    imwrite("CV_RGB/Equalized_G.jpg",HH2);

    vector<int> cal_H3 = cal_histogram_rgb(img,max3,2);
    Mat HH3  = out_Histogram(cal_H3,max3);
    imshow("cal_H3",HH3);
    imwrite("CV_RGB/Equalized_B.jpg",HH3);

    imshow("Equalized_img.jpg",img);
    imwrite("CV_RGB/Equzlized_img.jpg",img);
    waitKey(0);
    return 1;

 }
