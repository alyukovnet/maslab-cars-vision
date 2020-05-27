#ifndef MASLAB_CARS_VISION_BLURDETECT_H
#define MASLAB_CARS_VISION_BLURDETECT_H

#include <opencv2/core.hpp>

using namespace cv;

class BlurDetect {
    private: 
    double BlurFactor_;

public:

    BlurDetect();
    void blur(Mat& inFrame, Mat& outFrame, int k );
    bool detect(Mat& frame);


    double getBlurFactor();
};


#endif //MASLAB_CARS_VISION_BLURDETECT_H
