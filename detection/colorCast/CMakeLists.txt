cmake_minimum_required( VERSION 3.0 )
project( maslab-cars-vision )

set(CMAKE_CXX_STANDARD 14)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# sources list
add_executable( colorCast
        main.cpp
        colorCast.cpp
        colorCast.h)

target_link_libraries( colorCast ${OpenCV_LIBS} )
