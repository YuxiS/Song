#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include<sstream>
using namespace std;
using namespace cv;
string toString(double a);
int main(void) {
	Mat src, dst;
	src = imread("..\\girl.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	//产生一张具有噪声的图片
	Mat srcPlusNoise;
	src.copyTo(srcPlusNoise);
	Mat test=imread("..\\100.jpg");
	Mat test2;
	pyrDown(test, test, Size(test.cols / 2, test.rows / 2));
	cvtColor(test, test2, COLOR_BGR2HSV);
	RNG rng;
	for (int i = 0; i < 50; i++) {
		circle(srcPlusNoise, Point(rng.uniform(0, src.cols), rng.uniform(0, src.rows)),1, Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	}
	//转换到HSV空间
	Mat srcHsv,srcNoiseHsv;
	cvtColor(src, srcHsv, COLOR_BGR2HSV);
	cvtColor(srcPlusNoise, srcNoiseHsv, COLOR_BGR2HSV);
	//计算直方图并归一化
	int h_bins = 180;//H的级数
	int s_bins = 256;//S的级数
	int v_bins = 100;//V的级数
	const int histSize[] = { h_bins,s_bins,v_bins};//级数的最大值，多维图像有多个范围，所以calcHist函数中用int*来表时这一项
	const int channel[] = { 0,1,2};
	Mat histSrc, histSrcNoise,histTest;//存储直方图信息
	const float h_range[] = { 0,180 };
	const float sv_range[] = { 0,256 };//range表示级的范围，即最大级和最小级
	const float* hist_range[] = { h_range,sv_range,sv_range };//当有多维时，这个二级指针记录多个范围（每个范围用数组表示），必须为const
	calcHist(&srcHsv, 1, channel, Mat(), histSrc, 3, histSize, hist_range, true, false);
	calcHist(&srcPlusNoise, 1, channel, Mat(), histSrcNoise, 3, histSize, hist_range, true, false);
	calcHist(&test2, 1, channel, Mat(), histTest, 3, histSize, hist_range, true, false);
	//归一化
	normalize(histTest, histTest, 0, 1,NORM_MINMAX);
	normalize(histSrc, histSrc, 0, 1, NORM_MINMAX);
	normalize(histSrcNoise, histSrcNoise, 0, 1, NORM_MINMAX);
	//获取相似度
	double differ1 = compareHist(histSrc, histSrc, HISTCMP_BHATTACHARYYA);
	double differ2=compareHist(histSrc, histSrcNoise, HISTCMP_BHATTACHARYYA);
	double differ3 = compareHist(histSrc, histTest, HISTCMP_BHATTACHARYYA);
	cout << differ1 << endl << differ2 << differ3<<endl;
	putText(src, toString(differ1), Point(100, 100), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 2);
	putText(srcPlusNoise, toString(differ2), Point(100, 100), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 2);
	putText(test, toString(differ3), Point(100, 100), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 2);
	imshow("Input", src);
	imshow("noise", srcPlusNoise);
	imshow("test", test);
	//imwrite("..\\girl&noise.jpg", srcPlusNoise);
	waitKey(0);
	return 0;
	
}
string toString(double a) {
	stringstream sStream;
	sStream << a;
	string str;
	sStream >> str;
	return str;
}