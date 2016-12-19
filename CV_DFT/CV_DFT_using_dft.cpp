#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){

    Mat img = imread("CV_DFT/82.png",0);
    Mat dst = Mat::zeros(img.rows,img.cols,CV_32F);
    dft(img,dst);
    imshow("img",img);
    imshow("dst",dst);
    waitKey(0);

}
