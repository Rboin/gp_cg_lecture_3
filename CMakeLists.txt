cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)
project(lec_3)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

link_libraries(${SDL2_LIBRARY})


set(SOURCE_FILES main.cpp vector.h vector.cpp)

#target_link_libraries(lec_3, ${SDL2_LIBRARY})

add_executable(lec_3 ${SOURCE_FILES})


