
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
    //Mat img  = imread("CV_RGB/82.png",CV_LOAD_IMAGE_COLOR);
    Mat img (1,1,CV_16SC3);
    img.at<Vec3b>(0,0)[0] = 90;
     img.at<Vec3b>(0,0)[1] = 253;
      img.at<Vec3b>(0,0)[2] = 8;
    int rs = img.rows ,  cs = img.cols;
    Mat hsi;
    hsi.create(rs,cs,CV_8UC3);
    reHsi(img,hsi);//BRG  TO  HSI
    //cout<<hsi<endl;
    int maxi = 0;
    cout<<hsi<<endl;
    imshow("ori_img",img);//显示原图

    show_Hist(img,0,"ori_0",0);
    show_Hist(img,1,"ori_1",0);
    show_Hist(img,2,"ori_2",0);
    //显示原图BGR的直方图

    vector<int> i_Hist = cal_histogram_rgb(hsi,maxi,2);
    Mat Hist1 = out_Histogram(i_Hist,maxi);
    Equalized(hsi,i_Hist,2);
    //计算直方图同时进行hsi中i通道的直方图均衡化后结果

    imshow("hsi",hsi);

    hsi2bgr(img,hsi);//HSI TO BRG

    show_Hist(img,0,"equ_0",0);
    show_Hist(img,1,"equ_1",0);
    show_Hist(img,2,"equ_2",0);
    //显示直方图

    imshow("img",img);
    waitKey(0);
    return 1;
}
