#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	Mat handImage1, handImage2;
	handImage1 = imread("..\\Back_hand2.jpg");
	handImage2 = imread("..\\Back_hand2.jpg");
	if (handImage1.empty() || handImage2.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	//Mat red(handImage1.rows,handImage1.cols,CV_8UC3);
	//证明mixChannels可以分离通道
	/*Mat red = Mat::zeros(handImage1.size(), handImage1.type());
	int channels[] = { 0,2 };
	mixChannels(&handImage1,1, &red,1, channels,1);*/
	//转化到HSV空间
	Mat handHsv1,handHsv2;//hand直方图
	cvtColor(handImage1, handHsv1, COLOR_BGR2HSV);
	cvtColor(handImage2, handHsv2, COLOR_BGR2HSV);
	Mat handHue;
	handHue.create(handHsv1.size(), handHsv1.depth());
	//int a[] = { 0,0 };
	mixChannels(&handHsv1, 1, &handHue, 1, new int[2] {0,0},1);
	//计算直方图信息
	MatND hist1, hist2;
	int h_bins = 25;
	//int s_bins = 60;
	int histSize[] = { h_bins };
	int channel[] = { 0 };
	float h_range[] = { 0,180 };
	//float s_range[] = { 0,256 };
	const float* range[] = { h_range };
	calcHist(&handHue, 1, channel, Mat(), hist1, 1, histSize, range, true, false);
	normalize(hist1, hist1, 0, 180, NORM_MINMAX);
	//calcHist(&handHsv2, 1, channel, Mat(), hist2, 2, histSize, range, true, false);
	//normalize(hist2, hist2, 0, 1, NORM_MINMAX);
	//反向投影
	Mat backproj;
	float range1[] = { 0,180 };
	//float range2[] = { 0,100 };
	const float* rangeTest[] = { range1 };
	calcBackProject(&handHue, 1, channel, hist1, backproj, rangeTest);
	namedWindow("Hand1", WINDOW_AUTOSIZE);
	namedWindow("Hand2", WINDOW_AUTOSIZE);
	//imshow("blue", red);
	imshow("back", backproj);
	imshow("Hand1", handImage1);
	imshow("Hand2", handImage2);
	waitKey(0);
	return 0;

}