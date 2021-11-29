# Copyright (C) 2021 Robert Bosch GmbH

cmake_minimum_required(VERSION 3.18)

project(Example)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O3")
list(APPEND C_CXX_WARNING_FLAGS
    -Wall
    -W
    -Wwrite-strings
    -Wno-missing-field-initializers
    -Wno-misleading-indentation
)
add_compile_options(${C_CXX_WARNING_FLAGS})


# Schemas
# =======
set(AB_SCHEMAS_SOURCE_DIR ../../dist/automotive-bus-schema/flatbuffers/c)
set(AB_SCHEMAS_FLATCC_DIR ${AB_SCHEMAS_SOURCE_DIR}/automotive_bus_schema/flatcc)


# Target
# =======
add_executable(example
    example.c
    ${AB_SCHEMAS_FLATCC_DIR}/src/builder.c
    ${AB_SCHEMAS_FLATCC_DIR}/src/emitter.c
    ${AB_SCHEMAS_FLATCC_DIR}/src/refmap.c
)
target_include_directories(example
    PRIVATE
        ${AB_SCHEMAS_SOURCE_DIR}
        ${AB_SCHEMAS_FLATCC_DIR}/include
)
target_link_libraries(example
    PRIVATE
        m
)


# Install
# =======
install(TARGETS example)
