cmake_minimum_required(VERSION 3.21)

project(stream-frames-example)

include(GNUInstallDirs)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/_out)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ggdb")
list(APPEND C_CXX_WARNING_FLAGS
    -Wall
    -W
    -Wwrite-strings
    -Wno-missing-field-initializers
    -Wno-misleading-indentation
)
add_compile_options(${C_CXX_WARNING_FLAGS})

set(SCHEMAS_SOURCE_DIR ../../dist/automotive-bus-schema/flatbuffers/c)
set(FLATCC_SOURCE_DIR ${SCHEMAS_SOURCE_DIR}/automotive_bus_schema/flatcc/src)
set(FLATCC_INCLUDE_DIR ${SCHEMAS_SOURCE_DIR}/automotive_bus_schema/flatcc/include)


add_executable(frames
    frames.c
    ${FLATCC_SOURCE_DIR}/builder.c
    ${FLATCC_SOURCE_DIR}/emitter.c
    ${FLATCC_SOURCE_DIR}/refmap.c
)
target_include_directories(frames
    PRIVATE
        ${SCHEMAS_SOURCE_DIR}
        ${FLATCC_INCLUDE_DIR}
)
install(TARGETS frames)
