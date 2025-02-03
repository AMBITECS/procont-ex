###############################################################################
#                                                                             #
#                                  matiec                                     #
#                        Copyright (c) 2024 AMBITECS                          #
#                                                                             #
###############################################################################

cmake_minimum_required(VERSION 3.5)
project(libmodbus)

set(SRC_LIST_MASK ac am c cc def h hh ll Makefile mk txt xml yy)

list(TRANSFORM SRC_LIST_MASK PREPEND "*.")

file(
    GLOB_RECURSE
    SRC_LIST
    LIST_DIRECTORIES false
    "${SRC_LIST_MASK}"
)

set(
    OUT_LIST
    iec2c
    iec2iec
)

add_custom_command(
    OUTPUT
        ${OUT_LIST}
    COMMAND
        ./autogen.sh
    COMMAND
        ./configure --enable-static
    COMMAND
        make
    DEPENDS
        "${SRC_LIST}"
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR}
    COMMENT
        "Compiling ${PROJECT_NAME} ..."
    VERBATIM
)

add_custom_target(
    libmodbus ALL
    SOURCES
        "${SRC_LIST}"
    DEPENDS
        ${OUT_LIST}
)
