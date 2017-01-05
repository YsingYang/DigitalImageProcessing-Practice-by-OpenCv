#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){
    Mat source1 = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_enhancement/tulips.bmp",CV_LOAD_IMAGE_COLOR);

    vector<Mat> bgr_channel;
    split(source1,bgr_channel);
    int radius;
    cout<<"Please input the radius you want(int)"<<endl;
    cin>>radius;
    float sigma;
    cout<<"Please input the sigma you want (float)"<<endl;
    cin>>sigma;

    bgr_channel[0] = Guild_Filter(bgr_channel[0],bgr_channel[0],radius,sigma);
    bgr_channel[1] = Guild_Filter(bgr_channel[1],bgr_channel[1],radius,sigma);
    bgr_channel[2] = Guild_Filter(bgr_channel[2],bgr_channel[2],radius,sigma);
    Mat dst ;
    merge(bgr_channel,dst);
     int rs = source1.rows,cs = source1.cols;
    vector<vector<Vec3b>> mask(rs,vector<Vec3b> (cs));
    for(int i = 0 ;i<dst.rows;++i){
        for(int j=0;j<dst.cols;++j){
            mask[i][j] = source1.at<Vec3b> (i,j) - dst.at<Vec3b>(i,j);
            dst.at<Vec3b>(i,j) +=5*mask[i][j];
            if(dst.at<Vec3b>(i,j)[0]>255||dst.at<Vec3b>(i,j)[1]>255||dst.at<Vec3b>(i,j)[2]>255)
                cout<<dst.at<Vec3b>(i,j)<<endl;
        }
    }
    imwrite("Guilded_Filter/Tulips"+to_string(radius)+to_string(sigma)+" radius_.jpg" ,dst);
    imshow("img",source1);
    imshow("dst",dst);
    waitKey(0);
    return 0;
}

