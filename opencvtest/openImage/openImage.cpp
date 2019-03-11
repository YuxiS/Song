// openImage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1, image2,target;
	image1 = imread("./leaves1.png");
	image2 = imread("./leaves2.png");
	target.zeros(image1.size(), image1.type());
	if (!image1.data) {
		cout << "image1 loads faild" << endl;
	}
	if (!image2.data) {
		cout << "image2 loads faild" << endl;
		return -1;
	}
	//namedWindow("image1",WINDOW_AUTOSIZE);
	//namedWindow("image2", WINDOW_AUTOSIZE);
	//imshow("image1", image1);
	//imshow("image2", image2);
	//addWeighted(image1, 0.5, image2, 0.2, 0,target);
	//imshow("iamge2", target);
	cout << image1.rows<<endl;
	cout << image1.cols << endl;
	cout << image1.channels() << endl;
	int alpha = 1.5;
	int beta = 50;
	for (int i = 0; i < image1.rows; i++) {
		for (int j = 0; j < image1.cols; j++)
		{
			target.at<Vec3f>(i, j)[0] =saturate_cast<uchar>( alpha * image1.at<Vec3f>(i, j)[0] + beta);
			target.at<Vec3f>(i, j)[1] =saturate_cast<uchar>( alpha * image1.at<Vec3f>(i, j)[1] + beta);
			target.at<Vec3f>(i, j)[2] =saturate_cast<uchar>( alpha * image1.at<Vec3f>(i, j)[2] + beta);
		}
	}
	imshow("images1", image1);
	imshow("target", target);
	waitKey(0);
    //std::cout << "Hello World!\n"; 
	return 0;
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
