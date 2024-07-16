cmake_minimum_required(VERSION 3.22)

project(RasterizeRenderer)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  RasterizeRenderer
  main.cpp
  )
  
target_compile_features(RasterizeRenderer PRIVATE cxx_std_11)

