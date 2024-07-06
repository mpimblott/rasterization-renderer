cmake_minimum_required(VERSION 3.22)

project(RasterizeRenderer)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  RasterizeRenderer
  main.cpp
  vector.h
  vector.cpp
  matrix.h
  matrix.cpp
)

# include the external library at /external/stb_image.h
include_directories(external)
