#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat src, temp;
const char input[] = "Input image";
const char output[] = "Output image";
void matchDemo(int, void*);
int method = 1;
const int method_max = 5;
int main(void) {
	src = imread("..\\girl.jpg");
	temp = imread("..\\girl_template.jpg");
	if (temp.empty() || src.empty()) {
		cout << "Loading image failed!" << endl;
		return - 1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	pyrDown(temp, temp, Size(temp.cols / 2, temp.rows / 2));
	namedWindow(input, WINDOW_AUTOSIZE);
	//namedWindow(output, WINDOW_AUTOSIZE);
	createTrackbar("method", input, &method, method_max, matchDemo);
	matchDemo(0, 0);
	//imshow(input, src);
	//imshow(output, temp);
	waitKey(0);
	return 0;
}
void matchDemo(int, void*) {
	Mat result, dst;
	src.copyTo(dst);
	//result初始化很重要,长宽必须符合标准
	result.create(Size(src.cols - temp.cols + 1, src.rows - temp.rows + 1), CV_32FC1);
	matchTemplate(src, temp, result, method, Mat());
	double min, max;//纪录匹配结果，即记录在result中的结果
	Point pointMax, pointMin, pointLast;
	minMaxLoc(result, &min, &max, &pointMin, &pointMax, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX);
	cout << "Min:" << min << endl;
	cout << "Max:" << max << endl;
	if (method == TM_SQDIFF && method == TM_SQDIFF_NORMED){
		pointLast = pointMax;
	}
	else {
		pointLast = pointMin;
	}
	rectangle(dst, Rect(pointLast.x, pointLast.y, temp.cols, temp.rows), Scalar(0, 255, 0), 2);
	rectangle(result, Rect(pointLast.x, pointLast.y, temp.cols, temp.rows), Scalar(0, 255, 0), 2);
	//imshow(output, result);
	imshow(input, dst);
}
