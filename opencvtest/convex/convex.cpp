#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat src, dst;
const char input[] = "Input image";
const char output[] = "Output image";
void traceDemo(int, void*);
int main(void){
	src = imread("..\\fish.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	//src.copyTo(dst);
	
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	int thresh = 100;
	createTrackbar("shresh", output, &thresh, 255, traceDemo);
	traceDemo(thresh, 0);
	imshow(input, src);
	waitKey(0);
	return 0;
}
void traceDemo(int thresh, void*) {
	dst = Mat::zeros(src.size(), CV_8UC3);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, gray, Size(3, 3));
	threshold(gray, gray, thresh, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> hull(contours.size());
	for (size_t i = 0; i < contours.size(); i++){
		convexHull(contours[i], hull[i], false);
	}
	RNG rng;
	for (size_t i = 0; i < contours.size(); i++){
		//convexHull()
		drawContours(dst, contours, i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_AA, hierarchy, 0);
		drawContours(dst, hull, i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_AA, hierarchy, 0);
	}
	imshow(output, dst);
}