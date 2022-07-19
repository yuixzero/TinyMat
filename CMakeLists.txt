cmake_minimum_required(VERSION 3.10)
project(Mat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -pthread")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE"-O3")

add_executable(Mat main.cpp Mat.cpp Thread.hpp)


