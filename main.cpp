#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "core/interface.h"
#include "colorCast/detection.h"
#include "colorCast/correction.h"

#include"dirtDetect/dirtDetect.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {
    Interface interface(argc, argv);
    DirtDetect dirtDetect( interface );
    
    Mat frame, frameLab, frameOut, frameOutLab, magicFrame;
    float  M = 0.0, D = 0.0, da = 0.0, db = 0.0; // essential colorCast vars

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
        // Color cast magic operations here
        magicFrame = Mat::zeros(frame.size(), CV_8UC3);
		castVariator(magicFrame, frame, red, green, blue);
		magicFrame.copyTo(frame);
		averageChrominanceAndMomentum(M, D, da, db, magicFrame);
		castDecision(M, D, da, db);
        // end colorCast detection

        frame.copyTo(frameOut);
        colorCastCorrection(frame, frameOut);

        // dirtDetect here
        dirtDetect.detectDirt(frame);
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
