#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){

    //Mat image =Mat::zeros(400,400,CV_8UC1);//CV_<bit-depth>{U|S|F}C(<number_of_channels>)  U is unsigned integer type, S is signed integer type, and F is float type.
        //400 × 400 image with 8bit RGB;
    Mat image =Mat::zeros(400,400,CV_8UC3);

    line (image,Point(100,20),Point(70,50),Scalar(222),2,8);//if Mat if8UC1 ,the image would be grayimge,
    imshow("Line",image);
    waitKey(0);
    return 0;
}
