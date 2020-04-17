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
	Mat magicFrame;
	float  M = 0.0, D = 0.0, da = 0.0, db = 0.0; // initial vars
	float L = 0.0;
 
	//testing trackbars here
	int red = 100, green = 100, blue = 100;
	namedWindow("Color cast magic", WINDOW_AUTOSIZE);          // CAST MAGIC
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
		cvtColor(magicFrame, frameLab, COLOR_BGR2Lab);
		//imshow("camlab", frameLab);
	
		averageChrominanceAndMomentum(M, D, da, db, frameLab, L);
		if (!((20.0 <= D / M) && (D / M <= 30.0))){
			if ((da - 128 >= -12.0) && (da - 128 <= 12.0) && (db - 128 >= -12.0) && (db - 128 <= 12.0)){
				if ((L >= 0.80) && (L <= 1.20) && (db / da >= 0.80) && (db / da <= 1.20)){
					cout << "NO CAST (minor)" << endl;
				}
				else cout << "MINOR or MILD CAST" << endl;
			}
			else {
				if (D / M  >= 37.0) cout << "INCOMPATIBLE/UNCALIBRATED CAMERA (unable to measure cast)" << endl;
				else cout << "COLOR CAST" << endl;
			}
		}
		else {
			if ((da - 128 >= -20.0) && (da - 128 <= 20.0) && (db - 128 >= -20.0) && (db - 128 <= 20.0)){
				if ((L >= 0.80) && (L <= 1.20) && (db / da >= 0.80) && (db / da <= 1.20)){
					cout << "NO CAST (minor)" << endl;
				}
				else cout << "MINOR or MILD CAST" << endl;
			}
		}
		//cout << D / M << "   " << da - 128 << "   " << db - 128 << "   " << db / da << "   " << L << endl; // output of calculated values for testing
		if (waitKey(5) >= 0) break;
	}
	

    return 0;
}

