find_program(LIBMESH_CONFIG NAMES libmesh-config PATHS ENV PATH)

if (LIBMESH_CONFIG)
    execute_process(COMMAND ${LIBMESH_CONFIG} --include
            OUTPUT_VARIABLE LIBMESH_INCLUDE_DIRS
            OUTPUT_STRIP_TRAILING_WHITESPACE) #returning multiple paths I need to find out a way to
    #reconstruct it

    execute_process(COMMAND ${LIBMESH_CONFIG} --libs
            OUTPUT_VARIABLE LIBMESH_LINK_FLAGS
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    separate_arguments(LIBMESH_INCLUDE_DIRS UNIX_COMMAND "${LIBMESH_INCLUDE_DIRS}")
    list(TRANSFORM LIBMESH_INCLUDE_DIRS REPLACE "^-I" "")
    set(LibMesh_FOUND TRUE)
    message("LibMesh include: ${LIBMESH_INCLUDE_DIRS}")
    message("LibMesh lib: ${LIBMESH_LINK_FLAGS}")

else()
    set(LibMesh_FOUND FALSE)
    message("LibMesh not found")
endif()