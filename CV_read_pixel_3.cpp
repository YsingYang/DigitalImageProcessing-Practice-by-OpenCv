
#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using  namespace cv;

int main(){
    Mat image;
    image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    cout<<image;
    return 0;
}
