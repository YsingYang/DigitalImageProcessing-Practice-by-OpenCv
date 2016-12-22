#include<opencv2/opencv.hpp>
#include<math.h>
#include<vector>
#include<CV_helper/RGB_2_HSI.h>
using namespace std;
using namespace cv;

//-------------------------- RGB 模型 转换为 HSI 模型--------------------//
int main(){
    Mat LeafBGRImage = imread("CV_RGB/82.png",CV_LOAD_IMAGE_COLOR);
    Mat LeafHSIImage = Mat(Size(LeafBGRImage.cols, LeafBGRImage.rows), CV_8UC3);

    vector <Mat> channels;
    split(LeafHSIImage, channels);
    Mat Hvalue = channels.at(0);
    Mat Svalue = channels.at(1);
    Mat Ivalue = channels.at(2);

    for (int i = 0; i < LeafBGRImage.rows; ++i)
        for (int j = 0; j < LeafBGRImage.cols; ++j)
        {
            double H, S, I;
            int Bvalue = LeafBGRImage.at<Vec3b>(i, j)(0);
            int Gvalue = LeafBGRImage.at<Vec3b>(i, j)(1);
            int Rvalue = LeafBGRImage.at<Vec3b>(i, j)(2);

            //求Theta =acos((((Rvalue - Gvalue) + (Rvalue - Bvalue)) / 2) / sqrt(pow((Rvalue - Gvalue), 2) + (Rvalue - Bvalue)*(Gvalue - Bvalue)));
            double numerator = ((Rvalue - Gvalue) + (Rvalue - Bvalue)) / 2;
            double denominator = sqrt(pow((Rvalue - Gvalue), 2) + (Rvalue - Bvalue)*(Gvalue - Bvalue));
            if (denominator == 0) H = 0;
            else{
                double Theta = acos(numerator / denominator) * 180 / 3.14;
                if (Bvalue <= Gvalue)
                     H = Theta;
                else  H = 360 - Theta;
            }
            Hvalue.at<uchar>(i, j) = (int)(H * 255 / 360); //为了显示将[0~360]映射到[0~255]

            //求S = 1-3*min(Bvalue,Gvalue,Rvalue)/(Rvalue+Gvalue+Bvalue);
            int minvalue = Bvalue;
            if (minvalue > Gvalue) minvalue = Gvalue;
            if (minvalue > Rvalue) minvalue = Rvalue;
            numerator = 3 * minvalue;
            denominator = Rvalue + Gvalue + Bvalue;
            if (denominator == 0)  S = 0;
            else{
                S = 1 - numerator / denominator;
            }
            Svalue.at<uchar>(i, j) = (int)(S * 255);//为了显示将[0~1]映射到[0~255]

            I= (Rvalue + Gvalue + Bvalue) / 3;
            Ivalue.at<uchar>(i, j) = (int)(I);
        }

    merge(channels, LeafHSIImage);
    namedWindow("HSI");
    imshow("HSI", LeafHSIImage);
    hsi2bgr2(LeafBGRImage,LeafHSIImage);
    imshow("RGB",LeafBGRImage);

    waitKey(6000);
    return 0;
}
