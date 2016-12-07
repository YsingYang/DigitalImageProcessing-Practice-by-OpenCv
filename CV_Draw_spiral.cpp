//Opencv Code for Spiral Effect
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
int main( )
{
 // Create black empty images
 Mat image = Mat::zeros( 500, 500, CV_8UC3 );
 //Factor by which u need to increase the radius
 int x=5;

 for(int i=x;i<=250;i=i+x)
 {
  if(i%(2*x)==0){
 // Draw a ellipse
 ellipse( image, Point( 250+x, 250 ), Size( i, i ), 180, 180, 0, Scalar( 0, 255,255 ), 2, 8 );
 imshow("Image",image);
 waitKey( 100 );
  }
  else
  {
 ellipse( image, Point( 250, 250 ), Size( i, i ), 0, 0, 180, Scalar( 0, 255,255 ), 2, 8 );
 imshow("Image",image);
 waitKey( 100 );

  }
 }
 waitKey( 0 );

 return(0);
}
