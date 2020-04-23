#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "core/interface.h"
#include "colorCast/correction/correction.h"
#include "colorCast/colorCast.h"
#include "dirtDetec/dirtDetect.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {
    Interface interface(argc, argv);

    Mat frame, frameLab, frameOut, frameOutLab;

    // Input/Output video windows
    namedWindow("Input", WINDOW_NORMAL);
    namedWindow("Output", WINDOW_NORMAL);
    moveWindow("Input",200,0);
    moveWindow("Output",920,0);

    // Cast Magic
    int red = 100, green = 100, blue = 100;
    namedWindow("Color cast magic", WINDOW_NORMAL);
    createTrackbar( "R [%]", "Color cast magic", &red, 100);
    createTrackbar( "G [%]", "Color cast magic", &green, 100);
    createTrackbar( "B [%]", "Color cast magic", &blue, 100);

    interface.start();

    // Main loop
    bool isLab = false;

    while (interface.getFrame(frame)) {
        cvtColor(frame, frameLab, COLOR_BGR2Lab); // convert to Lab

        // Color cast magic operations here

        frame.copyTo(frameOut);
        colorCastCorrection(frame, frameOut);

        // dirtDetect here

        // Log example
        // interface.log("Message");

        // Show
        cvtColor(frame, frameLab, COLOR_BGR2Lab);
        imshow("Input", !isLab ? frame : frameLab);
        resizeWindow("Input", 720, 405);

        cvtColor(frameOut, frameOutLab, COLOR_BGR2Lab);
        imshow("Output", !isLab ? frameOut : frameOutLab);
        resizeWindow("Output", 720, 405);

        // Hot keys
        switch ((char) waitKey(25)) {
            case 'l':             // Switch RGB/Lab
                isLab = !isLab;
                break;
            case 'q':             // Quit
                exit(0);
        }
    }

    return 0;
}
