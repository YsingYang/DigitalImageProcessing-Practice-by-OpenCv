#include <stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Scale/82.png",0);
    cout<<"original image row:  "<<img.rows<<"   and  Cols  "<<img.cols<<endl;
    Mat dst;
    cv::resize(img,dst,Size(500, 200),CV_INTER_AREA);
    imshow("img",img);
    imshow("dst",dst);
    imwrite("CV_Scale/Down-500-200.jpg",dst);
    waitKey(0);
    return 0;

}
