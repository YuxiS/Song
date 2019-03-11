#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	const char input[] = "InputImage";
	const char output[] = "OutputImage";
	VideoCapture cap;
	cap.open(0);
	/*Mat src = imread("..\\build.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		waitKey(0);
		return -1;
	}*/if (cap.isOpened()) {
		//pyrDown(src, src, Size(src.cols / 2, src.rows / 2));

		Mat src,gray,edge;
		namedWindow(input, WINDOW_AUTOSIZE);
		namedWindow(output, WINDOW_AUTOSIZE);
		while (1) {
			cap >> src;
			cvtColor(src, gray, COLOR_BGR2GRAY);
			Canny(gray, edge, 100, 200);
			vector<Vec4f> pointline;
			HoughLinesP(edge, pointline, 1, CV_PI / 180, 10, 50, 5);//最后两个参数对直线的识别很重要！！！
			for (int i = 0; i < pointline.size(); i++) {
				line(src, Point(pointline[i][0], pointline[i][1]), Point(pointline[i][2], pointline[i][3]), Scalar(0, 255, 0), 1);
			}
			if(waitKey(20)>0)
			imshow(input, src);
			imshow(output, edge);
		}
		//waitKey(0);
	}
	return 0;
}
//hough变换计算缓慢，对视频的话很卡