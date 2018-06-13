// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace cv;

int main()
{
	Ptr<FastFeatureDetector> Dect = FastFeatureDetector::create(15);
	vector<KeyPoint> Keys;

	const int TEST = 1180348 - 1180141;
	const clock_t Begin = clock();
	for (int i = 1180141; i < 1180348; ++i)
	{
		Mat Img = imread("Images/P" + to_string(i) + ".JPG", IMREAD_COLOR);
		Dect->detect(Img, Keys);
		printf("%d\n", i);
	}
	printf("%.3f\n%d", (double(clock() - Begin) / CLOCKS_PER_SEC) / TEST, TEST);

	waitKey();
	return 0;
}

