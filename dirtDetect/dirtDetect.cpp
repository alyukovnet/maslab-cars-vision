#include "dirtDetect.h"

DirtDetect::DirtDetect(Interface& interface)
{
    iface=&interface;
}

DirtDetect::~DirtDetect()
{
}

void DirtDetect::detectDirt(Mat frame)
{
    if (framel.empty())
    {
        cvtColor(frame, framel, COLOR_BGR2GRAY);
        x = frame.cols;
        y = frame.rows;
        return;
    }
    cvtColor(frame, tmpFrame, COLOR_BGR2GRAY);
    // Display the resulting frame
    absdiff(tmpFrame,framel, dFrame);
    framel = dFrame;
    //imshow("Frame1", dframe);
    threshold(dFrame, dFrame, 15, 255, THRESH_BINARY);
    int nonzeros = countNonZero(dFrame);
    
    if (x * y * dirtThreshold > nonzeros)
    {
        iface->log("govno");
    }
    
    char c = (char)waitKey(25);
}
void DirtDetect::show()
{
    if(dFrame.empty()){
        return;
    }
    imshow("Frame12", dFrame);
}