
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
                int nowi = i<0? 0:i>=img.rows?img.rows-1:i;
                int nowj = j<0? 0:j>=img.cols?img.cols-1:j;
                intensity += img.at<uchar>(nowi,nowj);
        }
    }
    intensity /= pow(2*r+1,2);
    //cout<<intensity<<cout;//观察有没全为0;
    return intensity;
}

double mean(const vector<vector<double>> &input,const int &rfirst,const int &rlast,const int &cfirst,const int &clast,const int &r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = i<0? 0:i>=input.size()?input.size()-1:i;
                int nowj = j<0? 0:j>=input[0].size()?input[0].size()-1:j;
                intensity += input[nowi][nowj];
        }
    }
    intensity /= pow(2*r+1,2);
    return intensity;
}

double variance(const Mat&img,const int &rfirst,const int &rlast,const int &cfirst,const int &clast,const int &r,const double &mean){
    double intensity = 0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
            int nowi = i<0? 0:i>=img.rows?img.rows-1:i;
            int nowj = j<0? 0:j>=img.cols?img.cols-1:j;
            intensity  += pow(img.at<uchar>(nowi,nowj)-mean,2);
        }
    }
    intensity /= pow(2*r+1,2);
    //cout<<intensity<<endl;
    return intensity;
}

double corelation(const Mat &img,const Mat &I,const int &rfirst, const int &rlast,const int &cfirst,const int &clast,const int &r){
    double intensity = 0.0;
     for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
            int nowi = i<0? 0:i>=img.rows?img.rows-1:i;
            int nowj = j<0? 0:j>=img.cols?img.cols-1:j;
            intensity  +=img.at<uchar>(nowi,nowj)* I.at<uchar>(nowi,nowj);
        }
    }
    intensity /= pow(2*r+1,2);
    return intensity;
}
