// opencvtest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	/*VideoCapture cap(0);
	Mat frame;

	while (true)
	{
		cap >> frame;
		imshow("VIDEO", frame);
		waitKey(0);
	}
	std::cout << "Hello World!\n";
	*/
	double t = getTickCount();
	Mat frame = imread("./timg.jpg");
	Mat gray_frame=Mat::zeros(frame.size(),frame.type());
	Mat trav = Mat::zeros(frame.size(), frame.type());
	Mat kernal = (Mat_<uchar>(3, 3) << 1, 1, 1,1, 1, 1, 1, 1, 1);
	if (frame.empty()) {
		cout << "loading image failed." << endl;
		system("pause");
		return 0;
	}
	frame.copyTo(gray_frame);
	//namedWindow("image", WINDOW_AUTOSIZE);
	//namedWindow("test", WINDOW_AUTOSIZE);
	cvtColor(frame, trav, COLOR_BGR2GRAY);
	cout << trav.at<Vec3b>(1, 1) << endl;
	cout << frame.at<Vec3b>(1, 1) << endl;
	//filter2D(frame,gray_frame,-1,kernal);
	//cout << trav.channels();
	imshow("image",frame);
	//imshow("test", frame);
	//imshow("test", gray_frame);
	/*int height = frame.rows;
	int width = frame.cols;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			frame.at<Vec3b>(i, j)[0] = 255 - frame.at<Vec3b>(i, j)[0];
			frame.at<Vec3b>(i, j)[1] = 255 - frame.at<Vec3b>(i, j)[1];
			frame.at<Vec3b>(i, j)[1] = 255 - frame.at<Vec3b>(i, j)[1];
		}
	}*/
	//imshow("image", frame);
	cout << (getTickCount() - t) / getTickFrequency(); 
	//imwrite("G:\\2345Downloads\\image\\Lavender1.png",gray_frame);
	cv::waitKey(0);
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
