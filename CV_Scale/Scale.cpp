#include <stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Scale/82.png",0);
    cout<<"original image row:  "<<img.rows<<"   and  Cols  "<<img.cols<<endl;
    cout<<"Please input the size of image you want";
    int drow,dcol,row = img.rows,col = img.cols;
    cin>>drow>>dcol;
    cout<<drow<<dcol;
    Mat dst;//create dst image;
    cv::resize(img,dst,Size(drow, dcol),CV_INTER_LINEAR);
    imshow("img",img);
    imshow("dst",dst);
    //imwrite("CV_Scale/Down-367-298.jpg",dst);
    waitKey(0);
    return 0;

}
