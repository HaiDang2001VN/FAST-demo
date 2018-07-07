#pragma once 
#include <opencv2/opencv.hpp>
#include <vector>

namespace PoseEstimator{
	cv::Mat getTransform(const std::vector<cv::KeyPoint>&, const std::vector<cv::KeyPoint>&, cv::Mat K);
	cv::Mat getPose(cv::Mat image0, cv::Mat image1,
				  double fx = 500, double fy = 500, double cx = NAN, double cy = NAN);
};