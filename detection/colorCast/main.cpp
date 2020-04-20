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
		if (!((1.0 <= D / M) && (D / M <= 1.7))){
			if (D / M < 1){
				if ((da  >= -4.0) && (da <= 4.0) && (db >= -4.0) && (db  <= 4.0))
					cout << "K = " << D / M << "-----> MILD CAST" << endl;
				else cout << "K = " << D / M << "-----> INCOMPATIBLE CAMERA (Color cast detected or camera not tested)" << endl;
			} 
			else {
				if ((da  >= -4.0) && (da <= 4.0) && (db >= -4.0) && (db  <= 4.0))
					cout << "K = " << D / M << "-----> MILD CAST" << endl;
				else cout << "K = " << D / M << "-----> COLOR CAST DETECTED" << endl;
			}
		}
		else cout << "K = " << D / M << "-----> NO CAST" << endl;
		//cout << D / M << "   " << da  << "   " << db  << "   " << L << endl; // output of calculated values for testing
		if (waitKey(5) >= 0) break;
	}
	

    return 0;
}

