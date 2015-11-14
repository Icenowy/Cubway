project(cubway-xdg)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(QT5XDG)

add_library(Xdg SHARED xdg.cpp)
target_link_libraries(Xdg Qt5Xdg Qt5::Core Qt5::Gui)
