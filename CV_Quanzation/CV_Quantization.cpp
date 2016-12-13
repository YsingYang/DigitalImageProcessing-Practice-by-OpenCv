#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Quanzation/82.png",0);
    cout<<"Please input reduce  gray level";
    int level;
    cin>>level;
    Mat dst = Mat::zeros(img.rows,img.cols,0);
    double ra = 255.0/((1<<level)-1);
    img.at<uchar>(150,155)=255;
    imshow("img",img);
    for(int i=0;i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            int  intensity = img.at<uchar>(i,j);
            intensity /= (1<<(8-level));
            intensity *= ra;
            dst.at<uchar>(i,j) = intensity;
        }
    }
    imshow("dst",dst);
    imwrite("CV_Quanzation/1-bit.jpg",dst);
    waitKey(0);
    return 0;
}
