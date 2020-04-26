#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include"../core/interface.h"
using namespace std;
using namespace cv;

class dirtDetect
{
private:
    Mat framel ;
    Mat tmpFrame;
    int x,y;
    double dirtThreshold=0.9;
    Mat tmpFrameThresh;
    Mat dFrame;
public:
    dirtDetect(int , int);
    dirtDetect(Mat);
    dirtDetect();
    ~dirtDetect();
    void detectDirt(Mat);
    void Show();
};

