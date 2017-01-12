#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "CV_helper/Guilded_helper.h"

using namespace std;
using namespace  cv;

int main(){

   float scale_ratio;
    cout<<"Please input the scale_ration you want(int)"<<endl;
    cin>>scale_ratio;

    int radius;
    cout<<"Please input the radius you want(int)"<<endl;
    cin>>radius;

    float sigma;
    cout<<"Please input the sigma you want (float)"<<endl;
    cin>>sigma;

    int high_boost;
    cout<<"Please input the boost you want(int)"<<endl;
    cin>>high_boost;

    int i=1;
    while(i<6){
        Mat source1 = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_enhancement/"+ to_string(i)+".bmp",CV_LOAD_IMAGE_COLOR);
        vector<Mat> bgr_channel;
        split(source1,bgr_channel);//source 为使用普通guided filter结果.

        Mat source2 = imread("/home/ysing/codeblock Projects/OpenCV/Guilded_Filter/dataset/img_enhancement/"+ to_string(i)+".bmp",CV_LOAD_IMAGE_COLOR);
        //bgr 分别做guided_filter,然后再merge为一个3通道的图片
        vector<Mat> bgr_channel2;
        split(source2,bgr_channel2);

        bgr_channel2[0] = faster_GF(bgr_channel2[0],bgr_channel2[0],radius,sigma,scale_ratio);
        bgr_channel2[1] = faster_GF(bgr_channel2[1],bgr_channel2[1],radius,sigma,scale_ratio);
        bgr_channel2[2] = faster_GF(bgr_channel2[2],bgr_channel2[2],radius,sigma,scale_ratio);
        Mat dst2;
        merge(bgr_channel2,dst2);

        bgr_channel[0] = Guild_Filter(bgr_channel[0],bgr_channel[0],radius,sigma);
        bgr_channel[1] = Guild_Filter(bgr_channel[1],bgr_channel[1],radius,sigma);
        bgr_channel[2] = Guild_Filter(bgr_channel[2],bgr_channel[2],radius,sigma);
        Mat dst ;
        merge(bgr_channel,dst);

    //以下为high - boost
        int rs = source1.rows,cs = source1.cols;
        vector<vector<Vec3b>> mask(rs,vector<Vec3b> (cs));
        vector<vector<Vec3b>> mask2(rs,vector<Vec3b> (cs));
        for(int i = 0 ;i<dst.rows;++i){
            for(int j=0;j<dst.cols;++j){
                mask[i][j] = source1.at<Vec3b> (i,j) - dst.at<Vec3b>(i,j);
                mask2[i][j] = source2.at<Vec3b> (i,j) - dst2.at<Vec3b>(i,j);
                for(int z =0 ;z<3;++z){
                    int temp1 = dst.at<Vec3b>(i,j)[z]+5*mask[i][j][z],temp2 = dst2.at<Vec3b>(i,j)[z]+5*mask2[i][j][z];
                    if(temp1>255||temp1<0){
                        temp1 = temp1>255?255:0;
                    }
                    if(temp2>255||temp2<0){
                        temp2 = temp2>255?255:0;
                    }
                    dst.at<Vec3b>(i,j)[z] = temp1;
                    dst2.at<Vec3b>(i,j)[z] = temp2;
                }

                //dst2.at<Vec3b>(i,j) += 5*mask2[i][j]
                //dst.at<Vec3b>(i,j) +=5*mask[i][j];

            }
        }

        imwrite("Guilded_Filter/result/enhancement/"+to_string(high_boost)+"_"+to_string(radius)+"_"+to_string(sigma)+"/"+to_string(i)+ ".jpg" ,dst);
        imwrite("Guilded_Filter/result/enhancement/"+to_string(high_boost)+"_"+to_string(radius)+"_"+to_string(sigma)+"/"+"fast_" + to_string(i)+ ".jpg" ,dst2);
        ++i;
    }
    //imshow("img",source1);
    //imshow("dst",dst);
    waitKey(0);
    return 0;
}

