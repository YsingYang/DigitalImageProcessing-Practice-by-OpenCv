#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
#include"CV_helper/Histogram.h"

using namespace std;
using namespace cv;


int main(){
    const double PI=3.1415926;
    Mat img = imread("CV_DFT/82.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    int r = img.rows,c = img.cols;
    vector<vector<complex<double> > > comp(r,vector<complex<double> > (c));
   // vector<vector<double>>  dst(r,vector<double> (c));
    Mat dst(r,c,CV_64FC1,0.0);
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            img.at<uchar> (i,j) *=pow(-1,i+j);
        }
    }
    for(int u=0;u<r;++u){
        for(int v=0;v<c;++v){
            complex<double> temp (0.0,0.0) ;
            for(int i=0;i<r;++i){
                for(int j=0;j<c;++j){
                    double part = u*i*1.0/r+v*j*1.0/c;
                    complex<double> e = exp (complex<double>(0.0,-2*PI*part));
                    //double t = ((i+j)%2)==0?255-img.at<uchar>(i,j) : img.at<uchar>(i,j);
                    temp +=e*(double)img.at<uchar>(i,j);
                }
            }
            comp[u][v] = temp;
            dst.at<double> (u,v) =   (double) sqrt((temp.real(),2)+pow(temp.imag(),2));
        }
        cout<<u<<endl;
    }
    dst += Scalar::all(1.0);
    log(dst,dst);
    normalize(dst, dst, 0, 1,CV_MINMAX);
    imshow("dst",dst);
    Mat dst_to_img(r,c,CV_64FC1,Scalar(0.0));
    //vector<vector<complex<double> > > dst_to_img (r,vector<complex<double> > (c));
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            complex<double> temp (0.0,0.0);
            for(int u =0 ;u<r;++u){
                for(int v=0;v<c;++v){
                    double part = u*i*1.0/r+v*j*1.0/c;
                    complex<double> e = exp (complex<double>(0,2*PI*part));
                    temp += comp[u][v]*e;
                }
            }
            dst_to_img.at<double>(i,j) =abs(temp.real())*pow(-1,i+j) /(r*c);
            //cout<<sqrt((dst_to_img[i][j].real(),2)+pow(dst_to_img[i][j].imag(),2))<<endl;
            //res.at<uchar> (i,j) =  (int)sqrt((dst_to_img[i][j].real(),2)+pow(dst_to_img[i][j].imag(),2));
        }
    }
    normalize(dst_to_img,dst_to_img,0,1,CV_MINMAX);
    imshow("'res",dst_to_img);
    imwrite("res.jpg",dst_to_img);
    waitKey(0);
    return 1;
}
