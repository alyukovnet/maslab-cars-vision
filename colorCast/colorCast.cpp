#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "colorCast.h"

using namespace cv;


ColorCast::ColorCast() {
    CastFactor_ = 0;
}

int ColorCast::detect(Mat& input) {
    // averageChrominanceAndMomentum
    /*cvtColor(input, inputLab_, COLOR_BGR2Lab);
    Scalar Mat_mean = mean(input);
    mean_a_ = Mat_mean[1] - 128;
    mean_b_ = Mat_mean[2] - 128;

    Mat diffMat(input.rows, input.cols, CV_8UC3, Mat_mean);
    absdiff(input, Mat_mean, diffMat); // diff Input image and mean
    Scalar diffMat_mean = mean(diffMat);
    M_a_ = diffMat_mean[1];
    M_b_ = diffMat_mean[2];

    D_ = sqrt(mean_a_*mean_a_ + mean_b_*mean_b_);
    M_ = sqrt(M_a_*M_a_ + M_b_*M_b_);
    CastFactor_ = D_ / M_;*/


    cvtColor(input, inputLab_, COLOR_BGR2Lab);
    mean_a_ = 0;
    mean_b_ = 0;
    M_a_ = 0;
    M_b_ = 0;
    D_ = 0;
    M_ = 0;
	int step = inputLab_.step;
	int channels = inputLab_.channels();
	for (int r = 0; r < inputLab_.rows; r++) {
		for (int c = 0; c < inputLab_.cols; c++) {
			Point3i pixelData;
			//L*: 0-255 
			pixelData.x = inputLab_.data[step * r + channels * c + 0];
			//a*: 0-255 
			pixelData.y = inputLab_.data[step * r + channels * c + 1];
			//b*: 0-255 
			pixelData.z = inputLab_.data[step * r + channels * c + 2];
			mean_a_ += (double)(pixelData.y - 128);
			mean_b_ += (double)(pixelData.z - 128);
		}
	}
	mean_a_ = mean_a_ / ((double)inputLab_.rows * inputLab_.cols);
	mean_b_ = mean_b_ / ((double)inputLab_.rows * inputLab_.cols);
	for (int r = 0; r < inputLab_.rows; r++) {
		for (int c = 0; c < inputLab_.cols; c++) {
			Point3i pixelData;
			pixelData.x = inputLab_.data[step * r + channels * c + 0]; 
			pixelData.y = inputLab_.data[step * r + channels * c + 1];
			pixelData.z = inputLab_.data[step * r + channels * c + 2];
			M_a_ += fabs(((double)(pixelData.y - 128) - mean_a_));
			M_b_ += fabs(((double)(pixelData.z - 128) - mean_b_));
		}
	}
	M_a_ = M_a_ / ((double)inputLab_.rows * inputLab_.cols);
	M_b_ = M_b_ / ((double)inputLab_.rows * inputLab_.cols);
	D_ = sqrt(mean_a_ * mean_a_ + mean_b_ * mean_b_);
	M_ = sqrt(M_a_ * M_a_ + M_b_ * M_b_);
    CastFactor_ = D_ / M_;


    // castDecision
    if (1.0 <= CastFactor_ && CastFactor_ <= 2.0) {
        return NO_CAST;
    } else if (CastFactor_ < 1.0) {
        if ((mean_a_ >= -4.0) && (mean_a_ <= 4.0) && (mean_b_ >= -4.0) && (mean_b_ <= 4.0)) 
        return MILD;
        else return INCOMPATIBLE_CAMERA;
    } else if (CastFactor_ > 2.0) {
        return DETECTED;
    }
}

double ColorCast::getCastFactor() {
    return CastFactor_;
};

void ColorCast::correct(Mat& input, Mat& output) {
    Scalar Mat_mean = mean(output);  // Mean values of BGR
    // Gray scale method
    Mat maskGray(input.rows, input.cols, CV_8UC3, Scalar(
            127/Mat_mean[0],
            127/Mat_mean[1],
            127/Mat_mean[2]));
    multiply(output, maskGray, output);
}

ColorCast::~ColorCast() {
    return;
}


void castVariator(Mat& src, Mat& dest, int Red, int Green, int Blue) {
    Mat mask(src.rows, src.cols, CV_8UC3, Scalar(Blue, Green, Red));
    multiply(src, mask, dest, 0.01);
}
