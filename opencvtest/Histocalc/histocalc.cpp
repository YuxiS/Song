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
	//ͼ��ָ�ɵ�ͨ��ͼ��
	vector<Mat> bgr_1Cimage;//�����洢��ͨ��ͼ
	split(src, bgr_1Cimage);
	//����ֱ��ͼ��Ϣ
	 const int channel = 1;//ͨ����
	Mat hist_b, hist_g, hist_r;//�洢ֱ��ͼ��Ϣ
	const float range[] = { 0,256 };//���ķ�Χ������С�������
	const float* histrange = { range };//��һ�������ܣ�������д
	const int histsize = 256;//��ÿ�����ط�Ϊһ��������Ϊ256
	calcHist(&bgr_1Cimage[0], 1, 0, Mat(), hist_b, 1, &histsize, &histrange, true, false);
	calcHist(&bgr_1Cimage[1], 1, 0, Mat(), hist_g, 1, &histsize, &histrange, true, false);
	calcHist(&bgr_1Cimage[2], 1, 0, Mat(), hist_r, 1, &histsize, &histrange, true, false);
	//����ֱ��ͼ�Ĵ�С
	int histWidth = 600;
	int histHeight = 400;
	dst = Mat::zeros(Size(histWidth,histHeight),CV_8UC3);
	//��һ������
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	normalize(hist_b, hist_b, 0, dst.rows-1, NORM_MINMAX, -1, Mat());
	float binsWidth = cvRound((double)histWidth / histsize);
	//����ֱ��ͼ
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