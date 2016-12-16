#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;


int main(){
    const double PI=3.14;
    Mat img = imread("CV_DFT/82.png",CV_LOAD_IMAGE_GRAYSCALE);
    Mat dst = Mat::zeros(img.rows,img.cols,0);
    int r = img.rows,c = img.cols;
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            img.at<uchar>(i,j) *= pow(-1,i+j);
        }
    }
    vector<vector<complex<double> > > comp(r,vector<complex<double> > (c));
    for(int u=0;u<dst.rows;++u){
        for(int v=0;v<dst.cols;++v){
            complex<double> temp (0.0,0.0) ;
            for(int i=0;i<img.rows;++i){
                for(int j=0;j<img.cols;++j){
                    double part = u*i/r+v*j/c;
                    complex<double> e = exp (complex<double>(0,-1*2*PI*part));
                    temp +=e;
                }
            }
            temp /= r*c;
            comp[u][v] = temp;
            dst.at<uchar>(u,v) = (uchar) (sqrt(pow(temp.real(),2)+pow(temp.imag(),2)));
        }
        cout<<u<<endl;
    }
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            cout<<(int)dst.at<uchar>(i,j)<<"   ";
        }
        cout<<endl;
    }
    imshow("dst",dst);
    imwrite("CV_DFT/dft.jpg",dst);
    waitKey(0);
    return 1;
}
