#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat src, dst;
const char output[] = "Output";
void traceBarDemo(int, void*);
int main(void) {
	//src = imread("..\\girl.jpg");
	VideoCapture camera;
	camera.open(0);
	if (!camera.isOpened()) {
		//cout << "Loading image failed!" << endl;
		cout << "Opening camera failed!" << endl;
		waitKey(0);
		return -1;
	}
	int thre = 50;
	while (1) {
		if (waitKey(20)<=0) {
			camera >> src;
			//pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
			namedWindow("Input", WINDOW_AUTOSIZE);
			namedWindow(output, WINDOW_AUTOSIZE);
			createTrackbar("thre", output, &thre, 255, traceBarDemo);
			traceBarDemo(thre, 0);
			imshow("Input", src);
		}
		else {
			break;
		}
	}
	//waitKey(0);
	return 0;
}
void traceBarDemo(int thre, void*) {
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Canny(gray, dst, thre, 2 * thre);
	Mat newImage=Mat::zeros(src.size(), src.type());
	copyTo(src, newImage, dst);
	imshow(output, ~dst);
}