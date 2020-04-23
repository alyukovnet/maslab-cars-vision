/*!
\file
\brief Заголовочный файл с описанием класса Interface

Данный файл содержит в себе определения класса Interface

*/

#ifndef MASLAB_CARS_VISION_INTERFACE_H
#define MASLAB_CARS_VISION_INTERFACE_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <fstream>

using namespace std;
using namespace cv;

/*!
	\brief Обработчик входного видео и интерфейс записи логов

	Данный класс анализирует входные аргументы программы,
    отвечает за первичную обработку кадров (поворот, отражение),
    вывод информации в консоль и вывод логов с видео в файлы
*/
class Interface {
private:
    // Objects
    VideoCapture cap;          ///< Input video
    VideoWriter inputWriter;   ///< Modified input video
    VideoWriter outputWriter;  ///< Output video
    ofstream file;             ///< Text logs file
    // Args
    String videoSource;        ///< Input video path
    String logFileName;        ///< Name for log file
    // Flags
    bool repeat;
    int rotateFlag;
    int flipCode;
public:
    //! Конструктор, обработка аргументов программы
    Interface(int argc, char *argv[]);

    //! Открытие файлов на запись/чтение
    void start();

    /*!
    Вывод логов в консоль и файл (если указана директория для логов)
    \param[in] s Строка
    */
    void log(String s);

    /*!
    Копирует содержимое из исходной области памяти в целевую область память
    \param[out] dest Кадр (объект cv::Mat)
    \result Флаг существования кадра. Если видео зациклено, то всегда true
    */
    bool getFrame(Mat& frame);

    //! Закрывает файлы
    ~Interface();
};

#endif //MASLAB_CARS_VISION_INTERFACE_H