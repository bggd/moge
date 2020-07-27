cmake_minimum_required(VERSION 3.10)

project(MogeProj CXX)

include(CTest)

add_library(moge-gl OBJECT
  src/gl/gl.cpp)


if(BUILD_TESTING)
endif()
