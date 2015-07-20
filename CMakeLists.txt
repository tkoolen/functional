cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0042 NEW)
project(Functional)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#FIXME: hack due to https://youtrack.jetbrains.com/issue/CPP-270
FILE (GLOB_RECURSE clion_all_headers ${CMAKE_SOURCE_DIR}/*.h)
ADD_CUSTOM_TARGET(all_clion
    SOURCES ${clion_all_headers}
)

add_subdirectory(src)
add_subdirectory(test)
