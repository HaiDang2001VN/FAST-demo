#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include "FastFeatureMatcher.hpp"
#include "Pose.hpp"

using namespace cv;
using namespace std;

Mat PoseEstimator::getTransform(const vector<cv::KeyPoint>& points0,
					 const vector<cv::KeyPoint>& points1, Mat K) {
	
	cv::Mat E, R, T, Mask, Pose;
	vector<cv::Point2f> kp0, kp1;
	for (int i = 0; i < points0.size(); ++i) {
		kp0.push_back(points0[i].pt);
		kp1.push_back(points1[i].pt);
	}
	
	E = findEssentialMat(kp0, kp1, K, 8, 0.999, 1.0, Mask);
	Pose = Mat::eye(3, 4, CV_64F);

	vector<cv::Point2f> correct0, correct1;
	for (int i = 0; i < Mask.rows; ++i)
		if (Mask.at<unsigned char>(i)) {
			correct0.push_back(kp0[i]);
			correct1.push_back(kp1[i]);
		}

	Mask.release();
	recoverPose(E, kp0, kp1, K, R, T, Mask);
	R.copyTo(Pose.rowRange(0, 3).colRange(0, 3));
	T.copyTo(Pose.rowRange(0, 3).col(3));
	
	return Pose;
}

Mat PoseEstimator::getPose(Mat image0, Mat image1,
			  double fx, double fy, double cx, double cy) {
	
	Mat K = Mat::eye(3, 3, CV_32F);
	if (cx == NAN) cx = image0.size().width / 2;
	if (cy == NAN) cy = image0.size().height / 2;

	K.at<double>(0, 0) = fx;
	K.at<double>(1, 1) = fy;
	K.at<double>(0, 2) = cx;
	K.at<double>(1, 2) = cy;

	vector<KeyPoint> points0, points1;
	Ptr<FastFeatureDetector> Dect = FastFeatureDetector::create();
	Dect->detect(image0, points0);
	Dect->detect(image1, points1);

	KeyPointsFilter::retainBest(points0, 1000);
	KeyPointsFilter::retainBest(points1, 1000);

	vector<DMatch> matches = FastFeatureMatcher::match(image0, points0, image1, points1);
	vector<KeyPoint> res0(matches.size()), res1(matches.size());

	for (int i = 0; i < matches.size(); ++i) {
		res0[i] = points0[matches[i].queryIdx];
		res1[i] = points1[matches[i].trainIdx];
	}

	Mat DoF = getTransform(points0, points1, K);
	return DoF;
}