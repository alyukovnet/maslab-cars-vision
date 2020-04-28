cmake_minimum_required( VERSION 3.0 )
project( maslab-cars-vision )

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# add_subdirectory(colorCast/correction)

# sources list
add_executable( main
        main.cpp
        core/interface.h
        core/interface.cpp
        colorCast/colorCast.h
        colorCast/colorCast.cpp)

target_link_libraries( main ${OpenCV_LIBS} )
