#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<CV_helper/RGB_2_HSI.h>
#include<CV_helper/Histogram.h>
//#include<CV_helper/Filter.h>

using namespace std;
using namespace cv;

Mat arithmetic_MF(const Mat &img,int rz,int cz,int channel){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin>>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin>>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst =img.clone();
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            double  intensity =0.0;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends&&intensity!=-1;++u){
                for(int v= cstart;v<=cends&&intensity!=-1;++v){
                    int nowu = u<0?0:(u>=rs?rs-1:u);
                    int nowv = v<0?0:(v>=cs?cs-1:v);
                    intensity += img.at<Vec3b>(nowu,nowv)[channel];
                }
            }
            intensity = intensity *1.0/(rz*cz);
            dst.at<Vec3b>(i,j)[channel] = (int)intensity;
        }
    }
    return dst;
}

int main(){
    //创建要进行滤波的图像
    Mat img(150,150,CV_8UC3);
    for(int i=0;i<150;++i){
        for(int j=0;j<150;++j){
            if(i<75){
                img.at<Vec3b>(i,j) = j<75? Vec3b(0, 255, 255):Vec3b(255, 0, 255) ;
            }
            else{
                img.at<Vec3b>(i,j) = j<75?  Vec3b(255,255,0):Vec3b(0,255,0);
            }
        }
    }
    Mat dst(150,150,CV_8UC3);
    imshow("ori",img);
    reHsi(img,dst);
    imshow("dst",dst);
     show_Hist(dst,0,"hsi_h",0);
      show_Hist(dst,1,"hsi_s",0);
      show_Hist(dst,2,"hsi_i",0);
    dst = arithmetic_MF(dst,75,75,1);
    show_Hist(dst,0,"MF_hsi_h",0);
    show_Hist(dst,1,"MF_hsi_s",0);
      show_Hist(dst,2,"MF_hsi_i",0);
    imshow("MF",dst);
    hsi2bgr(img,dst);
    imshow("img",img);
    imwrite("CV_RGB/Sat_Ave.jpg",img);
    waitKey(0);
    return 0;
}
