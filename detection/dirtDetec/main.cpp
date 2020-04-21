// Test application for the Visual Studio Image Watch Debugger extension
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
void help()
{
    cout
        << "----------------------------------------------------" << endl
        << "This is a test program for the Image Watch Debugger " << endl
        << "plug-in for Visual Studio. The program loads an     " << endl
        << "image from a file and runs the Canny edge detector. " << endl
        << "No output is displayed or written to disk."
        << endl
        << "Usage:" << endl
        << "image-watch-demo inputimage" << endl
        << "----------------------------------------------------" << endl
        << endl;
}
int main(int argc, char *argv[])
{
    Mat framel, dframe,th;

    VideoCapture cap("/home/vova/work/maslab-cars-vision/detection/dirtDetec/bin/1.mkv");
    cap >> framel;
    cvtColor(framel, framel, COLOR_BGR2GRAY);
    while (1)
    {

        Mat frame;
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        // Display the resulting frame
        absdiff(frame, framel, dframe);
        framel=dframe;
        threshold(dframe,dframe, 30, 255, THRESH_BINARY);
        imshow("Frame", dframe);

        // Press  ESC on keyboard to exits
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    return 0;
}
