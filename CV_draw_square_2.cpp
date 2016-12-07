#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main(){
    Mat image = Mat::zeros(500,500,CV_8UC3);
    int count = 0,a,b=250,i,j;
    int p = 0, q=1;
    for(a=250;a<500&&a>0;){
        ++count;
        if((count&1)!=0){
            ++p;
            j=b;
            if(p&1){
                i=a+5*count;
            }
            else{
                i=a-5*count;
            }//x Axis line;
        }
        else{
                q++;
                i=a;
                if(!(q&1)){
                        j = b+5*count;
                }
                else{
                        j = b - 5 * count;
                }//y Axis line;
        }
        line (image , Point(a,b),Point(i,j),Scalar(255,255,0),2,8);
        imshow("Image",image);
        waitKey(100);//等待时间
        a=i;
        b=j;
    }
    imwrite("Square_spiral.jpg",image);
    waitKey(0);
    return 1;
}

