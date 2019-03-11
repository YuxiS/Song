// Morphology.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
char input[] = "inputImage";
char output[] = "outputImage";
void callBack(int,void*);
int value = 0;
int main()
{
    std::cout << "Hello World!\n";
	Mat src = imread("./test.png");
	//namedWindow(input, WINDOW_AUTOSIZE);
	//imshow(input, src);
		Mat dst = src.zeros(src.size(), src.type());
	//int value = 0;
		namedWindow(output, WINDOW_AUTOSIZE);
	createTrackbar("morphology_open", output, &value, 30, callBack);
	
	callBack(0,0);
	waitKey(0);

}
void callBack(int ,void*) {
	//Mat image = imread("./test2.png");开操作测试图
	Mat image = imread("./timg.jpg ");//闭操作测试图
	Mat dst = image.zeros(image.size(), image.type());
	Mat kernel = getStructuringElement(MORPH_RECT, Size(value+1, value+1), Point(-1, -1));
	//morphologyEx(image, dst, MORPH_OPEN, kernel);//开操作
	//morphologyEx(image, dst, MORPH_CLOSE, kernel);//闭操做
	//morphologyEx(image, dst, MORPH_GRADIENT, kernel);//梯度操作
	//morphologyEx(image, dst, MORPH_TOPHAT, kernel);//
	morphologyEx(image, dst, MORPH_BLACKHAT, kernel); //
	imshow(output, dst);
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
