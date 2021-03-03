#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "colorCast.h"

using namespace cv;


ColorCast::ColorCast()
{
    CastFactor_ = 0;
}

int ColorCast::detect(Mat& input) 
{
    return DETECTED;
    // averageChrominanceAndMomentum
    int con = 33;
    int brightness = 0;
    double Kp = 2;
    cvtColor(input, inputLab_, COLOR_BGR2Lab);
    Scalar Mat_mean;
    //if (Mat_mean[0] < 100){
	//		Kp = 1.9 - (130 - Mat_mean[0])/260.0;
	//		con = (int)con*(1.0 + 1.3*(130 - Mat_mean[0])/130.0);
	//		brightness = brightness + (int)20*(130 - Mat_mean[0])/130.0;
	//		input.convertTo(inputBright_, -1, 3.0 * con / 100.0, brightness);
	//} else {
     //   input.copyTo(inputBright_);
    //}
    //cvtColor(inputBright_, inputLab_, COLOR_BGR2Lab);
    Mat_mean = mean(inputLab_);
    mean_a_ = Mat_mean[1] - 128;
    mean_b_ = Mat_mean[2] - 128;
    Mat diffMat(input.rows, input.cols, CV_8UC3);
    absdiff(inputLab_, Mat_mean, diffMat); // diff Input image and mean
    Scalar diffMat_mean = mean(diffMat);
    M_a_ = diffMat_mean[1];
    M_b_ = diffMat_mean[2];

    D_ = sqrt(mean_a_*mean_a_ + mean_b_*mean_b_);
    M_ = sqrt(M_a_*M_a_ + M_b_*M_b_);
    CastFactor_ = D_ / M_;

    // castDecision
    Kp = 1.9 - (130 - Mat_mean[0])/260.0;
    if (CastFactor_ <= Kp) return NO_CAST;
    else return DETECTED;
}

double ColorCast::getCastFactor() 
{
    return CastFactor_;
};

void ColorCast::correct(Mat& input, Mat& output) 
{
    Scalar Mat_mean = mean(input);  // Mean values of BGR
    // Gray scale method
    float gray = (Mat_mean[0]+Mat_mean[1]+Mat_mean[2])/3;
    Mat maskGray(input.rows, input.cols, CV_8UC3, Scalar(
            Mat_mean[0],
            Mat_mean[1],
            Mat_mean[2]));
    divide(input, maskGray, input, gray);
}

ColorCast::~ColorCast() 
{
    return;
}


void castVariator(Mat& src, Mat& dest, int Red, int Green, int Blue) 
{
    Mat mask(src.rows, src.cols, CV_8UC3, Scalar(Blue, Green, Red));
    multiply(src, mask, dest, 0.01);
}
