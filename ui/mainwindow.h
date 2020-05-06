#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QButtonGroup>
#include <QPushButton>
#include "settingsLayout.h"
#include "video.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT
    QTimer _timer;

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *videoLayout;
    QGraphicsView *inputVideo;
    QGraphicsView *outputVideo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusbar;
    Stream *vid;
    QGraphicsPixmapItem *inPixmap;
    QGraphicsPixmapItem *outPixmap;

    void createVideoLayout(QVBoxLayout *parent);

private slots:
    void openFile();

    void closeFile();

    void showAbout();

    void setupUi(QMainWindow *MainWindow);

    void createMenuBar(QMainWindow *MainWindow);

    void showFrames();

    void rotate();

    void resizeEvent(QResizeEvent *) override;
};


#endif // UI_MAINWINDOW_H
