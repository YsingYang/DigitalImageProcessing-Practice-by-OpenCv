
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;

double mean(const Mat &img,const int &rfirst,const int &rlast,const int &cfirst,const int &clast,const int &r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?0:img.at<uchar>(i,j);
        }
    }
    float sub = 2.0*r+1;
  //  intensity /=49.0;
   intensity /= (sub * sub);
    //cout<<intensity<<cout;//观察有没全为0;
    return intensity;
}

double mean(const vector<vector<double>> &input,const int &rfirst,const int &rlast,const int &cfirst,const int &clast,const int &r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                intensity += (i<0||j<0||i>=input.size()||j>=input[0].size())?0: input[i][j];
        }
    }
    float sub = 2.0*r+1;
    intensity /= (sub * sub);
    return intensity;
}

double variance(const Mat&img,const int &rfirst,const int &rlast,const int &cfirst,const int &clast,const int &r,const double &mean){
    double intensity = 0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?pow(mean,2):(img.at<uchar>(i,j)-mean) * (img.at<uchar>(i,j)-mean);
        }
    }
    float sub = 2.0*r+1;
    intensity /= (sub * sub);
    return intensity;
}

double corelation(const Mat &img,const Mat &I,const int &rfirst, const int &rlast,const int &cfirst,const int &clast,const int &r){
    double intensity = 0.0;
     for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
              //  int nowi = (i<0||i>img.rows? 0:i>=img.rows?img.rows-1:i);
    //            int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
                intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?0:( img.at<uchar>(i,j)* I.at<uchar>(i,j));
        }
    }
    float sub = 2.0*r+1;
 //  intensity /=49.0;
    intensity /= (sub * sub);
    return intensity;
}
