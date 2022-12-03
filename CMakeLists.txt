cmake_minimum_required(VERSION 3.23)
project(circle_detection)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_executable(circle_detection main.cpp Point.hpp Circle.hpp ransac.hpp)

target_link_libraries(circle_detection fmt::fmt)
