//µ„∂‡±ﬂ–Œ≤‚ ‘
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(void) {
	Mat src;
	src=Mat::zeros(Size(500, 500), CV_8UC3);
	RNG rng(time(NULL));
	vector<Point> ploygon;
	//for (size_t i = 0; i < 5; i++){
		ploygon.push_back(Point(rng.uniform(0, (src.cols - 1)/2), rng.uniform(0, (src.rows - 1))/2));
		ploygon.push_back(Point(rng.uniform((src.cols - 1) / 2, src.cols - 1), rng.uniform(0, src.rows - 1)));
		ploygon.push_back(Point(rng.uniform((src.cols - 1) / 2, src.cols - 1), rng.uniform(((src.rows - 1) / 2), src.rows - 1)));
		ploygon.push_back(Point(rng.uniform(0, src.cols - 1), rng.uniform(((src.rows - 1) / 2), src.rows - 1)));

		//ploygon[i].x = rng.uniform(0, src.cols - 1);
		//ploygon[i].y = rng.uniform(0, src.rows - 1);
	//}
		Mat dst;
		//src.copyTo(dst);
		dst.create(src.size(), CV_8UC3);
	for (size_t i = 0; i < 4; i++){
		line(src, ploygon[i], ploygon[(i + 1) % 4], Scalar(255, 255, 255), 2,LINE_AA);
	}
	
	cvtColor(src, src, COLOR_BGR2GRAY);
	threshold(src, src, 100, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < src.cols; i++){
		for (size_t j = 0; j < src.rows; j++){
			double dist = pointPolygonTest(contours[0], Point2f(i,j), true);
			if (dist > 0) {
				for (size_t m = 0; m < 3; m++)
				{
					dst.at<Vec3b>(i, j)[m] = rng.uniform(0, 100);
				}
			}
			/*else if(dist<-30)
			{
				for (size_t m = 0; m < 3; m++)
				{
					dst.at<Vec3b>(i, j)[m] = rng.uniform(101, 180);
				}
			}*/
			else
			{
				for (size_t m = 0; m < 3; m++)
				{
					dst.at<Vec3b>(i, j)[m] = rng.uniform(181, 255);
				}
			}
		}
	}
	namedWindow("output", WINDOW_AUTOSIZE);
	namedWindow("Input", WINDOW_AUTOSIZE);
	imshow("Input", src);
	imshow("output", dst);
	waitKey(0);
	return 0;
}