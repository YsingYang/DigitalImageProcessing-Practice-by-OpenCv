
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"CV_helper/Histogram.h""

using namespace std;
using namespace cv;


int main(){
    Mat img,dst;
    img = imread("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/82.png",0);//0为灰度图，及时是灰度图也要这么用
    imshow("image",img);
    int maxPi1 =0 ,maxPi2 = 0;
    vector<int> histogram = cal_histogram(img,maxPi1);

    Equalized(img,histogram);
  // vector<int> Ehistgram = cal_histogram(dst,maxPi2);
  //  Mat histgraph = out_Histogram(histogram,maxPi1);
 //   Mat Ehistgraph = out_Histogram(Ehistgram,maxPi2);
    vector<int> Eq_hist = cal_histogram(img,maxPi2);
    imshow("dst",img);
    Equalized(img,Eq_hist);
    imshow("dst2",img);
    //imshow("histgraph",histgraph);
    //imshow("Ehistgraph",Ehistgraph);
    //imwrite("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/original_Hist.jpg",histgraph);
    //imwrite("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/Equalized_imge.jpg",dst);
    //imwrite("/home/ysing/codeblock Projects/OpenCV/EqualizeHist/Equalized_Hist.jpg",Ehistgraph);
    waitKey(0);
    return 1;

}
