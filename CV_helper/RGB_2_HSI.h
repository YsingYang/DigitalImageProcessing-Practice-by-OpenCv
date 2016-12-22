#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<math.h>
#include<cstdlib>
#include <unistd.h>

using namespace std;
using namespace  cv;

void reHsi (const Mat &img,Mat &hsi){
    int rs = img.rows,cs = img.cols;
    float h=0.0,s=0.0,intensity=0.0,r,g,b;
    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            b = img.at<Vec3b>(i,j)[0] ;
            g = img.at<Vec3b>(i,j)[1];
            r = img.at<Vec3b>(i,j)[2];
            intensity = (b+g+r)/3.0;
            s= ((r+g+b)==0||(r==g&&g==b)) ? 0:1-(3.0*min(r,min(g,b)))/(r+g+b);
            float temp = 2*sqrt(pow(r-g,2)+(r-b)*(g-b));//分母不能为0,为0时则H为0;

            h =((temp==0)||(r==g&&g==b))?0: acos(((r-g)+(r-b))/temp*1.0);
            h *= (180/M_PI);
            if(b>g){
                h = 360 - h;//将h 值域先定位0~360;
            }
            hsi.at<Vec3b>(i,j)[0] = (int) (h*(255.0/360));
            hsi.at<Vec3b>(i,j)[1] =  (int) (s*255); //s值域为0~1;
            hsi.at<Vec3b>(i,j)[2] = (int) (intensity);
             //cout<<(int)hsi.at<Vec3b>(i,j)[0]<<endl;
        }
    }
}

void hsi2bgr(Mat &img,const Mat &hsi){
     float tempr,tempg,tempb,h,s,it;
     for(int i=0;i<hsi.rows;++i){
        for(int j=0;j<hsi.cols;++j){
            h = hsi.at<Vec3b>(i,j)[0]*360/255.0;
            s = hsi.at<Vec3b>(i,j)[1]/255.0;
            it = hsi.at<Vec3b>(i,j)[2]/255.0;
            //cout<<h<<"    "<<"    "<<s <<"     "<<i<<"    "<<endl;
             if(s>1) s=1;
            if(it>1) it=1;
            if(s==0){
                img.at<Vec3b>(i,j)[0] = (int)(it*255);
                img.at<Vec3b>(i,j)[1] = (int)(it *255);
                img.at<Vec3b>(i,j)[2] = (int)(it *255);
                cout<<(int)(it*255)<<endl;
            }
            else{if(h<120){//rg空间
                h = h * M_PI /180;//将值域转为[0,2PI];
                tempb = it *(1-s);//  可能有问题
                tempr =  it * (1+(s * cos(h)/cos(M_PI/3-h)));
                tempg = 3 *it -tempb - tempr;
            }
            else if(h<240&&h>=120){
                h-=120;
                h*=M_PI/180;

                tempr = it *(1-s);
                tempg = it * (1+(s * cos(h)/cos(M_PI/3-h)));
                tempb = 3 * it -tempr -tempg;
            }
            else{
                h -=240;
                h *= M_PI/180;
                tempg = it * (1-s);
                tempb = it * (1+(s * cos(h)/cos(M_PI/3-h)));
                tempr = 3*it -tempg - tempb;
            }
             if(tempb>1) tempb =1;
            if(tempr>1) tempr =1;
            if(tempg>1) tempg =1;
            //cout<<tempb<<"   "<<tempg<<"   "<<tempr<<endl;
            img.at<Vec3b>(i,j)[0] = (int)(tempb *255);
            img.at<Vec3b>(i,j)[1] = (int)(tempg *255);
            img.at<Vec3b>(i,j)[2] = (int)(tempr *255);
        //   cout<<(int)(tempb *255)<< "    "<<(int)(tempg *255)<<"     "<<(int)(tempr *255)<<endl;
            }
        }
     }
}

/*void hsi2bgr2(Mat &img,Mat &hsi){
     float tempr,tempg,tempb,h,s,it;
     for(int i=0;i<hsi.rows;++i){
        for(int j=0;j<hsi.cols;++j){
            h = hsi.at<Vec3b>(i,j)[0];
            s = hsi.at<Vec3b>(i,j)[1]/255.0;
            it = hsi.at<Vec3b>(i,j)[2]/255.0;
            if(s>1) s=1;
            if(it>1) it=1;
            if(s==0){
                img.at<Vec3b>(i,j)[0] = (int)(it*255);
                img.at<Vec3b>(i,j)[1] = (int)(it *255);
                img.at<Vec3b>(i,j)[2] = (int)(it *255);
            }
            else{

                if(h>=0&&h<120){//rg空间
                    h = h * M_PI /180.0;//将值域转为[0,2PI];
                    tempb = (1-s)/3.0;//  可能有问题
                    tempr =  (1+(s * cos(h)/cos(M_PI/3-h)))/3.0;
                    tempg =  1 -tempb - tempr;
                }
                else if(h<240&&h>=120){
                    h-=120;
                    h*=M_PI/180.0;

                    tempr = (1-s)/3.0;
                    tempg = (1+(s * cos(h)/cos(M_PI/3-h)))/3.0;
                    tempb = 1 -tempr - tempg;
                }
                else if(h>=240&&h<360){
                    h -=240;
                    h *= M_PI/180.0;
                    tempg = (1-s)/3.0;
                    tempb = (1+(s * cos(h)/cos(M_PI/3-h)))/3.0;
                    tempr = 1 -tempg - tempb;
                }
                else {
                    cout<<"h out of range "<<endl;
                    system("PAUSE");
                }
                if(tempr<0) tempr=0;
                if(tempg<0) tempg=0;
                if(tempb<0) tempb =0;
                tempb *= 3*it;
                tempg *= 3*it;
                tempr *= 3*it;
                if(tempb>1) tempb =1;
                if(tempr>1) tempr =1;
                if(tempg>1) tempg =1;
                //cout<<tempb<<"   "<<tempg<<"   "<<tempr<<endl;
                img.at<Vec3b>(i,j)[0] = (int)(tempb *255);
                img.at<Vec3b>(i,j)[1] = (int)(tempg *255);
                img.at<Vec3b>(i,j)[2] = (int)(tempr *255);
            }
        }
     }
}*/
