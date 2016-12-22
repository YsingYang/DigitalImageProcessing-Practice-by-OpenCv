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
     int rs = img.rows,cs = img.cols;
    int rsize =1,csize=1;
    while(rsize<rs){
        rsize <<=1;
    }
    while(csize<cs){
        csize<<=1;
    }
    cout<<rsize<<"  "<<csize<<endl;
    //getOptimalDFTSize
    vector<vector< complex<double> > > intervet(rsize,vector<complex<double> > (csize));
    for(int i =0;i<rs;++i){
        for(int j=0;j<cs;++j){
            if(((i+j)&1)==1)
                intervet[i][j]  = 255 -img.at<uchar>(i,j);
            else
                intervet[i][j] = img.at<uchar> (i,j);
           // cout<<intervet[i][j]<<endl;
        }
    }
    img_fft(intervet);
    Mat fft_res(rsize,csize,CV_64F);
    for(int i=0;i<rsize;++i){
        for(int j=0;j<csize;++j){
            fft_res.at<double>(i,j) = sqrt(pow(intervet[i][j].real(),2)+pow(intervet[i][j].imag(),2));
        }
    }
    fft_res +=Scalar::all(1);
    log(fft_res,fft_res);
    normalize(fft_res, fft_res, 0, 1, CV_MINMAX);
    imshow("fft",fft_res);
    img_fft(intervet);
    idft_reverse(intervet);
    Mat res(rs,cs,CV_32F);
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            res.at<float>(i,j) = abs(intervet[i][j].real()/(rsize*csize));
            if(((i+j)&1)==1&&i<rs&&j<cs)
                res.at<float>(i,j) = 255 - res.at<float>(i,j);
        }
    }
    normalize(res,res,0,1,CV_MINMAX);
    imshow("res",res);
    waitKey(0);
    return 0;
}
