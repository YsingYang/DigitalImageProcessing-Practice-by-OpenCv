
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){
  // Mat img = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_smoothing/cat.bmp",0);

    u_int8_t data[5][5] = {{1,100,2,3,5},{2,100,4,6,7},{3,120,5,3,2},{1,2,3,4,5},{3,4,5,6,7}};
   Mat img(5,5,CV_8UC1,data);
    int rs = img.rows,cs = img.cols;
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
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa[i][j] = (core - mean_I*mean_img)/(var+sigma);
            double temp = tempa[i][j];
            cout<<tempa[i][j]<<"   ";
            tempb[i][j] = (mean_img)-tempa[i][j]*mean_I;
        }
        cout<<endl;
    }

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            tempa[i][j] = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
            tempb[i][j] = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
           //cout<<tempb[i][j]<<"   ";
        }
        //cout<<endl;
    }

    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            dst.at<uchar>(i,j)= (uchar)((img.at<uchar>(i,j) * tempa[i][j] + tempb[i][j]));
          // dst.at<uchar>(i,j) = temp<0?0:temp>255?255:temp;
        }
    }

    imshow("img",img);
    imshow("dst",dst);
   // cout<<dst<<endl;
    waitKey(0);
    return 0;
}
