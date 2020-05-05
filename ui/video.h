//
// Created by Данила Алюков on 01.05.2020.
//

#ifndef MASLAB_CARS_VISION_VIDEO_H
#define MASLAB_CARS_VISION_VIDEO_H

#include <QPixmap>
#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "../colorCast/colorCast.h"
#include "settingsLayout.h"

using namespace std;
using namespace cv;

class SettingsLayout;

class Stream: public QObject {
    Q_OBJECT
private:
    VideoCapture file;
    Mat inFrame;
    Mat outFrame;
    ColorCast colorCast;
    SettingsLayout *_settings;
    int cast[3]{};
    int dirt;
public:
    Stream(SettingsLayout *settings);
    bool open(string);
    void close();
    void process();
    int getDelay();
    QPixmap getInFrame();
    QPixmap getOutFrame();
    static QPixmap convertFrame(Mat&);
public slots:
    void setRedCast(int);
    void setGreenCast(int);
    void setBlueCast(int);
    void setDirt(int);
};


#endif //MASLAB_CARS_VISION_VIDEO_H
