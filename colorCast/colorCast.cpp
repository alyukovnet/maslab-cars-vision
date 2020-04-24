#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

using namespace std;
using namespace cv;

void check_colorcast() {
    printf("colorCast/colorCast.cpp check_colorcast()\n");
}

void averageChrominanceAndMomentum(float& M, float& D, float& da, float& db, Mat srcLab) {
	M = 0.0;
	D = 0.0;
	da = 0.0;
	db = 0.0;
	float Ma = 0.0;
	float Mb = 0.0;
	cvtColor(srcLab, srcLab, COLOR_BGR2Lab);
	int step = srcLab.step;
	int channels = srcLab.channels();
	for (int r = 0; r < srcLab.rows; r++) {
		for (int c = 0; c < srcLab.cols; c++) {
			Point3_<u_char> pixelData;
			//L*: 0-255 
			pixelData.x = srcLab.data[step * r + channels * c + 0];
			//a*: 0-255 
			pixelData.y = srcLab.data[step * r + channels * c + 1];
			//b*: 0-255 
			pixelData.z = srcLab.data[step * r + channels * c + 2];
			da += (float)(pixelData.y - 128);
			db += (float)(pixelData.z - 128);
		}
	}
	da = da / ((float)srcLab.rows * srcLab.cols);
	db = db / ((float)srcLab.rows * srcLab.cols);
	for (int r = 0; r < srcLab.rows; r++) {
		for (int c = 0; c < srcLab.cols; c++) {
			Point3_<u_char> pixelData;
			pixelData.x = srcLab.data[step * r + channels * c + 0]; 
			pixelData.y = srcLab.data[step * r + channels * c + 1];
			pixelData.z = srcLab.data[step * r + channels * c + 2];
			Ma += fabs(((float)(pixelData.y - 128) - da));
			Mb += fabs(((float)(pixelData.z - 128) - db));
		}
	}
	Ma = Ma / ((float)srcLab.rows * srcLab.cols);
	Mb = Mb / ((float)srcLab.rows * srcLab.cols);
	D = sqrt(da * da + db * db);
	M = sqrt(Ma * Ma + Mb * Mb);
}

void castVariator(Mat& dest, Mat src, int Red, int Green, int Blue)   // You are a wizard, Harry :D (src is a standart BGR Mat)
{
	int maxx = 100;
	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {
			dest.at<Vec3b>(r, c)[0] = src.at<Vec3b>(r, c)[0] * Blue / maxx;
			dest.at<Vec3b>(r, c)[1] = src.at<Vec3b>(r, c)[1] * Green / maxx;
			dest.at<Vec3b>(r, c)[2] = src.at<Vec3b>(r, c)[2] * Red / maxx;
		}
	}
}

void castDecision (float M, float D, float da, float db)
{
	if (!((1.0 <= D / M) && (D / M <= 2.0))){
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
}

