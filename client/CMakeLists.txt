cmake_minimum_required(VERSION 3.6.2)
project(dchat_client)

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
# Executable
add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/chat_client.cpp
  src/chat_client.hpp
)

# Static library dependencies
add_subdirectory(../common dchat_common)
target_link_libraries(${PROJECT_NAME} PRIVATE dchat_common)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32.lib)
endif()