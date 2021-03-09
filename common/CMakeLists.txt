cmake_minimum_required(VERSION 3.6.2)
project(dchat_common)

############################
# Compiler options (for all targets)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Compiling with ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-Wall -pedantic -Wextra)
endif()

############################
# Common library
add_library(${PROJECT_NAME}
    src/networking.hpp
    src/networking.cpp
    src/dchat.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./src)
