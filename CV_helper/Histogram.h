
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;

vector<int> cal_histogram(const Mat &img,int &maxPixel){
        vector<int> histogram(256,0);
        for(int i=0;i<img.rows;++i){
            for(int j=0;j<img.cols;++j){
                ++histogram[(int)img.at<uchar>(i,j)];
                maxPixel = max(maxPixel,histogram[(int)img.at<uchar>(i,j)]);
            }
        }
        return histogram;
}

Mat out_Histogram(vector<int> Pixelvector,const int maxPixel){
    Mat img = Mat::zeros(256,256,0);
    float scale = 256.0/maxPixel;
    for(int i=0;i<256;++i){
        float hight = (int)(scale * Pixelvector[i]);
        line(img , Point(i,255-hight),Point(i,255),128);
    }
    return img;
}


Mat Equalized(const Mat &img,vector<int> Pixelvector){
    vector<double> Pdf_Vector(256,0);
    vector<uchar> CDF_Vector(256,0);
    int count_Pixel = img.rows * img.cols;
    double last_cdf= 0.0;
    for(int i=0;i<256;++i){
        Pdf_Vector[i] = Pixelvector[i]*1.0/count_Pixel;
        double temp = Pdf_Vector[i] *255.0 + last_cdf;
         CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }//count
    /*for(int i=0;i<256;++i){
        double temp = Pdf_Vector[i] *255 + last_cdf;
        CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }*/
    Mat dst = Mat::zeros(img.rows,img.cols,CV_8UC1);
    for(int i=0;i<dst.rows;++i){
        for(int j=0;j<dst.cols;++j){
            dst.at<uchar>(i,j) = CDF_Vector[img.at<uchar>(i,j)];
        }
    }
    return dst;
}
