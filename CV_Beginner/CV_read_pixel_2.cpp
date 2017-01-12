#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using  namespace cv;

int main(){
    Mat image;
    image = imread("myImage.jpg",CV_LOAD_IMAGE_ANYCOLOR);

    if(!image.data){
        cout<<"image not found"<<endl;
        return 1;
    }

    while(1){
        int row,col;
        cout<<"Enter the co-ordinates of the image where you want to find the pixel value (i,j): \n";
        cout<<"i<"<<image.rows<<"\t"<<"&"<<"\t"<<"j<"<<image.cols<<"\n";

        cout<<"i="; cin>>row;
        cout<<"col=";cin>>col;
        if(row<image.rows){
            if(col<image.cols){
                Vec3b imagepixel = image.at<Vec3b> (row,col);
                cout<<"pixel is "<<imagepixel<<endl;
            }
            else{
                cout<<"end"<<endl;
                return 1;
            }
        }
    }
    return 1;
}
