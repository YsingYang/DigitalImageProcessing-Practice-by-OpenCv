#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<CV_helper/Noise_helper.h>
#include<CV_helper/Filter.h>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Denoise/82.png",0);
    int mean , sd;
    cout<<"Please input Gaussian mean"<<endl;
    cin>>mean;
    cout<<"Please input Gaussian standard deviation"<<endl;
    cin>>sd;
    Mat dst = Gaussian_generator(img,mean,sd);
    int rz,cz;
    cin>>rz;
    cout<<endl;
    cin>>cz;
    Mat ari_result = arithmetic_MF(dst,rz,cz);
    Mat geo_result = geometric_MF(dst,rz,cz);
    Mat medi_result = median_MF(dst,rz,cz);
    imshow("ari_result",ari_result);
    imwrite("CV_Denoise/arithmetic_MF_"+to_string(rz)+"size.jpg",ari_result);
    imwrite("CV_Denoise/geo_result_"+to_string(rz)+"size.jpg",geo_result);
    imwrite("CV_Denoise/medi_result_"+to_string(rz)+"size.jpg",medi_result);
    imshow("geo_result",geo_result);
    imshow("medi_result",medi_result);
    imwrite("CV_Denoise/Gaussian_img.jpg",dst);
    imshow("dst",dst);
    waitKey(0);
    return 1;
}

