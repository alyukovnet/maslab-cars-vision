#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include"../core/interface.h"
#include<string.h>


using namespace std;
using namespace cv;

class DirtDetect
{
private:
    Mat framel ;
    Mat tmpFrame;
    int x,y;
    double dirtThreshold=0.9;
    Mat tmpFrameThresh;
    Mat dFrame;
    Interface* iface;
public:
    DirtDetect(Interface&,int , int);
    DirtDetect(Interface&,Mat);
    DirtDetect(Interface&);
    ~DirtDetect();
    void detectDirt(Mat);
    void show();
};

