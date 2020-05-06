#include "settingsLayout.h"

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QCheckBox>


SettingsLayout::SettingsLayout(QWidget *parent): QWidget(parent)
{
    auto *layout = new QHBoxLayout();
    // Video settings
    auto *videoSettings = new QGroupBox(this);
    layout->addWidget(videoSettings);
    auto *videoSettingsLayout = new QVBoxLayout(this);
    videoSettings->setLayout(videoSettingsLayout);
    videoSettings->setTitle(tr("Video settings"));

    openButton = new QPushButton(tr("Open video"), parent);
    videoSettingsLayout->addWidget(openButton);
    rotateButton = new QPushButton(tr("Rotate 90 CW"), parent);
    videoSettingsLayout->addWidget(rotateButton);

    // Simulator settings
    auto *simulatorSettings = new QGroupBox(this);
    simulatorSettings->setTitle(tr("Simulator parameters"));

    redSlider = new PercentSlider(tr("Red"), this, 100);
    greenSlider = new PercentSlider(tr("Green"), this, 100);
    blueSlider = new PercentSlider(tr("Blue"), this, 100);
    dirtSlider = new PercentSlider(tr("Dirt"), this, 0);
    dirtCountSlider = new PercentSlider(tr("Dirt count"), this, 0, 5);

    blurBool = new QCheckBox(tr("Blur"), this);

    auto *simulatorSettingsLayout = new QVBoxLayout(this);
    simulatorSettingsLayout->addWidget(redSlider);
    simulatorSettingsLayout->addWidget(greenSlider);
    simulatorSettingsLayout->addWidget(blueSlider);
    simulatorSettingsLayout->addWidget(dirtSlider);
    simulatorSettingsLayout->addWidget(dirtCountSlider);
    simulatorSettingsLayout->addWidget(blurBool);
    simulatorSettings->setLayout(simulatorSettingsLayout);
    layout->addWidget(simulatorSettings);

    // Output settings
    auto *outputSettings = new QGroupBox(this);
    outputSettings->setTitle(tr("Output settings"));
    auto *outputSettingsLayout = new QVBoxLayout(this);
    outputSettings->setLayout(outputSettingsLayout);
    layout->addWidget(outputSettings);

    colorCastIndicator = new Indicator("Color Cast", this);
    outputSettingsLayout->addWidget(colorCastIndicator);

    castFactorIndicator = new Indicator("Cast Factor", this);
    outputSettingsLayout->addWidget(castFactorIndicator);

    correctingIndicator = new Indicator("Color Cast correction", this);
    outputSettingsLayout->addWidget(correctingIndicator);

    dirtIndicator = new Indicator("Dirt", this);
    outputSettingsLayout->addWidget(dirtIndicator);

    blurIndicator = new Indicator("Blur", this);
    outputSettingsLayout->addWidget(blurIndicator);

    this->setLayout(layout);
}


PercentSlider::PercentSlider(const QString& text, QWidget *parent, int value, int maxValue): QWidget(parent)
{
    auto *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    auto *label = new QLabel(text, this);
    label->setFixedWidth(60);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setMinimum(0);
    slider->setMaximum(maxValue);
    slider->setTickInterval(25);
    slider->setValue(value);

    layout->addWidget(label);
    layout->addWidget(slider);

    this->setLayout(layout);
}

Indicator::Indicator(const QString& name, QWidget *parent): QWidget(parent) {
    auto *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    label = new QLabel(name, this);
    status = new QLabel(parent);
    status->setFixedWidth(100);
    layout->addWidget(label);
    layout->addWidget(status);
    this->setLayout(layout);
}

void Indicator::setStatus(const string& s, int color) {
    if (color == 1)
        status->setStyleSheet("QLabel { color : white; background-color: red; font-weight: bold; }");
    else if (color == 2)
        status->setStyleSheet("QLabel { color : black; background-color: yellow; font-weight: bold; }");
    else if (color == 3)
        status->setStyleSheet("QLabel { color : white; background-color: green; font-weight: bold; }");
    else
        status->setStyleSheet("QLabel { color : white; font-weight: bold; }");
    status->setText(QString::fromStdString(s));
}
