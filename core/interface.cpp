#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

#include "interface.h"

using namespace std;
using namespace cv;


Interface::Interface(int argc, char *argv[]) {
    const string keys =
            "{ @input         |   | Path to input video (required) }"
            "{ help h usage ? |   | Print this message             }"
            "{ rotate         | 0 | Rotate +-90° CW                }"
            "{ flip           |   | Rotate 180°                    }"
            "{ flip-y         |   | Flip Vertical                  }"
            "{ flip-x         |   | Flip Horizontal                }"
            "{ log            |   | Name for log file              }"
            "{ repeat r       |   | Repeat after end of the video  }";
    CommandLineParser parser(argc, argv, keys);
    parser.about("Maslab Cars Vision v1.0.0 beta");

    // Parse args
    if (parser.has("help")) {
        parser.printMessage(); // Help message
        exit(0);
    }
    videoSource = parser.get<String>(0); // input (required)
    if (parser.has("log"))
        logFileName = parser.get<String>("log"); // save (if necessary)
    int rotate = parser.get<int>("rotate"); // rotate (default 0)

    // Check for errors in args
    if (!parser.check()) {
        parser.printErrors();
        exit(0);
    }

    // Values processing
    repeat = parser.has("repeat");

    // Rotate
    // Nums of 90 degrees rotates | (abs(rotate) % 360): rotateNum
    // 0..44: 0, 45..134: 1, 135..224: 2, 225..314: 3, 315..359: 0
    int rotateNum = (((abs(rotate) / 45) % 8 + 8) % 8 + 1) / 2 % 4;
    // Rotate flag
    // 0 - 90 CW, 1 - 180 CW, 2 - 90 CCW
    rotateFlag = rotate >= 0 ? rotateNum - 1 : (4 - rotateNum) % 4 - 1;

    // Flip optimize
    bool flipX = false;
    bool flipY = false;
    if (parser.has("flip")) {
        flipX = !flipX;
        flipY = !flipY;
    }
    if (parser.has("flip-x"))
        flipX = !flipX;
    if (parser.has("flip-y"))
        flipY = !flipY;
    // Flip code
    if (flipX && flipY) {
        flipCode = -1; // flip x&y
    } else if (flipX) {
        flipCode = 0;  // flip x
    } else if (flipY) {
        flipCode = 1;  // flip y
    } else {
        flipCode = -2; // no flip
    }
}

void Interface::start() {
    if (!cap.open(videoSource)) {
        exit(0);
    }
    if (logFileName.length() > 0) {
        file.open(logFileName);
    }
}

void Interface::log(String s) {
    cout << s << endl;
    if (file.is_open()) {
        file << s << endl;
    }
}

bool Interface::getFrame(Mat& frame) {
    GET_FRAME_START:
    if (cap.read(frame)) {
        if (flipCode != -2)
            flip(frame, frame, flipCode);
        if (rotateFlag != -1)
            rotate(frame, frame, rotateFlag);
        return true;
    } else if (repeat) {
        cap.set(CAP_PROP_POS_FRAMES, 0);
        goto GET_FRAME_START; // Try to read frame again
    } else {
        return false;
    }
}

Interface::~Interface() {
    file.close();
}
