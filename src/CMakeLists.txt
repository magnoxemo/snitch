file(GLOB SNITCH_SOURCES *.cpp)

add_library(MeshAmalgamationClustering SHARED ${SNITCH_SOURCES})

target_link_libraries(MeshAmalgamationClustering
        ${LIBMESH_LINK_FLAGS}
)