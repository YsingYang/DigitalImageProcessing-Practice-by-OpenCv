
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<stdio.h>

using namespace cv;
using namespace std;
int main(){
    Mat img(200,200,CV_8UC1,Scalar::all(0));
    for(int i=60;i<140;++i){
        for(int j=90;j<110;++j){
            img.at<uchar> (i,j) = 255;
        }
    }
    imshow("img",img);
    waitKey(0);
    imwrite("CV_DFT/82t.png",img);
    return 1;
}
