#include <opencv2/core.hpp>
#include "../colorCast/colorCast.h"
#include <QPixmap>
#include <QSize>
#include <opencv2/imgproc.hpp>
#include "settingsLayout.h"
#include "video.h"

using namespace cv;

Stream::Stream(SettingsLayout *settings) {
    inFrame = Mat::zeros(360, 640, CV_8UC3);
    outFrame = Mat::zeros(360, 640, CV_8UC3);
    cast[0] = cast[1] = cast[2] = 100;
    dirt = 0;
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

void Stream::close() {
    file.release();
}

void Stream::process() {
    if (!file.read(inFrame)) {
        file.set(CAP_PROP_POS_FRAMES, 0);
        file.read(inFrame);
    }
    castVariator(inFrame, inFrame, cast[0], cast[1], cast[2]);
    inFrame.copyTo(outFrame);
    colorCast.correct(inFrame, outFrame);
    _settings->correctingIndicator->setStatus("Enabled", Indicator::GREEN);

    // processing i/o frames
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
