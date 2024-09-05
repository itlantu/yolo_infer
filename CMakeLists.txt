cmake_minimum_required(VERSION 3.22)
project(yolo_infer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories("include")

add_executable(yolo_infer main.cpp)

find_package(utils MODULE REQUIRED)
find_package(project_opencv MODULE REQUIRED)
find_package(project_onnxruntime MODULE REQUIRED)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)