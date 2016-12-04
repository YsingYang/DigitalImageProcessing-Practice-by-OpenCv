#include<stdio.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){
    int count = 0,a=0,b=100,i,j,p=0,q=0;
    Mat image = Mat::zeros(500,500,CV_8UC3);
    for(;a<500;){
        ++count;
        if(count&1){
            i=a;
            if(!(p&1)){
                j = b + 100;
            }
            else
                j = b -100;
            ++p;
        }
        else{
            j = b;
            i = a + 50;
        }
        line(image,Point(a,b),Point(i,j),Scalar(150,150,150),2,8);
        cout<<"zhixing"<<endl;
        waitKey(100);
        imshow("wave",image);
        a =i;
        b = j;
    }

    waitKey(0);
    imwrite("Draw_wave.jpg",image);
    return 1;
}
