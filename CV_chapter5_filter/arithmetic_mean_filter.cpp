

#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<CV_helper/Filter.h>

int main(){
    Mat img = imread("CV_chapter5_filter/82_1.png",CV_LOAD_IMAGE_GRAYSCALE);
    int rz,cz;
    float Q;
    cout<<"input,filter rsize";
    cin>>rz;
    cout<<"input filter csize";
    //cin>>cz;

    //cin>>Q;
    Mat dst = arithmetic_MF(img,rz);
    imshow("dst",dst);
    imwrite("CV_chapter5_filter/arithmetic_MF"+to_string(rz)+"_.jpg",dst);
    waitKey(0);
    return 1;
}
