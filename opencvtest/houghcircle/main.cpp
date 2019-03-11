#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
	const char input[] = "Input image";
	const char output[] = "Output immage";
int main(void) {
	Mat src = imread("..\\football.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		waitKey(0);
		return -1;
	}
	pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	Mat blur;
	medianBlur(src, blur,3);
	cvtColor(blur, blur, COLOR_BGR2GRAY);
	Canny(blur, blur, 100, 200);
	vector<Vec3f> pcircle;
	HoughCircles(blur, pcircle, HOUGH_GRADIENT,1,100,100,40,50,140);
	Mat dst;
	src.copyTo(dst);
	for (int i = 0; i < pcircle.size(); i++){
		circle(dst, Point(pcircle[i][0], pcircle[i][1]), pcircle[i][2], Scalar(0, 0, 255), 2);
		circle(dst, Point(pcircle[i][0], pcircle[i][1]), 1, Scalar(255, 0, 255), 1);
	}
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);
	imshow(output, dst);
	waitKey(0);
	return 0;
}

