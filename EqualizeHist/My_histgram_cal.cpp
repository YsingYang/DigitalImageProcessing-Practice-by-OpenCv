
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(){
    Mat image,dst;
    image = imread("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/82.png",0);//0为灰度图，及时是灰度图也要这么用
    imshow("image",image);
    equalizeHist(image,dst);
    imshow("dst",dst);
    vector<float> histgram(256,0);
    vector<float> Ehistgram(256,0);
    for(int i=0;i<image.rows;++i){
        for(int j=0;j<image.cols;++j){
            ++histgram[(int)image.at<uchar>(i,j)];
            ++Ehistgram[(int)dst.at<uchar>(i,j)];
        }
    }
    float maxhist =0,maxe=0;
    for(int i=0;i<histgram.size();++i){
        maxhist = max(maxhist,histgram[i]);
        maxe = max(maxe,Ehistgram[i]);
    }
    Mat histgraph = Mat::zeros(256,256,CV_8U);
    Mat Ehistgraph = Mat::zeros(256,256,CV_8U);
    double  a = (256.0/maxhist),b = (256.0/maxe);

   for(int i=0;i<histgram.size();++i){
        histgram[i] =(int)(histgram[i] * a);
        Ehistgram[i] = (int) (Ehistgram[i] * b);
        line(histgraph,Point(i,255-histgram[i]),Point(i,255),Scalar::all(155));
        line(Ehistgraph,Point(i,255-Ehistgram[i]),Point(i,255),Scalar::all(155));
    }
    imshow("histgraph",histgraph);
    imshow("Ehistgraph",Ehistgraph);
    imwrite("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/original_Hist.jpg",histgraph);
    imwrite("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/Equalized_Hist.jpg",Ehistgraph);
    waitKey(0);
    return 1;

}
