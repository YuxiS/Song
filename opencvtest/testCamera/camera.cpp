#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	VideoCapture camera;
	camera.open(0);
	if (!camera.isOpened()) {
		cout << "camera open failed!" << endl;
		waitKey(0);
		return -1;
	}
	Mat type;
	while (1) {
		camera >> type;
		if (type.empty()) {
			cout << "convery Image failed!" << endl;
			waitKey(0);
			return -2;
		}
		Mat gray;
		GaussianBlur(type, gray, Size(3, 3), 0, 0);
		cvtColor(gray, gray, COLOR_BGR2GRAY);
		Mat gray_x, gray_y;
		Sobel(gray, gray_x, CV_16S, 0, 1);
		Sobel(gray, gray_y, CV_16S, 1, 0);
		convertScaleAbs(gray_x, gray_x);
		convertScaleAbs(gray_y, gray_y);
		addWeighted(gray_x, 1, gray_y, 1, 0, gray);
		threshold(gray, gray, 0, 255, THRESH_OTSU | THRESH_BINARY);
		namedWindow("input", WINDOW_AUTOSIZE);
		namedWindow("output", WINDOW_AUTOSIZE);
		imshow("input", type);
		imshow("output", gray);
		if (waitKey(10)>0) {
			break;
		}
	}
	return 0;
}