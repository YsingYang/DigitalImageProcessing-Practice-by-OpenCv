#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    imshow("original Image",image);

    Mat rgbchannel[3];
    split(image,rgbchannel);

    imshow("Red",rgbchannel[0]);

    imshow("Green",rgbchannel[1]);

    imshow("Blue",rgbchannel[2]);

    Mat dst = Mat::zeros(image.rows,image.cols,CV_8U);
    for(int i=0;i<image.rows;++i){
        for(int j=0;j<image.cols;++j){
            dst.at<uchar>(i,j) = (rgbchannel[0].at<uchar>(i,j)+rgbchannel[1].at<uchar>(i,j)+rgbchannel[2].at<uchar>(i,j))/3;
        }
    }
    imshow("dst",dst);
    imwrite("rgb_Count.jpg",dst);
    waitKey(0);


    return 0;
}
