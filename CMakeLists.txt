cmake_minimum_required(VERSION 3.26)
project(snitch)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED)
find_package(LibMesh REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${LIBMESH_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SNITCH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

add_subdirectory(src)
add_subdirectory(test_cases)