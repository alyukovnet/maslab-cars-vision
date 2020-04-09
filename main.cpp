#include <iostream>
#include <opencv2/opencv.hpp>
#include "detection/detection.h"
#include "correction/correction.h"

int main() {
    printf("main.cpp | OpenCV version: %s\n", CV_VERSION);
    check_detection();
    check_correction();
    return 0;
}
