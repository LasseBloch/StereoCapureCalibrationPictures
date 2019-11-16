cmake_minimum_required(VERSION 3.13)
project(StereoCapureCalibrationPictures)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(StereoCapureCalibrationPictures main.cpp)

target_link_libraries(StereoCapureCalibrationPictures ${OpenCV_LIBS})