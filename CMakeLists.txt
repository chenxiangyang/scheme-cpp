cmake_minimum_required(VERSION 3.2)

PROJECT(scheme-cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

ADD_EXECUTABLE(scheme ${DIR_SRCS})

