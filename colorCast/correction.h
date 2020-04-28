/*!
\file
\brief ColorCast correction module

Данный файл содержит в себе определения функций для
исправления ColorCast

*/

#ifndef MASLAB_CARS_VISION_COLORCAST_CORRECTION_H
#define MASLAB_CARS_VISION_COLORCAST_CORRECTION_H

#include <opencv2/core.hpp>
using namespace cv;


class ColorCast {
private:
    double CastFactor_;  //!< Описание
    double mean_a_;      //!< Mean of channel a
    double mean_b_;      //!< Mean of channel b
    double D_;           //!< Описание
    double M_a_;         //!< Описание
    double M_b_;         //!< Описание
    double M_;           //!< Описание
    Mat inputLab_;       //!< Lab image
public:
    /*!
    Конструктор класса ColorCast
    \param[in] input Входной кадр (объект cv::Mat) BGR
    \param[out] output Выходной кадр (объект cv::Mat) BGR
    */
    ColorCast();

    //! Результаты обнаружения ColorCast
    enum ColorCastFlags {
        NO_CAST = 0,              //!< No cast
        MILD = 1,                 //!< Color Cast is normal
        DETECTED = 2,             //!< You can use ColorCast correction for frame
        INCOMPATIBLE_CAMERA = 3,  //!< You can't use ColorCast correction
    };

    /*!
    Обнаружение ColorCast
    \param[out] output Код ошибки
    */
    int detect(Mat& input);

    /*!
    Обнаружение ColorCast
    \param[out] output Код ошибки
    */
    double getCastFactor();

    /*!
    Устраняет проблему ColorCast
    */
    void correct(Mat& input, Mat& output);

    ~ColorCast();
};


void castVariator(Mat& dest, Mat& src, int Red, int Green, int Blue);


#endif //MASLAB_CARS_VISION_COLORCAST_CORRECTION_H