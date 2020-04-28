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
    DirtDetect dirtDetect;

    float M = 0.0, D = 0.0, da = 0.0, db = 0.0; // essential colorCast vars
    Mat frame, frameOut;

    // Input/Output video windows
    namedWindow("Input", WINDOW_NORMAL);
    namedWindow("Output", WINDOW_NORMAL);
    moveWindow("Input", 200, 0);
    moveWindow("Output", 920, 0);

    // Cast Magic
    int red = 100, green = 100, blue = 100, dirt = 100;
    namedWindow("Color cast magic", WINDOW_NORMAL);
    createTrackbar("R [%]", "Color cast magic", &red, 100);
    createTrackbar("G [%]", "Color cast magic", &green, 100);
    createTrackbar("B [%]", "Color cast magic", &blue, 100);
    createTrackbar("D [%]", "Color cast magic", &dirt, 100);

    interface.start();
    ColorCast colorCast;

    // Main loop
    while (interface.getFrame(frame)) {
		castVariator(frame, frame, red, green, blue);  // Cast magic
        frame.copyTo(frameOut);

        switch (colorCast.detect(frame)) {
            case ColorCast::NO_CAST:
                interface.log(format("K = %f -----> NO CAST", colorCast.getCastFactor()));
                break;
            case ColorCast::MILD:
                interface.log(format("K = %f -----> MILD CAST", colorCast.getCastFactor()));
                break;
            case ColorCast::DETECTED:
                interface.log(format("K = %f -----> COLOR CAST DETECTED", colorCast.getCastFactor()));
                // ColorCast correction
                colorCast.correct(frame, frameOut);
                break;
            case ColorCast::INCOMPATIBLE_CAMERA:
                interface.log(format("K = %f -----> INCOMPATIBLE CAMERA "
                                     "(Color cast detected or camera not tested)", colorCast.getCastFactor()));
        }
                break;

        // dirtDetect here
        if(dirtDetect.detectDirt(frame)){
            interface.log("Detected dirt");
        }
        // Log example
        // interface.log("Message");

        // Show
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
