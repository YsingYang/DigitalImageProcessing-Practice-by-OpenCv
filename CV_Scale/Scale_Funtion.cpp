
#include <stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("CV_Scale/82.png",0);
    cout<<"original image row:  "<<img.rows<<"   and  Cols  "<<img.cols<<endl;
    cout<<"Please input the size of image you want";
    int drow,dcol,row = img.rows,col = img.cols;
    cin>>drow>>dcol;
    cout<<drow<<dcol;
    Mat dst = Mat::zeros(drow,dcol,0);//create dst image;
    float rsc = (row-1.0)/(drow-1.0),csc = (col-1.0)/(dcol-1.0);//ration between original img and dst;
    for(int i=0;i<drow;++i){
        for(int j=0;j<dcol;++j){
                float nowi ,nowj;
                nowi = (i*rsc)-floor(i*rsc);
                nowj = (j*csc)-floor(j*csc);
                cout<<nowi<<nowj<<endl;
                int ni = i==row-1?i:i+1,nj = j==col-1?j:j+1;//取2*2矩阵 坐标分别为(i,j)(i+1,j),(i,j+1),(i+1,j+1)
                //int  intensity = (nowi - floor(nowi))*img.at<uchar>(i,j) + (abs(nowi - floor(nowi))) * img.at<uchar;
                dst.at<uchar>(i,j) = img.at<uchar>(nowi,nowj);//取对应比例下原图像素点数值
        }
    }
    cv::resize(img,dst,Size(500, 200),CV_INTER_AREA);
    imshow("img",img);
    imshow("dst",dst);
    //imwrite("CV_Scale/Down-367-298.jpg",dst);
    waitKey(0);
    return 0;

}
