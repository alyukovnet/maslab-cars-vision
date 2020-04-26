// Test application for the Visual Studio Image Watch Debugger extension
#include"dirtDetect.h"
int main(int argc, char *argv[])
{
    Mat framel, dframe, th;

    VideoCapture cap("/home/vova/work/maslab-cars-vision/dirtDetec/bin/2.mkv");
    cap >> framel;
    cvtColor(framel, framel, COLOR_BGR2GRAY);
    dirtDetect dd;
    while (1)
    {

        Mat frame;
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;
        dd.detectDirt(frame);
        dd.Show();
        char c=waitKey(25);
    }

    return 0;
}
