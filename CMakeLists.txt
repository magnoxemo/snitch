cmake_minimum_required(VERSION 3.28)
project(snitch)

set(LIBMESH_INCLUDE_PATH "/home/ebny_walid/libmesh_opt/include")
set(LIBMESH_LINK_PATH "/home/ebny_walid/libmesh_opt/lib")
set(EIGEN_PATH "/usr/include/eigen3")

set(SNITCH_INCLUDE_PATH "/home/ebny_walid/Documents/github/snitch/include")
set(SNITCH_SRC_PATH "/home/ebny_walid/Documents/github/snitch/src")

#magic part (stack overflow )that I don't fully understand
#it's forcing cmake not to change dir of the precompiled libmesh.so file

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${LIBMESH_LINK_PATH})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${LIBMESH_LINK_PATH}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${LIBMESH_LINK_PATH}")
endif()
#

include_directories(${LIBMESH_INCLUDE_PATH})
include_directories(${EIGEN_PATH})
include_directories(${SNITCH_INCLUDE_PATH})

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
set(MPI_LIBRARIES ${MPI_LIBRARIES})
set(SOURCE_FILES src/EqualNeighborHeuristic.cpp  src/MeshAmalgamationBase.cpp)
file(GLOB SNITCH_SOURCES ${SNITCH_SRC_PATH}/*.cpp)
set(EXE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "-O2 -felide-constructors -fstrict-aliasing -Wdisabled-optimization -funroll-loops -ftrapping-math -fopenmp")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set(CMAKE_CXX_COMPILER "mpicxx")

add_executable(testLocalMeanHeuristics test_cases/testLocalMeanHeuristics.cpp ${SOURCE_FILES} ${SNITCH_SOURCES})
add_executable(testEqualNeighborHeuristics test_cases/testEqualNeighborHeuristic.cpp ${SOURCE_FILES} ${SNITCH_SOURCES})
add_executable(testSigmaHeuristics test_cases/testSigmaHeuristics.cpp ${SOURCE_FILES} ${SNITCH_SOURCES})

target_link_libraries(testLocalMeanHeuristics
        ${MPI_LIBRARIES}
        -L${LIBMESH_LINK_PATH}
        -lmesh_opt
        -ltimpi_opt
        -lnglib
        -lngcore
        -lz
        -ltirpc
)

target_link_libraries(testEqualNeighborHeuristics
        ${MPI_LIBRARIES}
        -L${LIBMESH_LINK_PATH}
        -lmesh_opt
        -ltimpi_opt
        -lnglib
        -lngcore
        -lz
        -ltirpc
)

target_link_libraries(testSigmaHeuristics
        ${MPI_LIBRARIES}
        -L${LIBMESH_LINK_PATH}
        -lmesh_opt
        -ltimpi_opt
        -lnglib
        -lngcore
        -lz
        -ltirpc
)