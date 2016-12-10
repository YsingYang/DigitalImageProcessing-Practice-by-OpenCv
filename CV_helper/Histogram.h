
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
