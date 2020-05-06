#ifndef MASLAB_CARS_VISION_BLURDETECT_H
#define MASLAB_CARS_VISION_BLURDETECT_H

#include <opencv2/core.hpp>

using namespace cv;

class BlurDetect {
public:
    BlurDetect();
    void blur(Mat& inFrame, Mat& outFrame);
    bool detect(Mat& frame);
};


#endif //MASLAB_CARS_VISION_BLURDETECT_H
