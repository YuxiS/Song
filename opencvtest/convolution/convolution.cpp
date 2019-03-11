// convolution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
const char output1[] = "outputImage1";
const char output2[] = "outputImage2";
const char input[] = "inputImage";
void robert(Mat src);
void sobel(Mat src);
void TraceBar1(int, void*);
void lapras(Mat src);
Mat testBorderin;
Mat testBorderout;
int main()
{
    std::cout << "Hello World!\n";
	Mat src, dst;
	src = imread("./girl.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		waitKey(0);
		return -1;
	}
	pyrDown(src, src, Size(src.cols/2, src.rows/2));
	namedWindow(input, WINDOW_AUTOSIZE);
	//namedWindow("outputImage", WINDOW_AUTOSIZE);
	imshow("inputImage", src);
	//robert(src);
	//sobel(src);
	lapras(src);
	waitKey(0);
}
void robert(Mat src) {
	Mat dst1, dst2;
	Mat kernelX = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat kernelY = (Mat_<int>(2, 2) << 0, 1, -1, 0);
	namedWindow(output1, WINDOW_AUTOSIZE);
	namedWindow(output2, WINDOW_AUTOSIZE);
	filter2D(src, dst1, -1, kernelX, Point(-1, -1));
	filter2D(src, dst2, -1, kernelY, Point(-1, -1));
	imshow(output1, dst1);
	imshow(output2, dst2);
}
void sobel(Mat src) {//图像边缘提取测试
	Mat dst1, dst2,dst;
	Mat kernelX = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat kernelY = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	//namedWindow(output1, WINDOW_AUTOSIZE);
	namedWindow(output2, WINDOW_AUTOSIZE);
	filter2D(src, dst1, -1, kernelX, Point(-1, -1));
	filter2D(src, dst2, -1, kernelY, Point(-1, -1));
	addWeighted(dst1, 1, dst2, 1, 0, dst);
	cvtColor(dst, testBorderin, COLOR_BGR2GRAY);
	int value=1;
	createTrackbar("threshold", output2, &value, 255, TraceBar1);
	TraceBar1(value, 0);
	//Mat grayX,grayY;
	//imshow(output2, testBorderout);
	//threshold(grayX, grayY, , 255, THRESH_BINARY);
	//imshow(output1, gray);
	//imshow(output2, dst2);
	//imshow(output1, grayX);
	//imshow(output2, grayY);
}
void TraceBar1(int value, void*) {
	threshold(testBorderin, testBorderout, value, 255, THRESH_BINARY);
	imshow(output2, testBorderout);
}
void lapras(Mat src) {
	//Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	//Mat kernel = (Mat_<int>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
	Mat kernel = (Mat_<int>(3, 3) << -1,0,-1,0,4,0,-1,0,-1);
	Mat dst;
	filter2D(src, dst, -1, kernel, Point(-1, -1));
	namedWindow("lapras", WINDOW_AUTOSIZE);
	imshow("lapras", dst);
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
