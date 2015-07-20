cmake_minimum_required(VERSION 2.8)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()
project(Functional)

include(ExternalProject)
ExternalProject_Add(eigen
  PREFIX eigen
  URL https://bitbucket.org/eigen/eigen/get/3.2.4.tar.bz2
  URL_HASH MD5=4c4b5ed9a388a1e475166d575af25477
  CMAKE_ARGS -D CMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR} EIGEN_BUILD_PKGCONFIG=ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_BINARY_DIR}/eigen/src/eigen)

#FIXME: hack due to https://youtrack.jetbrains.com/issue/CPP-270
FILE (GLOB_RECURSE clion_all_headers ${CMAKE_SOURCE_DIR}/*.h)
ADD_CUSTOM_TARGET(all_clion
    SOURCES ${clion_all_headers}
)

add_subdirectory(src)
add_subdirectory(test)
