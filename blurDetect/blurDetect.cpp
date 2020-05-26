#include "blurDetect.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;



BlurDetect::BlurDetect() {
    BlurFactor_ = 0;
}

void BlurDetect::blur(Mat &inFrame, Mat &outFrame, int k) {
    GaussianBlur(inFrame, outFrame, Size(k/5*2+1, k/5*2+1), 0);
}

bool BlurDetect::detect(Mat &frame) {
    Mat finish;
    Mat gray;

    double theshhold =100.0;

    cvtColor(frame, gray, COLOR_BGR2GRAY);

    Laplacian(gray, finish, CV_64F);

    Scalar variance_s, m;
    meanStdDev(finish, m, variance_s);

    double variance = variance_s[0]*variance_s[0];
    BlurFactor_=variance;
    return BlurFactor_ < theshhold;
     return BlurFactor_;
}

double BlurDetect::getBlurFactor() 
{
    return BlurFactor_;
};
