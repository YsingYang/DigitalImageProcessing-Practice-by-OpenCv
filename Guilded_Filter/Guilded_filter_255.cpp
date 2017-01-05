#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/255Level_test.h"

using namespace std;
using namespace  cv;

int main(){
   Mat img = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_smoothing/cat.bmp",0);
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
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa[i][j] = (core - mean_I*mean_img);
            if(tempa[i][j]<0)
                tempa[i][j] = 0;
            tempa[i][j] /= (var+sigma);
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
        }
    }

    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int temp = (floor) (img.at<uchar>(i,j) * tempa[i][j] + tempb[i][j]);
           // cout<<(int)img.at<uchar>(i,j) <<" and "<<temp<<endl;
            dst.at<uchar>(i,j) = temp;
        }
    }

    imshow("img",img);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}

