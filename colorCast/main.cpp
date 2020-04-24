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
	Mat frameLab; // useful Mats
	Mat magicFrame;
	float  M = 0.0, D = 0.0, da = 0.0, db = 0.0; // initial vars, means
 
	//testing trackbars here
	int red = 100, green = 100, blue = 100;
	namedWindow("Color cast magic", WINDOW_AUTOSIZE);          
	createTrackbar( "R [%]", "Color cast magic", &red, 100);
	createTrackbar( "G [%]", "Color cast magic", &green, 100);
	createTrackbar( "B [%]", "Color cast magic", &blue, 100);


	VideoCapture vid("../test.mp4");
	if (!vid.isOpened()) return -1;

	while (vid.read(frame)) {
		//imshow("Normal", frame);
		magicFrame = Mat::zeros(frame.size(), CV_8UC3);
		castVariator(magicFrame, frame, red, green, blue);
		imshow("Cast", magicFrame);
		averageChrominanceAndMomentum(M, D, da, db, magicFrame);
		castDecision(M, D, da, db);
		if (waitKey(10) >= 0) break;
	}
	

    return 0;
}

