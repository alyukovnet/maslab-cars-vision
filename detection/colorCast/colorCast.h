#ifndef MASLAB_CARS_VISION_COLORCAST_H
#define MASLAB_CARS_VISION_COLORCAST_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

using namespace std;
using namespace cv;

void check_colorcast();

void averageChrominanceAndMomentum(float&, float&, float&, float&, Mat, float&);

void BGRtoRed(Mat&, Mat&);

void BGRtoGreen(Mat&, Mat&);

void BGRtoBlue(Mat&, Mat&);

void BGRtoYellow(Mat&, Mat&);



#endif //MASLAB_CARS_VISION_COLORCAST_H
