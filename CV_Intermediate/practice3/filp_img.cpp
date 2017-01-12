#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main(){
    Mat img1 =  imread("CV_Intermediate/Test2.jpg",CV_LOAD_IMAGE_COLOR);
    Mat img2 = img1.clone();

    int rs = img1.rows,cs = img1.cols;

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            Vec3b temp  = img1.at<Vec3b> (i,j);
            img2.at<Vec3b> (rs-1-i,cs-1-j) = temp;
        }
    }
    imshow("img1",img1);
    imshow("img2",img2);
    imwrite("CV_Intermediate/practice3/filp.jpg",img2);
    waitKey(0);
    return 0;
}
