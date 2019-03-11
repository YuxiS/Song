#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
using namespace std;
using namespace cv;

int main(void) {
	Mat src, dst;
	src = imread("./girl.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		waitKey(0);
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	cvtColor(src, src, COLOR_BGR2GRAY);
	GaussianBlur(src, src, Size(3, 3), 0, 0);
	namedWindow("inputImage", WINDOW_AUTOSIZE);
	namedWindow("outputImage", WINDOW_AUTOSIZE);
	cout << src.type() << endl;
	Mat dstX, dstY;
	Sobel(src, dstX, CV_16U, 1, 0);
	Sobel(src, dstY, CV_16U, 0, 1);
	//Scharr(src, dstX, CV_16U, 1, 0);
	//Scharr(src, dstY, CV_16U, 1, 0);
	convertScaleAbs(dstX, dstX);
	convertScaleAbs(dstY, dstY);
	addWeighted(dstX, 1, dstY, 1, 0, dst);
	Mat handImage = Mat(src.size(),src.type());

	for (int i = 0; i < handImage.rows; i++) {
		for (int j = 0; j < handImage.cols; j++) {
			handImage.at<uchar>(i, j) = saturate_cast<uchar>(sqrt(dstX.at<uchar>(i, j)*dstX.at<uchar>(i, j) + dstY.at<uchar>(i, j)*dstY.at<uchar>(i, j)));
		}
	}
	imshow("handleImage", handImage);
	imshow("inputImage", src);
	imshow("outputImage", dst);
	waitKey(0);
	return 0;
}

	