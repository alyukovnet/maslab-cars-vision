#include <opencv2/core.hpp>
#include "../colorCast/colorCast.h"
#include <QPixmap>
#include <QSize>
#include <opencv2/imgproc.hpp>
#include "settingsLayout.h"
#include "video.h"
#include "../dirtDetect/dirtDetect.h"
#include "../blurDetect/blurDetect.h"

using namespace cv;

Stream::Stream(SettingsLayout *settings) {
    inFrame = Mat::zeros(360, 640, CV_8UC3);
    outFrame = Mat::zeros(360, 640, CV_8UC3);
    cast[0] = cast[1] = cast[2] = 100;
    dirt = dirtCount = 0;
    blur = 0;
    dirtDetect = new DirtDetect;
    _settings = settings;
}

bool Stream::open(string s) {
    return file.open(s);
}

int Stream::getDelay() {
    if (file.isOpened())
        return 1000 / (int) file.get(CAP_PROP_FPS);
    else
        return 0;
}

void Stream::setRedCast(int value) {
    cast[2] = value;
}

void Stream::setGreenCast(int value) {
    cast[1] = value;
}

void Stream::setBlueCast(int value) {
    cast[0] = value;
}

void Stream::setDirt(int value) {
    dirt = value;
}

void Stream::setDirtCount(int value) {
    dirtCount = value;
}

void Stream::setBlur(int flag) {
    blur = flag;
}

void Stream::close() {
    file.release();
}

void Stream::process() {
    // if no frame, repeat video
    if (!file.read(inFrame)) {
        file.set(CAP_PROP_POS_FRAMES, 0);
        file.read(inFrame);
    }

    // simulator works
    castVariator(inFrame, inFrame, cast[0], cast[1], cast[2]);
    inFrame = dirtDetect->derter(inFrame, dirt, dirtCount);
    if (blur > 0)
        blurDetect.blur(inFrame, inFrame, blur);
    inFrame.copyTo(outFrame);

    // ColorCast detection
    switch (colorCast.detect(inFrame)) {
        case ColorCast::NO_CAST:
            _settings->castFactorIndicator->setStatus(to_string(colorCast.getCastFactor()));
            _settings->colorCastIndicator->setStatus("No cast", Indicator::GREEN);
            _settings->correctingIndicator->setStatus("Disabled");
            break;
        case ColorCast::DETECTED:
            _settings->castFactorIndicator->setStatus(to_string(colorCast.getCastFactor()));
            _settings->colorCastIndicator->setStatus("Detected", Indicator::RED);
            // ColorCast correction
            colorCast.correct(inFrame, outFrame);
            _settings->correctingIndicator->setStatus("Enabled", Indicator::GREEN);
            break;
    }

    // Dirt detection
    if (dirtDetect->detectDirt(outFrame)){
        _settings->dirtIndicator->setStatus("Detected", Indicator::RED);
    } else {
        _settings->dirtIndicator->setStatus("No");
    }

    if (blurDetect.detect(outFrame)){
        _settings->blurIndicator->setStatus("Detected", Indicator::YELLOW);
    } else {
        _settings->blurIndicator->setStatus("No");
    }
}

void Stream::refresh() {
    delete dirtDetect;
    dirtDetect = new DirtDetect;
}

QPixmap Stream::getInFrame() {
    return convertFrame(inFrame);
}

QPixmap Stream::getOutFrame() {
    return convertFrame(outFrame);
}

QPixmap Stream::convertFrame(Mat& frame) {
    QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img.rgbSwapped());
}
