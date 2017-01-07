#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){
     float scale_ratio;
    cout<<"Please input the scale_ration you want(int)"<<endl;
    cin>>scale_ratio;

     int radius;
    cout<<"Please input the radius you want(int)"<<endl;
    cin>>radius;
    float sigma;
    cout<<"Please input the sigma you want (float)"<<endl;
    cin>>sigma;
    int i=0;
    while(i<5){
        Mat source = imread("Guilded_Filter/dataset/img_smoothing/"+to_string(i)+".bmp",CV_LOAD_IMAGE_GRAYSCALE);
        Mat guilded_img = imread("Guilded_Filter/dataset/img_smoothing/"+to_string(i)+".bmp",CV_LOAD_IMAGE_GRAYSCALE);


        Mat dst = faster_GF(source,guilded_img,radius,sigma,scale_ratio);
        Mat dst2 = Guild_Filter(source,guilded_img,radius,sigma);
        imwrite("Guilded_Filter/result/"+to_string(radius)+to_string(sigma)+"/"+to_string(i)+to_string(radius)+" radius  " + to_string(sigma) +"sigma"+".jpg",dst2);
        imwrite("Guilded_Filter/result/"+to_string(radius)+to_string(sigma)+"/fast_"+to_string(i)+to_string(radius)+" radius  " + to_string(sigma) +"sigma"+".jpg",dst);
        ++i;
    }
//    imshow("dst2",dst2);
    //imshow("dst",dst);
    waitKey(0);
    return 0;

}
