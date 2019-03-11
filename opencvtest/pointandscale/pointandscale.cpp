// pointandscale.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void paintLine(Mat image);
void paintCircle(Mat image);
void paintRect(Mat image);
//void paintPloygen(Mat image);
void paintEllipse(Mat image);
void paintRandomLine(Mat image);
int main()
{
    std::cout << "Hello World!\n"; 
	Mat image1;
	image1 = imread("./timg.jpg");
	if (image1.empty()) {
		cout << "load image failed!" << endl;
		system("pause");
		return -1;
	}
	//paintLine(image1);
	paintRect(image1);
	paintCircle(image1);
	namedWindow("rose2", WINDOW_AUTOSIZE);
	paintEllipse(image1);
	imshow("rose2", image1);
	
	waitKey(0);
	//paintRandomLine(image1);
	
}
void paintLine(Mat image) {
	Point a(100, 100);
	Point b(300, 300);
	Scalar color(0, 0, 255);
	line(image, a, b, color, 2, LINE_8);
}
void paintCircle(Mat image) {
	Point a(100, 100);
	Point b(300, 300);
	Scalar color(0, 255, 255);
	circle(image, Point(image.rows / 2, image.cols / 2), 100, color, 1, LINE_8);
}
void paintRect(Mat image) {
	Point a(100, 100);
	Point b(400, 400);
	Scalar color=Scalar(0, 255, 0);
	Rect rec(100,100,400,400);
	rectangle(image, rec, color, 2, LINE_AA);
}
void paintRandomLine(Mat image) {
	RNG rng(time(NULL));
	Mat image2 = image.zeros(image.size(), image.type());
	namedWindow("background", WINDOW_AUTOSIZE);
	for (int i = 0;  i < 10000;  i++){
		Point a(rng.uniform(0, image.cols), rng.uniform(0, image.rows));
		Point b(rng.uniform(0, image.cols), rng.uniform(0, image.rows));
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		line(image2, a, b, color, 1, LINE_8);
		imshow("background", image2);
		if (waitKey(10) > 0) {
			return;
		}
	}
}
void paintEllipse(Mat image) {
	Scalar color(0, 0, 234);
	ellipse(image, Point(image.cols / 2, image.rows / 2), Size(400, 200),0,0,360,color,1,LINE_AA);
	ellipse(image, Point(image.cols / 2, image.rows / 2), Size(400, 200), 45, 0, 360, color, 1, 8);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单


// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
