#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <ctime>


using namespace std;
using namespace cv;

class DirtDetect
{
private:
    Mat framel ;
    Mat tmpFrame;
    Mat dirtlay;
    int x,y;
    double dirtThreshold=0.1;
    Mat tmpFrameThresh;
    Mat dFrame,dFrame2,dFrame1;
    
public:

    DirtDetect(int , int);
    DirtDetect(Mat);
    DirtDetect();
    ~DirtDetect();
    int detectDirt(Mat);
    void show();
    Mat derter(Mat, int);
};

