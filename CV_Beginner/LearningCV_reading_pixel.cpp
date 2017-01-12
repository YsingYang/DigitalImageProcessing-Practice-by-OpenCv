#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>


using namespace std;
using   namespace cv;


int main(){
    Mat image;
    image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    if(!image.data){
        cout<<"image not found";
        return -1;
    }

    Vec3b imagepixel = image.at<Vec3b>(100,100);//using Vec3b
    cout<<"imagepixel(BGR="<<imagepixel<<endl;

    namedWindow("Display_image");
    imshow("Display_image",image);
    waitKey(0);
    return 0;
}
