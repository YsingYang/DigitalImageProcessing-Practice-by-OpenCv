
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Histogram.h"

using namespace std;
using namespace cv;
//mask = 1/9[[1,1,1].[1.1.1],[1,1,1]]
int main(){
    Mat src1;
    int msize;
    vector<int> histgram1;
    vector<int> histgram2;
    int max1=0,max2=0;
    src1 = imread("/home/ysing/codeblock Projects/OpenCV/CV_filter/82.png",0);
    Mat src2 = Mat::zeros(src1.rows,src1.cols,CV_8U);
    //Mat src2 = src1.clone();
     cout<<src1.rows<<"  "<<src2.rows;
     cout<<"  "<<src1.cols<<"  "<<src2.cols<<endl;
    cout<<"Enter the mask Size";
    cin>>msize;//msize<rsize
    for(int i=0;i<src1.rows-msize;++i){
        for(int j=0;j<src1.cols-msize;++j){
            int  intensity2 =0;
            for(int p=0;p<msize;++p){
                for(int q=0;q<msize;++q){
                    intensity2 += src1.at<uchar>(i+p,j+q);
                }
            }
            src2.at<uchar>(i+msize/2,j+msize/2) = (uchar)(intensity2/pow(msize,2));
        }
    }
    histgram1 = cal_histogram(src1,max1);
    histgram2 = cal_histogram(src2,max2);
    cout<<max1<<"  "<<max2<<endl;
    Mat histgraph1 = out_Histogram(histgram1,max1);
    Mat histgraph2 = out_Histogram(histgram2,max2);
    imshow("original_hist",histgraph1);
    imshow("filter_hist",histgraph2);
    imshow("original",src1);
    imshow("filter",src2);
    imwrite("CV_filter/Averaging_filter_hist.jpg",histgraph2);
    imwrite("CV_filteroriginal_hist.jpg",histgraph1);
    imwrite("CV_filteroriginal_image.jpg",src1);
    imwrite("CV_filter/Averagingfilter_image.jpg",src2);
    waitKey(0);
    return 1;
}
