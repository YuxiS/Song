#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
const char input[] = "Input image";
const char output[] = "Output histogram";
int main(void) {
	Mat src, dst;
	src = imread("..\\dream.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	//图像分割成单通道图像
	vector<Mat> bgr_1Cimage;//向量存储单通道图
	split(src, bgr_1Cimage);
	//计算直方图信息
	 const int channel = 1;//通道数
	Mat hist_b, hist_g, hist_r;//存储直方图信息
	const float range[] = { 0,256 };//级的范围，及最小级和最大级
	const float* histrange = { range };//这一步很难受，但必须写
	const int histsize = 256;//将每个像素分为一级，级数为256
	calcHist(&bgr_1Cimage[0], 1, 0, Mat(), hist_b, 1, &histsize, &histrange, true, false);
	calcHist(&bgr_1Cimage[1], 1, 0, Mat(), hist_g, 1, &histsize, &histrange, true, false);
	calcHist(&bgr_1Cimage[2], 1, 0, Mat(), hist_r, 1, &histsize, &histrange, true, false);
	//设置直方图的大小
	int histWidth = 600;
	int histHeight = 400;
	dst = Mat::zeros(Size(histWidth,histHeight),CV_8UC3);
	//归一化操作
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	float binsWidth = cvRound((double)histWidth / histsize);
	//绘制直方图
	for (int i = 1; i <histsize; i++){
		line(dst, Point((i - 1)*binsWidth, histHeight- hist_b.at<float>(i - 1)), Point((i)*binsWidth, histHeight - hist_b.at<float>(i)), Scalar(255, 0, 0),1,LINE_AA);
		line(dst, Point((i - 1)*binsWidth, histHeight - hist_g.at<float>(i - 1)), Point((i)*binsWidth, histHeight - hist_g.at<float>(i)), Scalar(0, 255, 0),1,LINE_AA);
		line(dst, Point((i - 1)*binsWidth, histHeight - hist_r.at<float>(i - 1)), Point((i)*binsWidth, histHeight - hist_r.at<float>(i)), Scalar(0, 0, 255),1,LINE_AA);
	}
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(output, dst);
	imshow(input, src);
	waitKey(0);
	return 0;
}