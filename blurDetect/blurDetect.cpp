#include "blurDetect.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;



BlurDetect::BlurDetect() {
}

void BlurDetect::blur(Mat &inFrame, Mat &outFrame, int k) {
    GaussianBlur(inFrame, outFrame, Size(k/5*2+1, k/5*2+1), 0);
}

bool BlurDetect::detect(Mat &frame) {
    Mat finish;
    Mat gray;

    double theshhold = 100.0;

    cvtColor(frame, gray, COLOR_BGR2GRAY);

    Laplacian(gray, finish, CV_64F);

    Scalar variance_s, m;
    meanStdDev(finish, m, variance_s);

    double variance = variance_s[0]*variance_s[0];

    return variance < theshhold;
}
