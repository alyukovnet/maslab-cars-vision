cmake_minimum_required( VERSION 3.0 )
project( maslab-cars-vision )

set(CMAKE_CXX_STANDARD 14)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(correction)
add_subdirectory(detection)

# sources list
add_executable( main
        main.cpp
        detection/detection.h
        detection/detection.cpp
        correction/correction.h
        correction/correction.cpp)

target_link_libraries( main ${OpenCV_LIBS} )
