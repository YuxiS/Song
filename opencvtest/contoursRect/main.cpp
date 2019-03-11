#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat src, dst;
const char input[] = "Input image";
const char output[] = "Output iamge";
void traceBarDemo(int, void*);
int main(void) {
	src = imread("..//boolean.jpg");
	if (src.empty()) {
		cout << "Loading image failed!" << endl;
		return -1;
	}
	//pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
	blur(src, src, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	int thresh = 127;
	createTrackbar("thresh", output, &thresh, 255, traceBarDemo);
	traceBarDemo(thresh, 0);
	imshow(input, src);
	waitKey(0);
	return 0;
}
void traceBarDemo(int thresh, void*) {
	src.copyTo(dst);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, gray, thresh, 255, THRESH_BINARY);
	//imshow(output, gray);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(gray, contours,hierarchy,RETR_TREE, CHAIN_APPROX_SIMPLE);

	//�����ʼ��
	vector<vector<Point>> ploy(contours.size());//��ʼ��,�������¼RPD�㷨ɸѡ�ĵ�
	vector<Rect> rect_ploy(contours.size());//��¼���ε�����
	vector<RotatedRect> rotateRect_ploy(contours.size());//��¼��ת����
	vector<RotatedRect> ellipse_ploy(contours.size());//��¼��Բ����Ϣ
	vector<Point2f> centers_circle(contours.size());//��¼Բ��Բ��
	vector<float> radius(contours.size());//��¼Բ�İ뾶
	//RNG rng(time(NULL));
	Scalar color(0, 0, 255);
	//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	for (size_t i = 0; i < contours.size(); i++){
		approxPolyDP(contours[i], ploy[i], 5, true);//epsilon��ʾ��������ľ���
		rect_ploy[i] = boundingRect(ploy[i]);//�õ�����
		minEnclosingCircle(ploy[i],centers_circle[i], radius[i]);
		rotateRect_ploy[i] = minAreaRect(ploy[i]);
		if (ploy[i].size() > 5) {
			ellipse_ploy[i] = fitEllipse(ploy[i]);
		}
		//rectangle(dst, Rect_ploy[i], color, 1);
	}
	for (size_t i = 0; i < centers_circle.size(); i++){
		//circle(dst, centers_circle[i], radius[i], color, 2);
		Point2f rotateRectPoint[4];//��¼��ת���ε��ĸ��ǵ���Ϣ
		rotateRect_ploy[i].points(rotateRectPoint);//���ĸ��㸳ֵ
		for (int j = 0; j < 4; j++) {
			line(dst, rotateRectPoint[j], rotateRectPoint[(j + 1) % 4], color);
		}
		//ellipse(dst, ellipse_ploy[i], color);
	}
	imshow(output, dst);
}