cmake_minimum_required(VERSION 3.10)

project(MogeProj CXX)

include(CTest)

set(MOGE_SDL2_INC_DIR "" CACHE FILEPATH "")
set(MOGE_SDL2_LIB_DIR "" CACHE FILEPATH "")

find_library(SDL2_LIBRARY
  NAMES SDL2.lib SDL2main.lib
  HINTS ${MOGE_SDL2_LIB_DIR})

add_library(moge-gl-d3d11 OBJECT
  src/gl/d3d11/context.cpp
  src/gl/d3d11/vertex_buffer.cpp
  src/gl/d3d11/texture.cpp
  src/gl/d3d11/uniform_array.cpp
  src/gl/d3d11/shader.cpp
  src/gl/d3d11/gl.cpp)

add_library(moge-gl-ogl OBJECT
  src/gl/ogl/bind.cpp
  src/gl/ogl/context.cpp
  src/gl/ogl/vertex_buffer.cpp
  src/gl/ogl/texture.cpp
  src/gl/ogl/uniform_array.cpp
  src/gl/ogl/shader.cpp
  src/gl/ogl/gl.cpp)

add_library(moge-sdl OBJECT
  src/macro.hpp
  src/sdl/sdl.hpp
  src/sdl/sdl.cpp)
target_include_directories(moge-sdl PRIVATE
  ${MOGE_SDL2_INC_DIR})

add_library(moge
  $<TARGET_OBJECTS:moge-gl-d3d11>
  $<TARGET_OBJECTS:moge-sdl>)
target_link_libraries(moge PRIVATE ${SDL2_LIBRARY})


if(BUILD_TESTING)
  add_library(gtest STATIC
    googletest/googletest/src/gtest-all.cc)
  target_include_directories(gtest PUBLIC
    googletest/googletest/include googletest/googletest)

  add_executable(test-moge tests/main.cpp)
  target_include_directories(test-moge PRIVATE
    ${MOGE_SDL2_INC_DIR})
  target_link_libraries(test-moge PRIVATE gtest)
  target_link_libraries(test-moge PRIVATE moge)

  add_test(NAME TestMoge COMMAND test-moge)
endif()
