#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "core/interface.h"
#include "colorCast/colorCast.h"

#include "dirtDetect/dirtDetect.h"
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Interface interface(argc, argv);

    Mat frame, frameOut;

    // Input/Output video windows
    namedWindow("Input", WINDOW_NORMAL);
    namedWindow("Output", WINDOW_NORMAL);
    moveWindow("Input", 200, 0);
    moveWindow("Output", 920, 0);

    // Cast Magic
    int red = 100, green = 100, blue = 100, dirt = 0;
    namedWindow("Color cast magic", WINDOW_NORMAL);
    createTrackbar("R [%]", "Color cast magic", &red, 100);
    createTrackbar("G [%]", "Color cast magic", &green, 100);
    createTrackbar("B [%]", "Color cast magic", &blue, 100);
    createTrackbar("Dirt [%]", "Color cast magic", &dirt, 100);

    interface.start();
    ColorCast colorCast;
    DirtDetect dirtDetect;

    // Main loop
    while (interface.getFrame(frame)) {
		castVariator(frame, frame, red, green, blue);  // Cast magic
        frame = dirtDetect.derter(frame,dirt);
        frame.copyTo(frameOut);

        switch (colorCast.detect(frame)) {
            case ColorCast::NO_CAST:
                interface.log(format("K = %f -----> NO CAST", colorCast.getCastFactor()));
                break;
            case ColorCast::DETECTED:
                interface.log(format("K = %f -----> COLOR CAST DETECTED", colorCast.getCastFactor()));
                // ColorCast correction
                colorCast.correct(frame, frameOut);
                break;
        }

        // dirtDetect here
        if(dirtDetect.detectDirt(frame)){
            interface.log("Detected dirt");
        }
        // Log example
        // interface.log("Message");

        // Show
        //dirtDetect.show();
        imshow("Input", frame);
        resizeWindow("Input", 720, 405);

        imshow("Output", frameOut);
        resizeWindow("Output", 720, 405);

        // Hot keys
        switch ((char) waitKey(25)) {
            case 'q':             // Quit
                exit(0);
        }
    }

    return 0;
}
