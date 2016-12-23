#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<random>

using namespace std;
using namespace cv;

Mat Gaussian_generator(Mat &img,const float mean,const float sd){
    default_random_engine generator;//随机数生成器
    normal_distribution<double> Gaussian(mean,sd);
    int rs = img.rows,cs = img.cols;
    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int temp;
            temp = img.at<uchar>(i,j) + Gaussian(generator);
            if(temp>255)
                temp=255;
            if(temp<0)
                temp =0;
            dst.at<uchar>(i,j) = temp;
        }
    }
    return dst;
}

Mat Impulse_generator(const Mat &img,double salt,double pepper){
        int rs = img.rows,cs = img.cols;
        double num;
        Mat dst(rs,cs,CV_8UC1);
        for(int i=0;i<rs;++i){
            for(int j=0;j<cs;++j){
                num = (rand()%1000)/1000.0;
                if(num>0&&num<salt){
                    dst.at<uchar>(i,j) = 255;
                }
                else if(num>=salt&&num<(salt+pepper)){
                    dst.at<uchar>(i,j) = 0;
                }
                else{
                    dst.at<uchar>(i,j) = img.at<uchar>(i,j);
                }
            }
        }
    return dst;
}



