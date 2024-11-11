cmake_minimum_required(VERSION 3.1)
project(OpenCV_Test)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main aruco_detection.cpp)
target_link_libraries(main ${OpenCV_LIBS})
