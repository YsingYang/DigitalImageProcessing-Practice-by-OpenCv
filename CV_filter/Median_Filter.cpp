
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
    src1 = imread("CV_filter/82.png",0);
    Mat src2 = Mat::zeros(src1.rows,src1.cols,CV_8U);
    //Mat src2 = src1.clone();
     cout<<src1.rows<<"  "<<src2.rows;
     cout<<"  "<<src1.cols<<"  "<<src2.cols<<endl;
    cout<<"Enter the mask Size";
    cin>>msize;//msize<rsize
    //边缘处理
    for(int i=0;i<src1.rows;++i){
        for(int j=0;j<src2.cols;++j){
            int rstart = i-((msize-1)>>1),rends = i+((msize-1)>>1);
            int cstart = j-((msize-1)>>1),cends = j+((msize-1)>>1);
            vector<uchar> intensity;
            for(int p = rstart;p<=rends;++p){
                for(int q= cstart;q<=cends;++q){
                    int nowp = (p<0?src1.rows+p:(p>=src1.rows?p-src1.rows:p) );
                    int nowq = (q<0?src1.cols+q: (q>=src1.cols?q-src1.cols:q));
                    intensity.push_back(src1.at<uchar>(nowp,nowq));
                }
            }
            sort(intensity.begin(),intensity.end());
            //cout<<intensity/9<<"  "<<(int)src1.at<uchar>(i,j)<<endl;
            src2.at<uchar>(i,j) = intensity[msize*msize/2];
        }
    }
    histgram1 = cal_histogram(src1,max1);
    histgram2 = cal_histogram(src2,max2);
    Mat histgraph1 = out_Histogram(histgram1,max1);
    Mat histgraph2 = out_Histogram(histgram2,max2);
    imshow("original_hist",histgraph1);
    imshow("filter_hist",histgraph2);
    imshow("original",src1);
    imshow("filter",src2);
    imwrite("CV_filter/Median_hist.jpg",histgraph2);
    imwrite("CV_filter/MedianFilter_image.jpg",src2);
    waitKey(0);
    return 1;
}
