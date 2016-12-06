
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(){
    Mat image,dst;
    image = imread("82.png",0);//0为灰度图，及时是灰度图也要这么用
    imshow("image",image);
    vector<float> histgram(256,0);
    for(int i=0;i<image.rows;++i){
        for(int j=0;j<image.cols;++j){
            ++histgram[(int)image.at<uchar>(i,j)];
        }
    }
    float maxhist =0;
    for(int i=0;i<histgram.size();++i){
        maxhist = max(maxhist,histgram[i]);
    }
    Mat histgraph = Mat::zeros(256,256,CV_8U);
    double  a = (256.0/maxhist);
    for(int i=0;i<histgram.size();++i){
        histgram[i] =(int)(histgram[i] * a);
        line(histgraph,Point(i,255-histgram[i]),Point(i,255),Scalar::all(155));
    }
    imshow("histgraph",histgraph);
    waitKey(0);
    return 1;

}
