
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;

double mean(const Mat &img,const int rfirst,const int rlast,const int cfirst,const int clast,const int r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
               // intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?0:img.at<double>(i,j);
               intensity += img.at<double>(nowi,nowj);
        }
    }
    float sub = 2.0*r+1;
  //  intensity /=49.0;
   intensity /= (sub * sub);
    //cout<<intensity<<cout;//观察有没全为0;
    return intensity;
}

double mean(const vector<vector<double>> &input,const int rfirst,const int rlast,const int cfirst,const int clast,const int r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = i<0?0:i>=input.size()?input.size()-1:i;
                int nowj = j<0?0:j>=input[0].size()?input[0].size()-1:j;
                //intensity += (i<0||j<0||i>=input.size()||j>=input[0].size())?0: input[i][j];
                intensity += input[nowi][nowj];
        }
    }
    float sub = 2.0*r+1;
 //   intensity /=49.0;
    intensity /= (sub * sub);
    return intensity;
}

double variance(const Mat&img,const int rfirst,const int rlast,const int cfirst,const int clast,const int r,const double mean){
    double intensity = 0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
               int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
               // intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?pow(mean,2):(img.at<double>(i,j)-mean) * (img.at<double>(i,j)-mean);
               intensity += pow(img.at<double>(nowi,nowj)-mean,2);
        }
    }
    float sub = 2.0*r+1;
   // intensity /=49.0;
    intensity /= (sub * sub);
    return intensity;
}

double corelation(const Mat &img,const Mat &I,const int rfirst, const int rlast,const int cfirst,const int clast,const int r){
    double intensity = 0.0;
     for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
                //intensity += (i<0||j<0||i>=img.rows||j>=img.cols)?0:( img.at<double>(i,j)* I.at<double>(i,j));
                intensity +=img.at<double>(nowi,nowj) * I.at<double>(nowi,nowj);
        }
    }
    float sub = 2.0*r+1;
 //  intensity /=49.0;
    intensity /= (sub * sub);
    return intensity;
}


Mat Guild_Filter(const Mat &source,const Mat &guilded,const int &radius,const float &sigma){
   Mat img(source.rows,source.cols,CV_64FC1);
   Mat guilded_img(guilded.rows,guilded.cols,CV_64FC1);
   int rs = img.rows,cs = img.cols;
   for(int i =0;i<rs;++i){
        for(int j=0;j<cs;++j){
            img.at<double>(i,j) = source.at<uchar>(i,j)/255.0;
            guilded_img.at<double>(i,j) = guilded.at<uchar>(i,j)/255.0;
        }
    }
    //令像素级别区间至[0,1]
    vector<vector<double>> tempa(rs,vector<double>(cs));//记录系数a
    vector<vector<double>> tempb(rs,vector<double>(cs));//记录系数b;

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            double mean_I =  mean(guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa[i][j] = (core - mean_I*mean_img);
            if(tempa[i][j]<0)
                tempa[i][j] = 0;
            tempa[i][j] /= (var+sigma);
            double temp = tempa[i][j];
       //     cout<<tempa[i][j]<<"   ";
            tempb[i][j] = (mean_img)-tempa[i][j]*mean_I;
        }
        //cout<<endl;
    }

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            tempa[i][j] = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
            tempb[i][j] = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
        }
    }

    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int temp = floor((img.at<double>(i,j) * tempa[i][j] + tempb[i][j])*255);
            dst.at<uchar>(i,j) = temp>255?255:temp;
        }
    }
    return dst;
    //imshow("img",img);
    //imshow("dst",dst);
}
