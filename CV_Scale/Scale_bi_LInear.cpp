
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
    cin>>drow;
    cin>>dcol;//输入需要调整的大小
    cout<<drow<<dcol;
    Mat dst = Mat::zeros(drow,dcol,0);//create dst image;
    float rsc = (row-1.0)/(drow-1.0),csc = (col-1.0)/(dcol-1.0);//ration between original img and dst;
    cout<<rsc<<"  "<<csc<<endl;
    for(int i=0;i<drow;++i){
        for(int j=0;j<dcol;++j){
                int match_i = (i*rsc),match_j =(j*csc);// i ,j 在原图中对应的index;
                double  i_rate,j_rate;
                 i_rate = ((double)i*rsc)-floor((double)i*rsc);//线性比例
                j_rate = ((double)j*csc)-floor((double)j*csc);
                //cout<<j_rate<<endl;
                int ni = match_i>=row-1?match_i:match_i+1,nj = match_j>=col-1?match_j:match_j+1;//取2*2矩阵 坐标分别为(i,j)(i+1,j),(i,j+1),(i+1,j+1)
                double intensity = (i_rate *j_rate) * img.at<uchar>(match_i,match_j) + ((1-i_rate)*j_rate) * img.at<uchar>(ni,match_j);//
                intensity += (i_rate *(1-j_rate))*img.at<uchar>(match_i,nj)+((1-i_rate)*(1-j_rate))*img.at<uchar>(ni,nj);
                if(intensity>255)   intensity=255;
                dst.at<uchar>(i,j) = (int)intensity;//取对应比例下原图像素点数值
        }
    }
    imshow("img",img);
    imshow("dst",dst);
   // imwrite("CV_Scale/Scale-367-298.jpg",dst);
    waitKey(0);
    return 0;

}

