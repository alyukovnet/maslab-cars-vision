#include "dirtDetect.h"

DirtDetect::DirtDetect()
{
    srand(time(NULL));
}

DirtDetect::~DirtDetect()
{
}

int DirtDetect::detectDirt(Mat frame)
{
    if (framel.empty())
    {
        cvtColor(frame, framel, COLOR_BGR2GRAY);

        x = frame.cols;
        y = frame.rows;
        return 0;
    }
    cvtColor(frame, tmpFrame, COLOR_BGR2GRAY);
    // Display the resulting frame
    tmpFrame *= 0.8;
    absdiff(tmpFrame, framel, dFrame);
    framel = dFrame;
    // imshow("Frame11", dFrame);
    threshold(dFrame, dFrame1, 5, 255, THRESH_BINARY);
    threshold(dFrame, dFrame2, 252, 255, THRESH_BINARY);
    threshold(dFrame, dFrame, 10, 255, THRESH_BINARY);

    dFrame1 = (255 - dFrame1) + dFrame2;

    // imshow("Frame12", dFrame1);
    int nonzeros = countNonZero(dFrame1);

    if (x * y * dirtThreshold < nonzeros)
    {
        return 1;
    }
    return 0;
}
void DirtDetect::show()
{
    if (dFrame.empty())
    {
        return;
    }
    imshow("Frame", dFrame1);
}
Mat DirtDetect::derter(Mat frame, int dirt)
{
    if (dirtlay.empty())
    {

        dirtlay.create(frame.rows, frame.cols, frame.type());

        circle(dirtlay, Point(100 + rand() % (frame.rows - 200), 100 + rand() % (frame.cols - 200)), 50, Scalar(255, 255, 255), 75, 0);
        blur(dirtlay, dirtlay, Size(50, 50), Point(-1, -1));
    }
    //imshow("Frame1", dirtlay);
    return frame - (dirtlay * dirt / 100);
}