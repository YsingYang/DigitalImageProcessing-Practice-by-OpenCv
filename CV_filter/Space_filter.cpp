
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
//mask = 1/9[[1,1,1].[1.1.1],[1,1,1]]
int main(){
    Mat src1;
    int msize;
    vector<int> histgram1(256,0);
    vector<int> histgram2(256,0);
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
                    intensity2 += src1.at<uchar>(i,j);
                }
            }
            src2.at<uchar>(i+msize/2,j+msize/2) = (uchar)(intensity2/pow(msize,2));
        }
    }
    for(int i=0;i<src1.rows;++i){
        for(int j=0;j<src1.cols;++j){
            ++histgram1[(int)src1.at<uchar>(i,j)];
            ++histgram2[(int)src2.at<uchar>(i,j)];
            max1 = max(max1,histgram1[(int)src1.at<uchar>(i,j)]);
            max2 = max(max2,++histgram2[(int)src2.at<uchar>(i,j)]);
        }
    }
    Mat histgraph1 = Mat::zeros(256,256,CV_8U);
    Mat histgraph2 = Mat::zeros(256,256,CV_8U);
    cout<<max1<<" "<<max2<<endl;
    double n1 = 256.0/max1,n2 = (256.0/max2);
    cout<<n1<<" "<<n2<<endl;
    for(int i=0;i<256;++i){
        histgram1[i] = (int) (histgram1[i]*n1);
        histgram2[i] = (int) (histgram2[i]*n2);
        line(histgraph1,Point(i,255-histgram1[i]),Point(i,255),128);
        line(histgraph2,Point(i,255-histgram2[i]),Point(i,255),128);
    }
    imshow("original_hist",histgraph1);
    imshow("filter_hist",histgraph2);
    imshow("original",src1);
    imshow("filter",src2);
    imwrite("filter_hist.jpg",histgraph2);
    imwrite("original_hist.jpg",histgraph1);
    imwrite("original_image.jpg",src1);
    imwrite("filter_image.jpg",src2);
    waitKey(0);
    return 1;
}
