#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat laplans(Mat src);
int main(void) {
	Mat src, dst;
	const char input[] = "Input image";
	const char output[] = "Output image";
	src = imread("..\\girl.jpg");
	//src = imread("..\\100.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		waitKey(0);
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	dst = laplans(src);
	imshow(input, src);
	imshow(output, dst);
	waitKey(0);
	return 0;
}
Mat laplans(Mat src) {
	Mat dst_gray,dst;
	GaussianBlur(src, dst_gray, Size(3, 3), 0, 0);
	cvtColor(dst_gray, dst_gray, COLOR_BGR2GRAY);
	Laplacian(dst_gray, dst, CV_16S, 5);
	convertScaleAbs(dst, dst);
	threshold(dst, dst, 0, 255, THRESH_OTSU | THRESH_BINARY);
	//adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3,0);
	return dst;
}
