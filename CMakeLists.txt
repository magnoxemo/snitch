cmake_minimum_required(VERSION 3.26)
project(snitch)

find_package(Eigen3 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(LibMesh REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIBMESH_INCLUDE_DIRS})

file(GLOB SNITCH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set(CMAKE_CXX_COMPILER mpicxx)

add_subdirectory(src)
add_subdirectory(test_cases)