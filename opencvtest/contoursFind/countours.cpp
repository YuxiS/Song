#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
const char input[] = "Input image";
const char output[] = "Output image";
Mat src, dst;
void contourDemo(int, void*);
int main(void) {
	src = imread("..\\fish.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	//pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	src.copyTo(dst);
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);
	int thresh = 200;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat edge;
	Canny(src, edge, thresh, 2 *thresh, 3, false);
	findContours(edge, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		drawContours(dst, contours, i, Scalar(0, 0, 255), 1, 8, hierarchy, 0);
	}
	imshow(output, dst);
	//createTrackbar("threshold", input, &thresh, 255, contourDemo);
	//contourDemo(thresh, 0);
	waitKey(0);
	return 0;

}
void contourDemo(int sheld, void*) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat edge;
	Canny(src, edge, sheld, 2 * sheld, 3, false);
	findContours(edge, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		drawContours(dst, contours, i, Scalar(0, 0, 255), 1, 8, hierarchy, 0);
	}
	imshow(output, dst);
}