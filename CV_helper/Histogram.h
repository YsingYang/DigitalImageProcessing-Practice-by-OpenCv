
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;

vector<int> cal_histogram(const Mat &img,int &maxPixel){
        vector<int> histogram(256,0);
        for(int i=0;i<img.rows;++i){
            for(int j=0;j<img.cols;++j){
                ++histogram[(int)img.at<uchar>(i,j)];
                maxPixel = max(maxPixel,histogram[(int)img.at<uchar>(i,j)]);
            }
        }
        return histogram;
}//统计直方图 用一个vector<256>存储像素值的个数

vector<int> cal_histogram_rgb(const Mat &img,int &maxPixel,int channel){
     vector<int> histogram(256,0);
        for(int i=0;i<img.rows;++i){
            for(int j=0;j<img.cols;++j){
                ++histogram[(int)(img.at<Vec3b>(i,j)[channel])];
                maxPixel = max(maxPixel,histogram[(int)img.at<uchar>(i,j)]);
            }
        }
        return histogram;
}//用于计算3通道的或者4通道的直方图.

Mat out_Histogram(vector<int> Pixelvector,const int maxPixel){
    Mat img = Mat::zeros(256,256,0);
    float scale = 256.0/maxPixel;
    for(int i=0;i<256;++i){
        float hight = (int)(scale * Pixelvector[i]);
        line(img , Point(i,255-hight),Point(i,255),128);
    }
    return img;
}//导出直方图的图片,用于显示直方图


void Equalized(Mat &img,vector<int> Pixelvector){
    vector<double> Pdf_Vector(256,0);
    vector<uchar> CDF_Vector(256,0);
    int count_Pixel = img.rows * img.cols;
    double last_cdf= 0.0;
    for(int i=0;i<256;++i){
        Pdf_Vector[i] = Pixelvector[i]*1.0/count_Pixel;
        double temp = Pdf_Vector[i] *255.0 + last_cdf;
         CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }//count
    Mat dst = Mat::zeros(img.rows,img.cols,CV_8UC1);
    for(int i=0;i<dst.rows;++i){
        for(int j=0;j<dst.cols;++j){
            img.at<uchar>(i,j) = CDF_Vector[img.at<uchar>(i,j)];
        }
    }
}//直方图均衡化 直接传图片的引用,对图像进行直接改变,如果要返回原矩阵,可以用下面的函数
/*
Mat Equalized(const Mat &img,vector<int> Pixelvector){
    vector<double> Pdf_Vector(256,0);
    vector<uchar> CDF_Vector(256,0);
    int count_Pixel = img.rows * img.cols;
    double last_cdf= 0.0;
    for(int i=0;i<256;++i){
        Pdf_Vector[i] = Pixelvector[i]*1.0/count_Pixel;
        double temp = Pdf_Vector[i] *255.0 + last_cdf;
         CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }//count
    Mat dst = Mat::zeros(img.rows,img.cols,CV_8UC1);
    for(int i=0;i<dst.rows;++i){
        for(int j=0;j<dst.cols;++j){
            dst.at<uchar>(i,j) = CDF_Vector[img.at<uchar>(i,j)];
        }
    }
    return dst;
}*/

//用于3通道以上的直方图均衡化,可以指定具体通道的直方图均衡化

void Equalized(Mat &img,vector<int> Pixelvector,int channel){
    vector<double> Pdf_Vector(256,0);
    vector<uchar> CDF_Vector(256,0);
    int count_Pixel = img.rows * img.cols;
    double last_cdf= 0.0;
    for(int i=0;i<256;++i){
        Pdf_Vector[i] = Pixelvector[i]*1.0/count_Pixel;
        double temp = Pdf_Vector[i] *255.0 + last_cdf;
         CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }
    for(int i=0;i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            img.at<Vec3b>(i,j)[channel] = CDF_Vector[img.at<Vec3b>(i,j)[channel]];
        }
    }
}
//返回一个矩阵的直方图均衡化
Mat Equalized_R(Mat img,vector<int> Pixelvector,int channel){
    vector<double> Pdf_Vector(256,0);
    vector<uchar> CDF_Vector(256,0);
    int count_Pixel = img.rows * img.cols;
    double last_cdf= 0.0;
    for(int i=0;i<256;++i){
        Pdf_Vector[i] = Pixelvector[i]*1.0/count_Pixel;
        double temp = Pdf_Vector[i] *255.0 + last_cdf;
         CDF_Vector[i] = (uchar)(temp - floor(temp)>=0.5? ceil(temp):floor(temp));
        last_cdf = temp;
    }
    Mat dst = img.clone();
    for(int i=0;i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            dst.at<Vec3b>(i,j)[channel] = CDF_Vector[img.at<Vec3b>(i,j)[channel]];
        }
    }
    return dst;
}


//用于显示直方图.fwrited为是否导出图片,1为导出图片 ,name为给直方图的命名字符串,该函数主要调用了之前的计算和导出直方图矩阵的函数,用于直接显示图片的直方图

void show_Hist(Mat &img,int channel,string name,int fwrited){//如果fwrited 为1 则保存图片
    int maxPixel=0;
    vector<int> Hist = cal_histogram_rgb(img,maxPixel,channel);
    Mat Hist_graph= out_Histogram(Hist,maxPixel);
    imshow(name,Hist_graph);
    //string address = "CV_helper/"+name+""
    if(fwrited)
        imwrite("CV_helper/"+name+".jpg",Hist_graph);
}
