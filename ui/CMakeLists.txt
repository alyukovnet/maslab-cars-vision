cmake_minimum_required(VERSION 3.5)

project(maslab-cars-vision LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(maslab-cars-vision
        main.cpp
        mainwindow.cpp
        mainwindow.h
        video.cpp
        video.h
        settingsLayout.cpp
        settingsLayout.h
        ../colorCast/colorCast.h
        ../colorCast/colorCast.cpp
)

target_link_libraries(maslab-cars-vision PRIVATE Qt5::Widgets ${OpenCV_LIBS} )
