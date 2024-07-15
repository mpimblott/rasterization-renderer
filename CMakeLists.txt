cmake_minimum_required(VERSION 3.22)

project(RasterizeRenderer)

set(CMAKE_CXX_STANDARD 20)

add_executable(
  RasterizeRenderer
  main.cpp
  vector.h
  )
  
target_compile_features(RasterizeRenderer PRIVATE cxx_std_20)

# include the external library at /external/stb_image.h
include_directories(external)
