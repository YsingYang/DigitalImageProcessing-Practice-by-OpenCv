
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
    cv::Mat histogram;
    const int histSize = 256;
    float range[] = {0, 255};
    const float *ranges[] = {range};//二维矩阵
    const int channels = 0;
    for(int i=0;i<image.rows;++i){
        for(int j=0;j<image.cols;++j){
            cout<<(int)image.at<uchar>(i,j)<<"  ";
        }
        cout<<endl;
    }

    /*cv::calcHist(&image, 1, &channels,Mat(), histogram, 1, &histSize, &ranges[0], true,false );
    waitKey(0);
    double minVal =0,maxVal=0;//由于没有归一化所以有小数值
    Point  indexmin,indexmax;
    minMaxLoc(histogram,&minVal,&maxVal,&indexmin,&indexmax);
    Mat histimage(histSize,histSize,CV_8U,Scalar(255));//初始化为图像
    int hpt = static_cast<int>(histSize);
    for(int h=0;h<histSize;h++){
        float binVal = histogram.at<float>(h);//直方图在h中的个数？
       int intensity = static_cast<int>(binVal*hpt/maxVal);
        line(histimage,Point(h,histSize),Point(h,histSize-intensity),Scalar::all(0));
    }
    imshow("histgram",histimage);
    waitKey(0);
*/
    return 1;
}
