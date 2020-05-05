#ifndef MASLAB_CARS_VISION_PERCENTSLIDER_H
#define MASLAB_CARS_VISION_PERCENTSLIDER_H

#include "mainwindow.h"
#include "video.h"

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QString>
#include <QLabel>

// announcements
class PercentSlider;
class Indicator;


class SettingsLayout: public QWidget
{
    Q_OBJECT

public:
    QPushButton *openButton;
    QPushButton *rotateButton;
    PercentSlider *redSlider;
    PercentSlider *greenSlider;
    PercentSlider *blueSlider;
    PercentSlider *dirtSlider;

    Indicator *correctingIndicator;
    Indicator *colorCastIndicator;
    Indicator *castFactorIndicator;
    Indicator *dirtIndicator;
    Indicator *blurIndicator;

    explicit SettingsLayout(QWidget *parent);
};


class PercentSlider: public QWidget
{
    Q_OBJECT

public:
    QSlider *slider;
    explicit PercentSlider(const QString& text, QWidget *parent, int value = 100);
};


class Indicator: public QWidget
{
    Q_OBJECT

public:
    explicit Indicator(const QString& name, QWidget *parent);
    QLabel *label;
    QLabel *status;

    enum Color {
        NEUTRAL = 0,
        RED = 1,
        YELLOW = 2,
        GREEN = 3
    };

    void setStatus(const String& s, int color = 0);
};

#endif //MASLAB_CARS_VISION_PERCENTSLIDER_H
