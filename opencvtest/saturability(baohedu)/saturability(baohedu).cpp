// saturability(baohedu).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
	image1 = imread("./timg.jpg");
	image2 = Mat::zeros(image1.size(),image1.type());
	if (image1.empty()) {
		cout << "data read error!" << endl;
		system("pause");
		return 0;
	}
	int height = image1.rows;
	int width = image1.cols;
	//int channel = image1.channels;
	double alpha = 1.5;
	int beta = 0;
 	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (image1.channels() == 3) {
				float b = image1.at<Vec3b>(i,j)[0];
				float g = image1.at<Vec3b>(i,j)[1];
				float r = image1.at<Vec3b>(i,j)[2];
				image2.at<Vec3b>(i,j)[0] = saturate_cast<uchar>(alpha*b + beta);
				image2.at<Vec3b>(i,j)[1] = saturate_cast<uchar>(alpha*g + beta);
				image2.at<Vec3b>(i,j)[2] = saturate_cast<uchar>(alpha*r + beta);
			}
			else {
				float c = image1.at<uchar>(i,j);
				image2.at<uchar>(i,j) = saturate_cast<uchar>(alpha*c + beta);
			}
		}
	}
	namedWindow("timg", WINDOW_AUTOSIZE);
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("timg", image2);
	imshow("image", image1);
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
