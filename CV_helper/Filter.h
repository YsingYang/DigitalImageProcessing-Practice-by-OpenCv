#include<stdio.h>
#include<iostream>
#include<vector>
#include<complex.h>
#include<bitset>
#include <limits.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


Mat arithmetic_MF(const Mat &img,int rz,int cz){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin>>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin>>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            float intensity =0.0;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends&&intensity!=-1;++u){
                for(int v= cstart;v<=cends&&intensity!=-1;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    intensity += img.at<uchar>(nowu,nowv);
                }
            }
            intensity = intensity *1.0/(rz*cz);
            dst.at<uchar>(i,j) = (int)intensity;
        }
    }
    return dst;
}

Mat harmonic_MF(const Mat &img,int rz,int cz){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin >>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin >>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            float intensity =0.0;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends&&intensity!=-1;++u){
                for(int v= cstart;v<=cends&&intensity!=-1;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    if(img.at<uchar>(nowu,nowv)==0)
                        intensity = -1;

                    else
                        intensity += 1.0/img.at<uchar>(nowu,nowv);
                }
            }
            dst.at<uchar>(i,j) = (intensity==-1)? 0:(rz*cz)/intensity;
        }
    }
    return dst;
}


Mat contraharmonic_MF(const Mat &img,int rz,int cz,float Q){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin >>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin >>cz;
    }
    cout<<"Q parameter is "<<Q<<endl;
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            float intensity_m =0.0,intensity_n=0.0;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends&&intensity_n!=-1;++u){
                for(int v= cstart;v<=cends&&intensity_n!=-1;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    if(Q<-1&&img.at<uchar>(nowu,nowv)==0)
                        intensity_m =-1;
                    else
                        intensity_m += pow(img.at<uchar>(nowu,nowv),Q+1);
                   if(Q<0&&img.at<uchar>(nowu,nowv)==0){
                        intensity_n=-1;
                    }
                    else{
                        intensity_n += pow(img.at<uchar>(nowu,nowv),Q);
                    }
                }
            }
            //cout<<intensity_m<<"   "<<intensity_n<<endl;
            dst.at<uchar>(i,j) =intensity_n==-1?0: (int)(intensity_m*1.0/intensity_n);
        }
    }
    return dst;
}

Mat geometric_MF(const Mat &img,int rz,int cz){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin >>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin >>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            float intensity =0.0;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends&&intensity!=-1;++u){
                for(int v= cstart;v<=cends&&intensity!=-1;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    intensity += log(img.at<uchar>(nowu,nowv));
                }
            }
            intensity /= (rz*cz*1.0);
            intensity = exp(intensity);
            if(intensity>255)   intensity=255;
           dst.at<uchar>(i,j)  = (int)intensity;
        }
    }
    return dst;
}

Mat median_MF(const Mat &img,int rz,int cz){
    while((rz&1)==0){
        cout<<"Please input a odd number";
        cin >>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin >>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            vector<uchar> median;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends;++u){
                for(int v= cstart;v<=cends;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    median.push_back(img.at<uchar>(nowu,nowv));
                }
            }
            sort(median.begin(),median.end());
            dst.at<uchar>(i,j) = median[(rz*cz)>>1];
        }
    }
    return dst;
}

Mat min_MF(const Mat &img,int rz,int cz){
     while((rz&1)==0){
        cout<<"Please input a odd number";
        cin >>rz;
    }
    while((cz&1)==0){
        cout<<"Please input a odd number";
        cin >>cz;
    }
    int rs = img.rows,cs =img.cols;
    Mat dst(rs,cs,CV_8UC1);//new dst_img

    for(int i=0;i<rs;++i){
        for(int j=0;j<cs;++j){
            int min_intensity =INT_MAX;
            int rstart = i - (rz>>1),rends = i+(rz>>1);
            int cstart = j- (cz >>1),cends = j+(cz>>1);
            for(int u=rstart;u<=rends;++u){
                for(int v= cstart;v<=cends;++v){
                    int nowu = u<0?rs+u:(u>=rs?u-rs:u);
                    int nowv = v<0?cs+v:(v>=cs?v-cs:v);
                    min_intensity = min(min_intensity,(int)img.at<uchar>(nowu,nowv));
                }
            }
            dst.at<uchar>(i,j) = min_intensity;
        }
    }
    return dst;
}
