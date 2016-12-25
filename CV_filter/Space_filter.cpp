
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Histogram.h"
#include "CV_helper/Filter.h"

using namespace std;
using namespace cv;
//mask = 1/9[[1,1,1].[1.1.1],[1,1,1]]
int main(){
    Mat img;
    int k;
    int max1=0,max2=0;
    img = imread("/home/ysing/codeblock Projects/OpenCV/CV_filter/82.png",0);
    cout<<"Please input k"<<endl;
    cin>>k;
    Mat aver_filter1 = arithmetic_MF(img,3,3);
    vector<vector<int>>mask(img.rows,vector<int>(img.cols));//使用vector暂存mask;
    //Mat aver_filter2 = arithmetic_MF(img,7,7);
    //Mat aver_filter3 = arithmetic_MF(img,11,11);
    Mat dst(img.rows,img.cols,CV_8UC1);
    imshow("aver_filter1",aver_filter1);
    for(int i=0;i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            mask[i][j] =(int) img.at<uchar>(i,j) -(int) aver_filter1.at<uchar>(i,j);
            int temp = mask[i][j]*k + img.at<uchar>(i,j);
            if(temp>255)
                temp=255;
            if(temp<0)
                temp =0;
            dst.at<uchar>(i,j) = temp;
        }
    }
    imshow("dst",dst);
   imwrite("CV_filter/high-boost_k="+to_string(k)+".jpg",dst);
    waitKey(0);
    return 1;
}
