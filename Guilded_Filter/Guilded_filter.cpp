
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){
   Mat img1 = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_smoothing/cat.bmp",0);
   Mat img(img1.rows,img1.cols,CV_64FC1);
   int rs = img.rows,cs = img.cols;
   for(int i =0;i<rs;++i){
        for(int j=0;j<cs;++j){
            img.at<double>(i,j) = img1.at<uchar>(i,j)/255.0;
        }
    }
   // double data[3][3] = {{1.0/255,1.0/255,1.0/255},{1.0/255,2.0/255,3.0/255},{1.0/255,2.0/255,1.0/255}};
    //u_int8_t data[5][5] = {{1,100,2,3,5},{2,100,4,6,7},{3,120,5,3,2},{1,120,3,4,5},{3,130,5,6,7}};
    //cout<<data[0][0]<<endl;
   //Mat img(3,3,CV_64FC1,data);
    vector<vector<double>> tempa(rs,vector<double>(cs));
    vector<vector<double>> tempb(rs,vector<double>(cs));
    int radius;
    cout<<"Please input the radius you want(int)";
    cin>>radius;
    float sigma;
    cout<<"Please input the sigma you want (float)";
    cin>>sigma;

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            double mean_I =  mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa[i][j] = (core - mean_I*mean_img);
            if(tempa[i][j]<0)
                tempa[i][j] = 0;
            tempa[i][j] /= (var+sigma);
            double temp = tempa[i][j];
       //     cout<<tempa[i][j]<<"   ";
            tempb[i][j] = (mean_img)-tempa[i][j]*mean_I;
        }
        //cout<<endl;
    }

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            tempa[i][j] = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
            tempb[i][j] = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
        }
    }

    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int temp = floor((img.at<double>(i,j) * tempa[i][j] + tempb[i][j])*255);
            dst.at<uchar>(i,j) = temp>255?255:temp;
        }
    }

    imshow("img",img);
    imshow("dst",dst);
   // cout<<dst<<endl;
    waitKey(0);
    return 0;
}
