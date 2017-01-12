#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Intermediate/Test2.jpg",CV_LOAD_IMAGE_COLOR);
    int rs = img.rows,cs= img.cols;
    Mat channel_r(rs,cs,CV_8UC1),channel_b(rs,cs,CV_8UC1),channel_g(rs,cs,CV_8UC1);
    for(int i =0;i<rs;++i){
        for(int j=0;j<cs;++j){
                Vec3b temp= img.at<Vec3b> (i,j);
                channel_r.at<uchar>(i,j) = temp[2];
                channel_g.at<uchar>(i,j) = temp[1];
                channel_b.at<uchar>(i,j) = temp[0];
        }
    }
    imshow("source",img);
    imshow("channel_r",channel_r);
    imwrite("CV_Intermediate/practice4/r_img.jpg",channel_r);
    imwrite("CV_Intermediate/practice4/b_img.jpg",channel_b);
    imwrite("CV_Intermediate/practice4/g_img.jpg",channel_g);
    imshow("channel_b",channel_b);
    imshow("channel_g",channel_g);
    waitKey(0);
    return 0;

}
