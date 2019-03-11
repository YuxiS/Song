// getLine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    std::cout << "Hello World!\n"; 
	Mat test = imread("./test3.png");
	cout << test.channels() << endl;
	namedWindow("test", WINDOW_AUTOSIZE);
	imshow("test", test);
	Mat gray(test.rows,test.cols,CV_8UC1);
	//gray.zeros(test.size(), test.type());
	cvtColor(test, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	Mat adapt;
	adaptiveThreshold(gray, adapt, 255,ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15,-2);
	imshow("binary1", adapt);
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(adapt.cols / 16, 1),Point(-1,-1));
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(1, adapt.rows / 16), Point(-1, -1));
	morphologyEx(adapt, adapt, MORPH_OPEN, kernel2);
	bitwise_not(adapt, adapt);
	/*erode(adapt, adapt, kernel1);
	dilate(adapt, adapt, kernel1);*/
	imshow("binary", adapt);
	waitKey(0);
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
