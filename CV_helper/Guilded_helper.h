
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
      Mat tempa(rs,cs,CV_64FC1),tempb(rs,cs,CV_64FC1);//记录系数a//记录系数b;

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            double mean_I =  mean(guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            //cout<<mean_I<<endl;
            double mean_img = mean(img,i-radius,i+radius,j-radius,j+radius,radius);
            double var = variance(img,i-radius,i+radius,j-radius,j+radius,radius,mean_I);
            double core = corelation(img,guilded_img,i-radius,i+radius,j-radius,j+radius,radius);
            tempa.at<double>(i,j) = (core - mean_I*mean_img);
            if( tempa.at<double>(i,j)<0)
                 tempa.at<double>(i,j) = 0;
             tempa.at<double>(i,j) /= (var+sigma);
             tempb.at<double>(i,j) = (mean_img)- tempa.at<double>(i,j)*mean_I;
        }
        //cout<<endl;
    }

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            tempa.at<double>(i,j) = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
             tempb.at<double>(i,j) = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
        }
    }

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

        //Mat scale_source(scale_rs,scale_cs,CV_8UC1),scale_guilded(scale_rs,scale_cs,CV_8UC1);
        Mat scale_source,scale_guilded;
       /* while(radius%scale_ratio!=0){
            cout<<"Please input the radius you want(int)"<<endl;
            cin>>scale_ratio;
        }*/
        radius *=scale_ratio;

        cout<<scale_ratio<<endl;;
        resize(source,scale_source,Size(),scale_ratio,scale_ratio,INTER_AREA);
       // imshow("scale",scale_source);
        resize(guilded,scale_guilded,Size(),scale_ratio,scale_ratio,INTER_AREA);
        //imshow("g",scale_guilded);

        //cout<<scale_source.rows<<"and "<<scale_source.cols<<endl;
        Mat img(scale_rs,scale_cs,CV_64FC1);
        Mat guilded_img(scale_rs,scale_cs,CV_64FC1);
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

        //vector<vector<double>> tempa(scale_rs,vector<double>(scale_cs));//记录系数a
        //vector<vector<double>> tempb(scale_rs,vector<double>(scale_cs));//记录系数b;
        Mat tempa(scale_rs,scale_cs,CV_64FC1),tempb(scale_rs,scale_cs,CV_64FC1);


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

        for(int i=0;i<scale_rs;++i){
            for(int j=0;j<scale_cs;++j){
                tempa.at<double>(i,j) = mean(tempa,i-radius,i+radius,j-radius,j+radius,radius);
                tempb.at<double>(i,j) = mean(tempb,i-radius,i+radius,j-radius,j+radius,radius);
                //cout<<tempa[i][j]<<endl;
            }
        }

      //  vector<vector<double>> a(rs,vector<double>(cs)),b(rs,vector<double> (cs));
        Mat a(rs,cs,CV_64FC1),b(rs,cs,CV_64FC1);
        resize(tempa,a,Size(),1/scale_ratio,1/scale_ratio,CV_INTER_LINEAR);
        resize(tempb,b,Size(),1/scale_ratio,1/scale_ratio,CV_INTER_LINEAR);

        Mat dst(rs,cs,CV_8UC1);
        for(int i=0;i<rs;++i){
            for(int j=0;j<cs;++j){
               int temp = floor((original_img.at<double>(i,j) *a.at<double>(i,j) +b.at<double>(i,j))*255);
                dst.at<uchar>(i,j) = temp>255?255:temp;
            }
        }
        return dst;
    }
