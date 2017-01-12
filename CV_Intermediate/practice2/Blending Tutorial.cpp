#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main(){
    Mat img1 = imread("CV_Intermediate/Test1.jpg",CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread("CV_Intermediate/Test2.jpg",CV_LOAD_IMAGE_COLOR);
    resize(img2,img2,img1.size(),CV_INTER_LINEAR);
    int rs1 =  img1.rows,cs1 = img1.cols;
    int rs2 = img2.rows,cs2 = img2.cols;
    if(rs1!=rs2||cs1!=cs2){
        cout<<" imgs is not same size";
        return 0;
    }
    double alpha = rand()%1000000/1000000.0;
    double beta = 1.0 - alpha;
    Mat dst;
    addWeighted(img1,alpha,img2,beta,0.0,dst);
    imshow("img1",img1);
    imshow("dst",dst);
    imwrite("CV_Intermediate/practice2/blending_res.jpg",dst);
    imshow("img",img2);
    waitKey(0);
    return 0;
}
