#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat src, dst;
const char input[] = "Input image";
const char output[] = "Output iamge";
void traceBarDemo(int, void*);
int main(void) {
	src = imread("..//boolean.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	//pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	blur(src, src, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	int thresh = 127;
	createTrackbar("thresh", output, &thresh, 255, traceBarDemo);
	traceBarDemo(thresh, 0);
	imshow(input, src);
	waitKey(0);
	return 0;
}
void traceBarDemo(int thresh, void*) {
	src.copyTo(dst);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, gray, thresh, 255, THRESH_BINARY);
	//imshow(output, gray);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(gray, contours,hierarchy,RETR_TREE, CHAIN_APPROX_SIMPLE);

	//数组初始化
	vector<vector<Point>> ploy(contours.size());//初始化,该数组记录RPD算法筛选的点
	vector<Rect> rect_ploy(contours.size());//记录矩形的数组
	vector<RotatedRect> rotateRect_ploy(contours.size());//记录旋转矩形
	vector<RotatedRect> ellipse_ploy(contours.size());//记录椭圆的信息
	vector<Point2f> centers_circle(contours.size());//记录圆的圆心
	vector<float> radius(contours.size());//记录圆的半径
	//RNG rng(time(NULL));
	Scalar color(0, 0, 255);
	//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	for (size_t i = 0; i < contours.size(); i++){
		approxPolyDP(contours[i], ploy[i], 5, true);//epsilon表示最近两点间的距离
		rect_ploy[i] = boundingRect(ploy[i]);//得到矩形
		minEnclosingCircle(ploy[i],centers_circle[i], radius[i]);
		rotateRect_ploy[i] = minAreaRect(ploy[i]);
		if (ploy[i].size() > 5) {
			ellipse_ploy[i] = fitEllipse(ploy[i]);
		}
		//rectangle(dst, Rect_ploy[i], color, 1);
	}
	for (size_t i = 0; i < centers_circle.size(); i++){
		//circle(dst, centers_circle[i], radius[i], color, 2);
		Point2f rotateRectPoint[4];//记录旋转矩形的四个角的信息
		rotateRect_ploy[i].points(rotateRectPoint);//给四个点赋值
		for (int j = 0; j < 4; j++) {
			line(dst, rotateRectPoint[j], rotateRectPoint[(j + 1) % 4], color);
		}
		//ellipse(dst, ellipse_ploy[i], color);
	}
	imshow(output, dst);
}