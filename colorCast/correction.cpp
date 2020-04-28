#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "correction.h"

using namespace cv;


ColorCast::ColorCast() {
    CastFactor_ = 0;
}

int ColorCast::detect(Mat& input) {
    // averageChrominanceAndMomentum
    cvtColor(input, inputLab_, COLOR_BGR2Lab);
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
    CastFactor_ = D_ / M_;

    // castDecision
    if (1.0 <= CastFactor_ && CastFactor_ <= 2.0) {
        return NO_CAST;
    } else if ((mean_a_ >= -4.0) && (mean_a_ <= 4.0) && (mean_b_ >= -4.0) && (mean_b_ <= 4.0)) {
        return MILD;
    } else if (CastFactor_ < 1.0) {
        return INCOMPATIBLE_CAMERA;
    } else if (CastFactor_ > 2.0) {
        return DETECTED;
    }
}

double ColorCast::getCastFactor() {
    return CastFactor_;
};

void ColorCast::correct(Mat& output) {

//    Mat diffMat(input.rows, input.cols, CV_8UC3, Scalar(0, ));

  //  cvtColor(inputLab_, output, COLOR_Lab2BGR);
}

ColorCast::~ColorCast() {

    return;
}


void castVariator(Mat& src, Mat& dest, int Red, int Green, int Blue) {
    Mat mask(src.rows, src.cols, CV_8UC3, Scalar(Blue, Green, Red));
    multiply(src, mask, dest, 0.01);
}
