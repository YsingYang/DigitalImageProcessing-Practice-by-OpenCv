#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat image = Mat::zeros(400,400,CV_8UC3);

    line(image,Point(25,50),Point(225,50),Scalar(255,0,0),2,8);//this Point set by(x,y) so, you can consider the first   parameter is col?
    line(image,Point(25,50),Point(25,225),Scalar(0,225,0),2,8);
    line(image,Point(25,225),Point(225,225),Scalar(0,0,225),2,8);
    line(image,Point(225,50),Point(225,225),Scalar(225,225,0),2,8);

    imshow("Square",image);
    waitKey(0);
    return 0;
}
