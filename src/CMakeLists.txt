cmake_minimum_required(VERSION 3.22)

project(Renderer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
  Renderer
  main.cpp
  camera.cpp
  geometry.cpp
  ppm.cpp
  )
  
target_compile_features(Renderer PRIVATE cxx_std_11)

