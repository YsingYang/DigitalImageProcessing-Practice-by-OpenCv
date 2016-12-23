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
    double salt,pepper,Q,Q2;
    cout<<"Please input probabilities of salt (salt+pepper<1)"<<endl;
    cin>>salt;
    cout<<"Please input probabilities of pepper (<1)"<<endl;
    cin>>pepper;
    cout<<"Please input Q parameter"<<endl;
    Mat dst = Impulse_generator(img,salt,pepper);
    int rz,cz;//滤波器大小;
    cin>>rz;
    cin>>cz;
    Mat arithmetic_MF_result = arithmetic_MF(dst,rz,cz);
    Mat geometric_MF_result = geometric_MF(dst,rz,cz);
    Mat median_MF_result = median_MF(dst,rz,cz);
    imshow("median_MF_result",median_MF_result);
    imshow("arithmetic_MF_result",arithmetic_MF_result);
    imshow("geometric_MF_result",geometric_MF_result);
    //imwrite("CV_Denoise/contraharmonic_MF_with"+to_string(Q)+"and_3size.jpg",contraharmonic_MF_1);
    //imwrite("CV_Denoise/contraharmonic_MF_with"+to_string(Q2)+"and_3size.jpg",contraharmonic_MF_2);
    //imwrite("CV_Denoise/Impluse.jpg",dst);
    imshow("dst",dst);
    waitKey(0);
    return 1;
}
