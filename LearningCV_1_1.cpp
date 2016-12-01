#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat image;
    image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    if(!image.data){
        cout<<"image not fount"<<endl;
        return 1;
    }

    Mat gray_image;
     cvtColor(image, gray_image, CV_BGR2GRAY );

    //namedWindow("Display_color",CV_WINDOW_AUTOSIZE);
    namedWindow("Display_gray",CV_WINDOW_AUTOSIZE);

    //imshow("Display_color",image);
    imshow("Display_gray",gray_image);

    waitKey(0);

    return 0;

}
