#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src, dst;
const char input[] = "Imput image";
const char output[] = "Output image";
void traceBarDemo(int, void*);
int main(void) {
	src = imread("..\\girl.jpg");
	if (src.empty()) {
		cout << "Loading image error！" << endl;
		return -1;
	}
	pyrDown(src, src, Size(src.cols/2, src.rows/2));
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	int a = 1;
	createTrackbar("case", output, &a, 3, traceBarDemo);
	traceBarDemo(a, 0);
	imshow(input, src);
	waitKey(0);
}
void traceBarDemo(int a, void*) {
	Mat map_x, map_y;
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	switch (a) {
		case 0://左右翻转
			for (int i = 0; i < src.rows; i++) {
				for (int j = 0; j < src.cols; j++) {
					map_x.at<float>(i, j) = src.cols  - j-1;
					map_y.at<float>(i, j) = i;
				}
			}
			break;
		case 1://上下翻转
			for (int i = 0; i < src.rows; i++) {
				for (int j = 0; j < src.cols; j++) {
					map_x.at<float>(i, j) = j;
					map_y.at<float>(i, j) = src.rows  - i-1;
				}
			}
			break;
		case 2://旋转180度
			for (int i = 0; i < src.rows; i++) {
				for (int j = 0; j < src.cols; j++) {
					map_x.at<float>(i, j) = src.rows - j-0.5;
					map_y.at<float>(i, j) = src.cols - i-0.5;
				}
			}
			break;
		case 3://左右翻转
			for (int i = 0; i < src.rows; i++) {
				for (int j = 0; j < src.cols; j++) {
					if (i > src.rows / 4 && i<src.rows * 3 / 4 && j>src.cols / 4 && j < src.cols * 3 / 4) {
						map_x.at<float>(i, j) = 2*j-src.cols/2;
						map_y.at<float>(i, j) = 2*i-src.rows/2;
					}
					else{
						map_x.at<float>(i, j) = 0 ;
						map_y.at<float>(i, j) = 0 ;
					}
				}
			}
	}
	remap(src, dst, map_x, map_y, INTER_LINEAR, 0, Scalar(0, 0, 255));
	imshow(output, dst);
}