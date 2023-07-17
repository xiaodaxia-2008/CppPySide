cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)

project(cpp-pyside)

# set(Python_ROOT_DIR "$ENV{HOME}/AppData/Local/Programs/Python/Python310/python.exe" CACHE STRING "Python root dir" FORCE)
# find_package(Python 3.10 REQUIRED COMPONENTS Interpreter Development)
# message(STATUS "Python_EXECUTABLE:${Python_EXECUTABLE}")
add_subdirectory(pybind11)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(cpp-pyside1 main.cpp)
target_link_libraries(cpp-pyside1 PRIVATE pybind11::embed Qt::Widgets)

add_executable(cpp-pyside2 main2.cpp)
target_link_libraries(cpp-pyside2 PRIVATE pybind11::embed)