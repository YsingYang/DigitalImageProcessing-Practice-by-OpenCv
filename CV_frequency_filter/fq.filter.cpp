#include <unistd.h>
#include <iostream>
#include <complex>
#include "CV_helper/DFT_helper.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_DFT/82.png",0);
   // int8_t m[12]= {0,1,0,1,-4,1,0,1,0};
    //int8_t m[16] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //Mat mask = (Mat_<int8_t>(3,3)<<1,1,1,1,-8,1,1,1,1);
    Mat mask(7,7,CV_8UC1,Scalar::all(1));
    cout<<mask;
    int rs = img.rows,cs = img.cols;
    int frs = rs + mask.rows -1,frc = cs +mask.cols-1;
    int rsize = 1,csize =1;
    while(rsize<frs){
        rsize <<=1;
    }
    while(csize<frc){
        csize<<=1;
    }
    cout<<rsize<<"  "<<csize<<endl;
    vector<vector< complex<double> > > inter_img(rsize,vector<complex<double> > (csize));
    vector<vector< complex<double> > > inter_mask(rsize,vector<complex<double> > (csize));
    copy_img_vec(inter_img,img);
    //copy_img_vec(inter_mask,mask);
    copy_img_vec_float(inter_mask,mask);
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cout<<inter_mask[i][j]<<"   ";
        }
    }
    img_fft(inter_img);
    img_fft(inter_mask);
    vector<vector< complex<double> > > filted(rsize,vector<complex<double> > (csize));
    for(int i=0;i<rsize;++i){
        for(int j=0;j<csize;++j){
            filted[i][j] = inter_img[i][j] *inter_mask[i][j];
           // cout<<"img   "<<inter_img[i][j]<<"   mask"<<inter_mask[i][j]<<endl;
        }
    }//阵列乘法
    img_fft(filted);//IFFT
    idft_reverse(filted);
    Mat res(rs,cs,CV_32F);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            res.at<float>(i,j) = abs(filted[i][j].real())/(rsize*csize);
        }
    }
  // cout<<res<<endl;
    normalize(res,res,0,1,CV_MINMAX);
    Mat dst = out_normalized(res);
    imshow("res",dst);
    imwrite("CV_frequency_filter/7*7_AMF.jpg",dst);
    // imshow("res",res);
     waitKey(0);
    return 1;
}
