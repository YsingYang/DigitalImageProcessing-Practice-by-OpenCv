#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main(){
    int p[3];
    IplImage *img = cvLoadImage("/home/ysing/codeblock Projects/OpenCV/CV_Intermediate/Test_img.jpg");

    p[0] = CV_IMWRITE_JPEG_QUALITY;
    p[1] = 25;
    p[2] = 0;
    cvSaveImage("/home/ysing/codeblock Projects/OpenCV/CV_Intermediate/practice1/result_img1.jpg",img,p);

    p[0] = CV_IMWRITE_JPEG_QUALITY;
    p[1] = 100;
    p[2] = 0;
    cvSaveImage("CV_Intermediate/practice1/result_img2.jpg",img,p);
    waitKey(0);
    return 0;
}

//C++: bool imwrite(const string& filename, InputArray img, const vector<int>& params=vector<int>() )
//C: int cvSaveImage(const char* filename, const CvArr* image, const int* params=0 )
