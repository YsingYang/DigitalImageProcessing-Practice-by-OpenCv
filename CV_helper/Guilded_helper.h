
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;

//以下为取均值的操作
double mean(const Mat &img,const int rfirst,const int rlast,const int cfirst,const int clast,const int r){//仅针对灰度图
    double  intensity=0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
               intensity += img.at<double>(nowi,nowj);
        }
    }
    float sub = 2.0*r+1;
   intensity /= (sub * sub);
    return intensity;
}

//以下为求方差的操作
double variance(const Mat&img,const int rfirst,const int rlast,const int cfirst,const int clast,const int r,const double mean){
    double intensity = 0.0;
    for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
               int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
               intensity += pow(img.at<double>(nowi,nowj)-mean,2);
        }
    }
    float sub = 2.0*r+1;
    intensity /= (sub * sub);
    return intensity;
}

double corelation(const Mat &img,const Mat &I,const int rfirst, const int rlast,const int cfirst,const int clast,const int r){
    double intensity = 0.0;
     for(int i=rfirst;i<=rlast;++i){
        for(int j=cfirst;j<=clast;++j){
                int nowi = (i<0? 0:i>=img.rows?img.rows-1:i);
                int nowj = (j<0? 0:j>=img.cols?img.cols-1:j);
                intensity +=img.at<double>(nowi,nowj) * I.at<double>(nowi,nowj);
        }
    }
    float sub = 2.0*r+1;
    intensity /= (sub * sub);
    return intensity;
}


Mat Guild_Filter(const Mat &source,const Mat &guilded,const int &radius,const float &sigma){
   Mat img(source.rows,source.cols,CV_64FC1);
   Mat guilded_img(guilded.rows,guilded.cols,CV_64FC1);
   int rs = img.rows,cs = img.cols;

    //令像素级别区间至[0,1]
   for(int i =0;i<rs;++i){
        for(int j=0;j<cs;++j){
            img.at<double>(i,j) = source.at<uchar>(i,j)/255.0;
            guilded_img.at<double>(i,j) = guilded.at<uchar>(i,j)/255.0;
        }
    }

      Mat tempa(rs,cs,CV_64FC1),tempb(rs,cs,CV_64FC1);//记录系数a//记录系数b的矩阵;

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            double mean_I =  mean(guilded_img,i-radius,i+radius,j-radius,j+radius,radius);//求guided_img的均值
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);//求p_img的均值
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);//求方差
            double core = corelation(img,guilded_img,i-radius,i+radius,j-radius,j+radius,radius);//求协方差

            tempa.at<double>(i,j) = (core - mean_I*mean_img);
            if( tempa.at<double>(i,j)<0)
                 tempa.at<double>(i,j) = 0;
             tempa.at<double>(i,j) /= (var+sigma);
             tempb.at<double>(i,j) = (mean_img)- tempa.at<double>(i,j)*mean_I;//计算a,与b并放入相应的矩阵中
        }
        //cout<<endl;
    }

    //对a,b求均值
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            tempa.at<double>(i,j) = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
             tempb.at<double>(i,j) = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
        }
    }

    //dst为滤波后图像,由于显示需要[0,255],在这从[0,1]转为[0,255]
    Mat dst(rs,cs,CV_8UC1);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int temp = floor((img.at<double>(i,j) *  tempa.at<double>(i,j) +  tempb.at<double>(i,j))*255);
            dst.at<uchar>(i,j) = temp>255?255:temp;
        }
    }
    return dst;
}

    Mat faster_GF(const Mat &source,const Mat &guilded, int radius,const float &sigma,const float &scale_ratio){
        int rs = source.rows,cs = source.cols;//resize前图片的大小
        int scale_rs = rs*scale_ratio,scale_cs = cs*scale_ratio ;//resize后图片的行和列

        Mat scale_source,scale_guilded;

        radius *=scale_ratio;//这里没写太好,我觉得需要判断做比例后,半径是否为小数,如果是小数需重新输入

        resize(source,scale_source,Size(),scale_ratio,scale_ratio,INTER_AREA);//对图像进行resize操作
        resize(guilded,scale_guilded,Size(),scale_ratio,scale_ratio,INTER_AREA);


        Mat img(scale_rs,scale_cs,CV_64FC1);
        Mat guilded_img(scale_rs,scale_cs,CV_64FC1);//新建2个矩阵存储像素区间为[0,1]的矩阵
       // cout<<img.size()<<"   "<<scale_source.size()<<endl;


        //暂存一个区间为[0,1]的Mat;
       for(int i =0;i<scale_rs;++i){
            for(int j=0;j<scale_cs;++j){
                img.at<double>(i,j) = scale_source.at<uchar>(i,j)/255.0;
                guilded_img.at<double>(i,j) = scale_guilded.at<uchar>(i,j)/255.0;
                //cout<<img.at<double>(i,j)<<"   "<<guilded_img.at<double>(i,j)<<endl;;
            }
        }//令像素级别区间至[0,1]

        Mat original_img(rs,cs,CV_64FC1);
        for(int i=0;i<rs;++i){
            for(int j=0;j<cs;++j){
                original_img.at<double>(i,j) = source.at<uchar>(i,j)/255.0;
            }
        }

        //存储,a,b系数
        Mat tempa(scale_rs,scale_cs,CV_64FC1),tempb(scale_rs,scale_cs,CV_64FC1);


        //求a,b滤波过程
        for(int i=0;i<scale_rs;++i){
        for(int j=0;j<scale_cs;++j){
            double mean_I =  mean(guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(guilded_img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa.at<double>(i,j) = (core - mean_I*mean_img);
            if(tempa.at<double>(i,j)<0)
                tempa.at<double>(i,j) = 0;
            tempa.at<double>(i,j) /= (var+sigma);

            tempb.at<double>(i,j) = (mean_img)-tempa.at<double>(i,j)*mean_I;
        }
        //cout<<endl;
    }

        //对a,b求均值
        for(int i=0;i<scale_rs;++i){
            for(int j=0;j<scale_cs;++j){
                tempa.at<double>(i,j) = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
                tempb.at<double>(i,j) = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
                //cout<<tempa[i][j]<<endl;
            }
        }

      //  vector<vector<double>> a(rs,vector<double>(cs)),b(rs,vector<double> (cs));
      //将a,b,resize 为原图像的大小
        Mat a(rs,cs,CV_64FC1),b(rs,cs,CV_64FC1);
        resize(tempa,a,Size(),1/scale_ratio,1/scale_ratio,CV_INTER_LINEAR);
        resize(tempb,b,Size(),1/scale_ratio,1/scale_ratio,CV_INTER_LINEAR);

        //得到a,b系数,求得滤波后图像dst
        Mat dst(rs,cs,CV_8UC1);
        for(int i=0;i<rs;++i){
            for(int j=0;j<cs;++j){
               int temp = floor((original_img.at<double>(i,j) *a.at<double>(i,j) +b.at<double>(i,j))*255);
                dst.at<uchar>(i,j) = temp>255?255:temp;
            }
        }
        return dst;
    }
