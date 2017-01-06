#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){
    Mat source1 = imread("Guilded_Filter/dataset/img_smoothing/cat.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    Mat guilded_img = imread("Guilded_Filter/dataset/img_smoothing/cat.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    float scale_ratio;
    cout<<"Please input the scale_ration you want(int)"<<endl;
    cin>>scale_ratio;

     int radius;
    cout<<"Please input the radius you want(int)"<<endl;
    cin>>radius;
    float sigma;
    cout<<"Please input the sigma you want (float)"<<endl;
    cin>>sigma;

    Mat dst = faster_GF(source1,guilded_img,radius,sigma,scale_ratio);
    Mat dst2 = Guild_Filter(source1,guilded_img,radius,sigma);
    imshow("origin",source1);
    imshow("dst2",dst2);
    imshow("dst",dst);
    waitKey(0);
    return 0;

}
