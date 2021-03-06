// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Pose.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat Img0 = imread("Images/Data/0.jpg", IMREAD_COLOR);
	Mat Img1 = imread("Images/Data/1.jpg", IMREAD_COLOR);
	Mat Pose = PoseEstimator::getPose(Img0, Img1);
	
	printf("%lf", Pose.at<uchar>(0, 0));
	waitKey();
	return 0;
}