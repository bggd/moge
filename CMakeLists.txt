cmake_minimum_required(VERSION 2.8)

project(MogeProj CXX)

option(MOGE_GL_BACKEND_OGL "Use OpenGL for moge::gl backend" OFF)
option(MOGE_GL_BACKEND_D3D11 "Use Direct3D 11 for moge::gl backend" OFF)

if(MOGE_GL_BACKEND_OGL)
  add_definitions(-DMOGE_USE_OPENGL)
elseif(MOGE_GL_BACKEND_D3D11)
  add_definitions(-DMOGE_USE_DIRECT3D11)
endif()

add_library(moge-gl src/gl/gl.cpp)
