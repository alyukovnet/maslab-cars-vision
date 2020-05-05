#ifndef MASLAB_CARS_VISION_DIRT_DETECT_H
#define MASLAB_CARS_VISION_DIRT_DETECT_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <ctime>
#include <iostream>

using namespace std;
using namespace cv;

class DirtDetect
{
private:
    Mat framel;
    Mat tmpFrame;
    Mat dirtlay;
    int x, y;
    double dirtThreshold = 0.02;
    Mat tmpFrameThresh;
    Mat dFrame, dFrame2, dFrame1;
    int count;
    RNG rng;

public:
    DirtDetect(int, int);
    DirtDetect(Mat);
    DirtDetect();
    ~DirtDetect();
    int detectDirt(Mat);
    void show();
    Mat derter(Mat, int, int);
    void draw(Mat, Mat);
    void draw_l(Mat, Mat);
};

#endif //MASLAB_CARS_VISION_DIRT_DETECT_H
