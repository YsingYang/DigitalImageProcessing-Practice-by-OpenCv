
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<CV_helper/RGB_2_HSI.h>
#include<CV_helper/Histogram.h>

using namespace std;
using namespace  cv;

int main(){
    Mat img  = imread("CV_RGB/82.png",CV_LOAD_IMAGE_COLOR);
    int rs = img.rows ,  cs = img.cols;
    Mat hsi;
    hsi.create(rs,cs,CV_8UC3);
    reHsi(img,hsi);
    //cout<<hsi<endl;
    int maxi = 0,maxe =0;
    imshow("ori_img",img);
    show_Hist(img,0,"ori_0",0);
    show_Hist(img,1,"ori_1",0);
    show_Hist(img,2,"ori_2",0);
    vector<int> i_Hist = cal_histogram_rgb(hsi,maxi,2);
    Mat Hist1 = out_Histogram(i_Hist,maxi);
   // imshow("Hist1",Hist1);

    Equalized(hsi,i_Hist,2);
    //vector<int> Equal_Hist = cal_histogram_rgb(hsi,maxe,2);
   // Mat Hist2 = out_Histogram(Equal_Hist,maxe);
   // imshow("Hist2",Hist2);

    imshow("hsi",hsi);
    show_Hist(hsi,2,"H_Model",0);
    //imshow("img",img);
    hsi2bgr(img,hsi);

    show_Hist(img,0,"equ_0",0);
    show_Hist(img,1,"equ_1",0);
    show_Hist(img,2,"equ_2",0);
    imshow("img",img);
    waitKey(0);
    return 1;
}
