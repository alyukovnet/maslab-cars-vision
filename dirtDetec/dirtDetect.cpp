#include "dirtDetect.h"

dirtDetect::dirtDetect(/* args */)
{
}

dirtDetect::~dirtDetect()
{
}

void dirtDetect::detectDirt(Mat frame)
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
        cout << "govno" << endl;
    }
    
    char c = (char)waitKey(25);
}
void dirtDetect::Show()
{
    if(dFrame.empty()){
        return;
    }
    imshow("Frame12", dFrame);
}