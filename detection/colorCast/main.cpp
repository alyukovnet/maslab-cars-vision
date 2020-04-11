#include <iostream>
#include "colorCast.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    printf("colorCast/main.cpp main()\n");
    check_colorcast();

    Mat frame;
	Mat frameLab;
	Mat frameR, frameG, frameB, frameY;
	float  M = 0.0, D = 0.0, da = 0.0, db = 0.0;
	float L = 0.0;
	VideoCapture vid("../test.mp4");

	if (!vid.isOpened()) return -1;
	while (vid.read(frame)) {
		//imshow("cam", frame);
		frameR = Mat::zeros(frame.size(), CV_8UC3);
		//frameG = Mat::zeros(frame.size(), CV_8UC3);
		//frameB = Mat::zeros(frame.size(), CV_8UC3);
		frameY = Mat::zeros(frame.size(), CV_8UC3);
		//BGRtoRed(frameR, frame);
		//BGRtoGreen(frameG, frame);
		//BGRtoBlue(frameB, frame);
		BGRtoYellow(frameY, frame);
		//imshow("R", frameR);
		//imshow("G", frameG);
		//imshow("B", frameB);
		imshow("Y", frameY);
		cvtColor(frameY, frameLab, COLOR_BGR2Lab);
		imshow("camlab", frameLab);
		averageChrominanceAndMomentum(M, D, da, db, frameLab, L);
		cout << D / M << "   " << da << "   " << db << "   " << db / da << "   " << L << endl;
		if (waitKey(5) >= 0) break;
	}
	//system("pause");

    return 0;
}

