file(GLOB TEST_SOURCES *.cpp)

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME}
            MeshAmalgamationClustering
            ${LIBMESH_LINK_FLAGS}
    )
endforeach()