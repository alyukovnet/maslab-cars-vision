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


/*!
Устраняет проблему ColorCast
\param[in] input Входной кадр (объект cv::Mat) BGR
\param[out] output Результат обработки (объект cv::Mat)
*/
void colorCastCorrection(Mat& input, Mat& output);


/*!
Умножает коэффициенты (3) соответсвенно на значение
 каждого канала пикселя
\param[in] input Входной кадр (объект cv::Mat) BGR
\param[out] output Результат обработки (объект cv::Mat) BGR
\param[in] k Коэффициенты для 3-х каналов
*/
void applyColorsCoef(Mat& input, Mat& output, float k[3]);


#endif //MASLAB_CARS_VISION_COLORCAST_CORRECTION_H