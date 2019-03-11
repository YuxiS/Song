// Blur.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    std::cout << "Hello World!\n";
	Mat image1, image2;
	image1 = imread("./eyes.jpg");
	if (image1.empty()) {
		cout << "Load image failed!" << endl;
		system("pause");
		return -1;
	}
	//namedWindow("inputImagae", WINDOW_FULLSCREEN);
	 imshow("inputImage", image1);
	 Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 6, -1, 0, -1, 0);
	//blur(image1, image2, Size(11,11), Point(-1, -1));
	//imshow("outputimage", image2);
	//GaussianBlur(image1, image2, Size(11, 11), 11, 11);;
	//imshow("GaussianBlur", image2);
	//medianBlur(image1, image2,  9);
	//imshow("medianBlur", image2);
	/*image2 = imread("./eyes.jpg");
	namedWindow("eyes", WINDOW_AUTOSIZE);
	imshow("eyes", image2);*/
	//medianBlur(image2, image2, 5);
	 Mat filter;
	 filter2D(image1, filter, -1, kernel, Point(-1, -1), 0);
	 imshow("filter", filter);
	bilateralFilter(image1, image2, 11, 100, 3);
	imshow("median", image2);
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
