#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat image;
    image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    if(!image.data){
        cout<<"image not found";
        return 1;
    }

    Mat grayimage;
    grayimage = imread("myImage.jpg",CV_LOAD_IMAGE_GRAYSCALE);

    namedWindow("DisplayColor",CV_WINDOW_AUTOSIZE);
    imshow("DisplayColor",image);

    namedWindow("Displaygray",CV_WINDOW_AUTOSIZE);
    imshow("Displaygray",grayimage);

    imwrite("myImage_gray.jpg",grayimage);

    waitKey(0);
    return 0;

}
