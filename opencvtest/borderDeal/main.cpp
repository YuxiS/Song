#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat src, dst;
const char output[] = "OutputImage";
void traceBarDemo(int, void*);
int main(void) {
	src = imread("./girl.jpg");
	if (src.empty()) {
		cout << "Loading image failed!"<<endl;
		waitKey(0);
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	namedWindow("inputImage", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	int border_type = 0;
	//createTrackbar("boderType", output, &border_type, 4, traceBarDemo);
	//traceBarDemo(border_type, 0);
	GaussianBlur(src, dst, Size(3, 3), 10, 0,BORDER_WRAP);
	imshow("inputImage", src);
	imshow(output, dst);
	waitKey(0);
}
void  traceBarDemo(int border, void*) {
	RNG rng(time(NULL));
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	int top = (int)0.05*src.rows;
	int bottom = (int)0.05*src.rows;
	int left =(int) src.cols*0.05;
	int right = (int)src.cols*0.05;
	switch (border) {
	case 0:
		copyMakeBorder(src, dst, top, bottom, left, right, BORDER_CONSTANT,color);
		break;
	case 1:
		copyMakeBorder(src, dst, top, bottom, left, right, BORDER_REPLICATE);
		break;
	case 2:
		copyMakeBorder(src, dst, top, bottom, left, right, BORDER_REFLECT);
		break;
	case 3:
		copyMakeBorder(src, dst, top, bottom, left, right, BORDER_WRAP);
		break;
	case 4:
		copyMakeBorder(src, dst, top, bottom, left, right,BORDER_DEFAULT);
		break;
	}
	imshow(output, dst);
}