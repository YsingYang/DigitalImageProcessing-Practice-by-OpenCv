
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

int main()
{
  Mat image1 = imread( "CV_Advanced/Test2.jpg", CV_LOAD_IMAGE_COLOR );

  if( !image1.data)
  {
   cout<< " --(!) Error reading images " << endl;
   return -1;
  }

  //-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 100;
  SurfFeatureDetector detector( minHessian);
  std::vector<KeyPoint> keypoints_1;
  detector.detect( image1, keypoints_1 );

  //--Step2: Draw keypoints
  Mat img_keypoints_surf;
  drawKeypoints( image1, keypoints_1, img_keypoints_surf, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

  //--Step3: Show detected (drawn) keypoints
  imshow("Keypoints 1", img_keypoints_surf );
  waitKey(0);

  return 0;
  }
