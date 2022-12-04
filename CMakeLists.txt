cmake_minimum_required(VERSION 3.23)
project(circle_detection)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(circle_detection main.cpp Point.hpp Circle.hpp Ransac.hpp Ransac.cpp Circle.cpp)
target_link_libraries(circle_detection fmt::fmt  ${OpenCV_LIBS} ${Boost_SYSTEM_LIBRARY})
