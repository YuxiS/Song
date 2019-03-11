// threshold.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat right_image;
Mat output_image;
int threshold_type;
void traceBarDemo1(int, void*);
//void traceBarDemo2(int, void*);
const char output[] = "Output image";
int main()
{
    std::cout << "Hello World!\n";
	Mat image = imread("./girl.jpg");
	if (image.empty() == true) {
		cout << "Loading image failed!";
		system("pause");
		return -1;
	}
	namedWindow("orignal image", WINDOW_AUTOSIZE);
	pyrDown(image, right_image, Size(image.cols / 2, image.rows / 2));
	cvtColor(right_image, right_image, COLOR_BGR2GRAY);
	imshow("orignal image", right_image);
	namedWindow(output, WINDOW_AUTOSIZE);
	int shold = 127;
	createTrackbar("thersh_type", output, &threshold_type, 4, traceBarDemo1);
	createTrackbar("thresh", output,&shold , 255, traceBarDemo1);
	traceBarDemo1(shold, 0);
	waitKey(0);
} 
void traceBarDemo1(int thresh, void*) {
	switch(threshold_type){
		case 0:
			threshold(right_image, output_image, thresh, 255, THRESH_BINARY);
			break;
		case 1:
			threshold(right_image, output_image, thresh, 255, THRESH_BINARY_INV);
			break;
		case 3:
			threshold(right_image, output_image, thresh, 255, THRESH_TOZERO);
			break;
		case 4:
			threshold(right_image, output_image, thresh, 255, THRESH_TOZERO_INV);
			break;
		case 2:
			threshold(right_image, output_image, thresh, 255, THRESH_TRUNC);
			break;
	}
	imshow(output, output_image);
}
//void traceBarDemo2(int, void*) {
//	switch (thresh_type) {
//
//	}
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
