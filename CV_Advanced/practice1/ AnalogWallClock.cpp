#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <ctime>
#include <sys/timeb.h>
using namespace std;
using namespace cv;

int main()
{
Mat clk(640,640,CV_8UC3); //Mat to store clock image
Mat back_up(640,640,CV_8UC3); //Mat to store backup image

Point cent(320,320);
Point perim(0,0);
int rad =320;
float sec_angle,min_angle,hour_angle;



//Draw second markings
int s1[60][2];
for (int i=0; i<60; i++)
          for (int j=0; j<2; j++)
                   if(j%2==0)
                   s1[i][j]=320+295*cos(6.0*i*3.14/180) ;
                   else
                   s1[i][j]=320+295*sin(6.0*i*3.14/180);

int s2[60][2];
for (int i=0; i<60; i++)
          for (int j=0; j<2; j++)
                   if(j%2==0)
                   s2[i][j]=320+315*cos(6.0*i*3.14/180) ;
        else
        s2[i][j]=320+315*sin(6.0*i*3.14/180);

for(int i=0;i<60;i++){
    line(clk,Point(s1[i][0],s1[i][1]),Point(s2[i][0],s2[i][1]), Scalar(0,255,0,0), 1.5,CV_AA,0);
}


//Draw hour markings
int h1[12][2];
for (int i=0; i<12; i++)
          for (int j=0; j<2; j++)
                   if(j%2==0)
                   h1[i][j]=320+275*cos(30.0*i*3.14/180) ;
                   else
                   h1[i][j]=320+275*sin(30.0*i*3.14/180);

int h2[12][2];
for (int i=0; i<12; i++)
          for (int j=0; j<2; j++)
                   if(j%2==0)
                   h2[i][j]=320+315*cos(30.0*i*3.14/180) ;
        else
        h2[i][j]=320+315*sin(30.0*i*3.14/180);
for(int i=0;i<12;i++){
    line(clk,Point(h1[i][0],h1[i][1]),Point(h2[i][0],h2[i][1]), Scalar(0,255,0,0), 4,CV_AA,0);
}

circle(clk,cent,rad-5,Scalar(0,0,255,0),4,CV_AA,0); //Draw outercircle of clock
circle(clk,cent,1,Scalar(0,255,0,0),5,CV_AA,0);        //Draw inner circle

back_up=clk.clone();                                                  // Clone to backup image

time_t rawtime;
struct tm * timeinfo;
float second;
float minute;
float hour;
float millisec;
struct timeb tmb;


while(1){
//Access system time and store it to a local variable
    ftime(&tmb);
    rawtime=tmb.time;
    timeinfo = localtime ( &rawtime );

    second     = timeinfo->tm_sec;
    minute     = timeinfo->tm_min;
    hour       = timeinfo->tm_hour;
    millisec   = tmb.millitm;


    second=second+millisec/1000;
    sec_angle=(second*6)+270;                     //Convert second to angle

   minute=minute+second/60;
   min_angle=minute*6+270;                        //Convert minute to angle

  if(hour>12)hour = hour-12;
   hour_angle=(hour*30)+(minute*.5)+270;  //Convert hour to angle


   if(sec_angle>360)sec_angle=sec_angle-360;
   if(min_angle>360)min_angle=min_angle-360;
   if(hour_angle>360)hour_angle=hour_angle-360;

//Find out the co-ordinates in the circle perimeter for second and draw the line from center
perim.x =  (int)(cent.x + (rad-5) * cos(sec_angle * CV_PI / 180.0));
perim.y =  (int)(cent.y + (rad-5) * sin(sec_angle * CV_PI / 180.0));
line(clk,cent,perim, Scalar(0,255,255,0), 1.5,CV_AA,0);


//Find out the co-ordinates on the circle perimeter for minute and draw the line from center
perim.x =  (int)(cent.x + (rad-50) * cos(min_angle * CV_PI / 180.0));
perim.y =  (int)(cent.y + (rad-50) * sin(min_angle * CV_PI / 180.0));
line(clk,cent,perim, Scalar(0,255,255,0), 4,CV_AA,0);


//Find out the co-ordinates on the circle perimeter for hour and draw the line from center
perim.x =  (int)(cent.x + (rad-75) * cos(hour_angle * CV_PI / 180.0));
perim.y =  (int)(cent.y + (rad-75) * sin(hour_angle * CV_PI / 180.0));
line(clk,cent,perim, Scalar(0,255,255,0), 8,CV_AA,0);


imshow("Clock",clk);  //Show result in a window
clk.setTo(0);                // set clk image to zero for next drawing
clk=back_up.clone();  // Clone the previously drawned markings from back-up image

char c=waitKey(10);   // Wait for few millisecond and go back to loop.
if(c==27)break;
}

    return 0;
}
