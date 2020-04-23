#include <opencv2/core.hpp>
#include "correction.h"
using namespace cv;


void colorCastCorrection(Mat& input, Mat& output) {
    float k[3];
    k[0] = 1; // Blue
    k[1] = 0; // Green
    k[2] = 1; // Red
    applyColorsCoef(input, output, k);
}


void applyColorsCoef(Mat& input, Mat& output, float k[3]) {
    for (int i = 0; i < input.rows; i++) {
        for (int j = 0; j < input.cols; j++) {
            output.at<Vec3b>(i, j)[0] = input.at<Vec3b>(i, j)[0] * k[0];
            output.at<Vec3b>(i, j)[1] = input.at<Vec3b>(i, j)[1] * k[1];
            output.at<Vec3b>(i, j)[2] = input.at<Vec3b>(i, j)[2] * k[2];
        }
    }
}
