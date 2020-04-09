cmake_minimum_required( VERSION 3.0 )
project( maslab-cars-vision )

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# sources list
add_executable( detection
        main.cpp
        detection.cpp
        detection.h)

target_link_libraries( detection ${OpenCV_LIBS} )
