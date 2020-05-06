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
#include "../dirtDetect/dirtDetect.h"
#include "../blurDetect/blurDetect.h"
#include "settingsLayout.h"

using namespace std;
using namespace cv;

class SettingsLayout;
class DirtDetect;

class Stream: public QObject {
    Q_OBJECT
private:
    VideoCapture file;
    Mat inFrame;
    Mat outFrame;
    ColorCast colorCast;
    DirtDetect *dirtDetect;
    BlurDetect blurDetect;
    SettingsLayout *_settings;
    int cast[3]{};
    int dirt;
    int dirtCount;
    int blur;
public:
    Stream(SettingsLayout *settings);
    bool open(string);
    void close();
    void process();
    int getDelay();
    QPixmap getInFrame();
    QPixmap getOutFrame();
    static QPixmap convertFrame(Mat&);
    void refresh();
public slots:
    void setRedCast(int);
    void setGreenCast(int);
    void setBlueCast(int);
    void setDirt(int);
    void setDirtCount(int);
    void setBlur(int);
};


#endif //MASLAB_CARS_VISION_VIDEO_H
