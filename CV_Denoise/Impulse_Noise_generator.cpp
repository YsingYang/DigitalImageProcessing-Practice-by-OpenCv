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
    //以下为输入参数的过程.
    cout<<"Please input probabilities of salt (salt+pepper<1)"<<endl;
    cin>>salt;
    cout<<"Please input probabilities of pepper (<1)"<<endl;
    cin>>pepper;
    cout<<"Please input Q parameter"<<endl;
    Mat dst = Impulse_generator(img,salt,pepper);
    int rz,cz;//滤波器大小;
    cin>>Q;
    cout<<"Please input filter size"<<endl;
    cin>>rz;
    cin>>cz;
    Mat arithmetic_MF_result = arithmetic_MF(dst,rz,cz);
    Mat geometric_MF_result = geometric_MF(dst,rz,cz);
    Mat median_MF_result = median_MF(dst,rz,cz);
    Mat harmonic_MF_result = harmonic_MF(dst,rz,cz);
    Mat contraharmonic_MF_result = contraharmonic_MF(dst,rz,cz,Q);
    Mat min_MF_result = min_MF(dst,rz,cz);
//    imshow("median_MF_result",median_MF_result);
   // imshow("arithmetic_MF_result",arithmetic_MF_result);
    //imshow("geometric_MF_result",geometric_MF_result);
    //imshow("harmonic_MF",harmonic_MF_result);
    //imshow("contraharmonic_MF_result",contraharmonic_MF_result);
    //imshow("min_MF_result",min_MF_result);
    //imwrite("CV_Denoise/harmonic_MF_salt.jpg",harmonic_MF_result);
    //imwrite("CV_Denoise/contraharmonic_MF_result_salt_Q_-1.jpg",contraharmonic_MF_result);
    //imwrite("CV_Denoise/min_MF_result_salt.jpg",min_MF_result);
    //imwrite("CV_Denoise/contraharmonic_MF_with"+to_string(Q)+"and_3size.jpg",contraharmonic_MF_1);
    //imwrite("CV_Denoise/contraharmonic_MF_with"+to_string(Q2)+"and_3size.jpg",contraharmonic_MF_2);
    imwrite("CV_Denoise/arithmetic_MF_result.jpg",arithmetic_MF_result);
    imwrite("CV_Denoise/geometric_MF_result.jpg",geometric_MF_result);
    imwrite("CV_Denoise/median_MF_result.jpg",median_MF_result);
    //imwrite("CV_Denoise/Impluse_salt.jpg",dst);
    imshow("dst",dst);
    waitKey(0);
    return 1;
}
