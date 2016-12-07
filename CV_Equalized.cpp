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
    //MatND histo = h.getHistogram(image);
    //imshow("Histgram",h.getHistogramImage(image));
    equalizeHist(image,dst);
    getHistogramImage(image);
    imshow("equalize",dst);
    waitKey(0);
    return 1;
}
