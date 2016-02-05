cmake_minimum_required(VERSION 2.8.11)

project(cubway)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5WebKit)
find_package(Qt5WebKitWidgets)
find_package(Qt5DBus)

add_definitions("-DCUBWAY_DEBUG=1")
# Tell CMake to create the executable
add_executable(cubway main.cpp View.cpp Controller.cpp moduleloader.cpp DBusInterface.cpp FileSystem.cpp Process.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(cubway Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets Qt5::DBus)
