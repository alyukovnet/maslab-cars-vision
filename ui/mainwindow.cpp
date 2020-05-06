#include "mainwindow.h"
#include <QFileDialog>
#include <QWidget>
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QMessageBox>
#include <QCommandLineParser>

#include "settingsLayout.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), _timer(this)
{
    setupUi(this);
    QCommandLineParser parser;
    QCoreApplication::setApplicationName("Maslab Cars Vision project");
    QCoreApplication::setApplicationVersion("1.1.0 beta");
    parser.setApplicationDescription("Computer vision for self-driving cars");
    //parser.addPositionalArgument("input", tr("Input video"));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(showFrames()));
}

void MainWindow::setupUi(QMainWindow *MainWindow)
{
    MainWindow->setEnabled(true);
    MainWindow->resize(1000, 600);
    MainWindow->setMinimumSize(QSize(800, 400));
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Maslab Cars Vision", nullptr));

    createMenuBar(MainWindow);

    statusbar = new QStatusBar(MainWindow);
    MainWindow->setStatusBar(statusbar);
    statusbar->showMessage(tr("Select file to open"));

    centralwidget = new QWidget(this);
    verticalLayout = new QVBoxLayout(centralwidget);

    createVideoLayout(verticalLayout);

    auto *settings = new SettingsLayout(centralwidget);
    vid = new Stream(settings);
    connect(settings->openButton, SIGNAL(released()), this, SLOT(openFile()));
    connect(settings->rotateButton, SIGNAL(pressed()), this, SLOT(rotate()));
    connect(settings->redSlider->slider, SIGNAL(valueChanged(int)), vid, SLOT(setRedCast(int)));
    connect(settings->greenSlider->slider, SIGNAL(valueChanged(int)), vid, SLOT(setGreenCast(int)));
    connect(settings->blueSlider->slider, SIGNAL(valueChanged(int)), vid, SLOT(setBlueCast(int)));
    connect(settings->dirtSlider->slider, SIGNAL(valueChanged(int)), vid, SLOT(setDirt(int)));
    connect(settings->dirtCountSlider->slider, SIGNAL(valueChanged(int)), vid, SLOT(setDirtCount(int)));
    connect(settings->blurSlider, SIGNAL(stateChanged(int)), vid, SLOT(setBlur(int)));
    verticalLayout->addWidget(settings);

    MainWindow->setCentralWidget(centralwidget);

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::rotate()
{
    inputVideo->rotate(90);
    outputVideo->rotate(90);
}

void MainWindow::createMenuBar(QMainWindow *MainWindow)
{
    menubar = new QMenuBar(MainWindow);
    menubar->setNativeMenuBar(false); // todo: resolve problem, doesn't work on macOS

    // File menu
    menuFile = new QMenu(menubar);
    menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
    menubar->addAction(menuFile->menuAction());

    menuFile->addAction("Open", this, &MainWindow::openFile);
    menuFile->addAction("Close", this, &MainWindow::closeFile);
    menuFile->addAction("Quit", QApplication::instance(), SLOT(quit()));

    // About menu
    menuAbout = new QMenu(menubar);
    menuAbout->setTitle(QCoreApplication::translate("MainWindow", "&About", nullptr));
    menubar->addAction(menuAbout->menuAction());

    menuAbout->addAction("About project", this, &MainWindow::showAbout);
    menuAbout->addAction("About Qt", QApplication::instance(), SLOT(aboutQt()));

    MainWindow->setMenuBar(menubar);
}

void MainWindow::createVideoLayout(QVBoxLayout *parent)
{
    videoLayout = new QHBoxLayout();

    inputVideo = new QGraphicsView(centralwidget);
    videoLayout->addWidget(inputVideo);
    inPixmap = new QGraphicsPixmapItem;

    outputVideo = new QGraphicsView(centralwidget);
    videoLayout->addWidget(outputVideo);
    outPixmap = new QGraphicsPixmapItem;

    parent->addLayout(videoLayout);
}


void MainWindow::openFile()
{
    closeFile();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.mp4 *.mov *.avi)"));
    if (fileName.length() > 0) {
        if (vid->open(fileName.toStdString())) {
            vid->refresh();
            inputVideo->setScene(new QGraphicsScene(this));
            inPixmap = new QGraphicsPixmapItem;
            inputVideo->scene()->addItem(inPixmap);
            outputVideo->setScene(new QGraphicsScene(this));
            outPixmap = new QGraphicsPixmapItem;
            outputVideo->scene()->addItem(outPixmap);
            _timer.start(vid->getDelay());
            statusbar->showMessage(fileName);
        } else {
            statusbar->showMessage(tr("Can't open file"), 5000);
        }
    } else {
        statusbar->showMessage(tr("No file selected"), 5000);
    }
}

void MainWindow::closeFile()
{
    _timer.stop();
    vid->close();
    delete inputVideo->scene();
    delete outputVideo->scene();
    statusbar->showMessage(tr("Select file to open"));
}

void MainWindow::showAbout()
{
    QString infoText = QString::fromUtf8("Maslab Cars Vision project 1.1.0 Beta");
    QMessageBox::information(this, tr("About"), infoText);
}

void MainWindow::showFrames()
{
    vid->process();
    inPixmap->setPixmap(vid->getInFrame());
    outPixmap->setPixmap(vid->getOutFrame());
    inputVideo->fitInView(inPixmap, Qt::KeepAspectRatio);
    outputVideo->fitInView(outPixmap, Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    inputVideo->fitInView(inPixmap, Qt::KeepAspectRatio);
    outputVideo->fitInView(outPixmap, Qt::KeepAspectRatio);
}
