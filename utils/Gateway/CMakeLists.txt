##
## Copyright © 2016-2025 AMBITECS <info@ambi.biz>
##
cmake_minimum_required(VERSION 3.20)
project( PRO-gateway VERSION 1.0.1 DESCRIPTION "Procont gateway library" LANGUAGES CXX )
MESSAGE("------------------- PROJECT: ${PROJECT_NAME} BEGIN")
set( PROJECT_SO_VERSION "1"  )
set( CMAKE_CXX_STANDARD 17   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( PROJ ${PROJECT_NAME} )             # PROJ = project name in orig case
string ( TOLOWER ${PROJECT_NAME} proj )  # proj = project name in lowercase

set( PROJ_DIR  ${CMAKE_CURRENT_SOURCE_DIR} ) # PROJ project  directory
set( CMAKE_DIR ${PROJ_DIR}/../../.cmake    ) # PROJ cmake files directory
set( PROJ_SRC_DIR ${PROJ_DIR}/src          ) # PROJ sources directory
set( PROJ_INS_DIR ${PROJ_DIR}/$install     ) # PROJ install directory

message(STATUS "SOURCES == ${PROJ_SRC_DIR}")
message(STATUS "INSTALL == ${PROJ_INS_DIR}")

#### CONFIGURATION ####
set(LIBPRO_GATEWAY_VERSION       ${PROJECT_VERSION})
set(LIBPRO_GATEWAY_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(LIBPRO_GATEWAY_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(LIBPRO_GATEWAY_VERSION_MICRO ${PROJECT_VERSION_PATCH})

#--- ADD CONFIG HERE ---
#configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(
        ${PROJ_DIR}/pro-gateway-version.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/pro-gateway-version.h
)
configure_file(
        ${CMAKE_CURRENT_BINARY_DIR}/pro-gateway-version.h
        ${PROJ_SRC_DIR}/pro-gateway-version.h
        COPYONLY
)

# -----------------------------------------------------------------------------
#### BUILD ####
# -----------------------------------------------------------------------------
include(${CMAKE_DIR}/build_tools.cmake)
include(GNUInstallDirs)

### For Install include files (variant-#1)
set(PRO_GATEWAY_PUBLIC_HEADERS
        ${PROJ_SRC_DIR}/VARIANT.h
        ${PROJ_SRC_DIR}/gateway.h
        ${CMAKE_CURRENT_BINARY_DIR}/pro-gateway-version.h
)

option(BUILD_SHARED_LIBS "Build ${proj} as a shared library" ON)

# ---------------------------------------------------
### TARGET: pro-gateway (shared lib)  ###
# ---------------------------------------------------
build_target( ${proj} LIB SHARED
        INCS ${PROJ_SRC_DIR}
        SRCS
        :MASK ${PROJ_SRC_DIR}/*.cpp
)

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE -D_GNU_SOURCE -Wall -Wextra)
endif()

target_include_directories(${proj} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${proj} PROPERTIES PUBLIC_HEADER "${PRO_GATEWAY_PUBLIC_HEADERS}")

target_include_directories(${proj} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${proj}>
)

set(LIBPRO_GATEWAY_SOVERSION_VERSION   ${PROJECT_VERSION})
set(LIBPRO_GATEWAY_SOVERSION_SOVERSION ${PROJECT_SO_VERSION})

set_target_properties(${proj} PROPERTIES
        VERSION   ${LIBPRO_GATEWAY_SOVERSION_VERSION}
        SOVERSION ${LIBPRO_GATEWAY_SOVERSION_SOVERSION}
)

# -----------------------------------------------------------------------------
#### INSTALL ####
#-------------------------------------------------------------------------------
set( CMAKE_INSTALL_PREFIX  ${PROJ_INS_DIR} ) # CMake install path

message("== CMAKE_INSTALL_PREFIX:       ${CMAKE_INSTALL_PREFIX}")
message("== ABSOLUTE_INSTALL_PREFIX:    ${ABSOLUTE_INSTALL_PREFIX}")
message("== CMAKE_INSTALL_LIBDIR:       ${CMAKE_INSTALL_LIBDIR}")
message("== CMAKE_INSTALL_INCLUDEDIR:   ${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS ${proj}     # shared library
        EXPORT lib${proj}Config # library Config for export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        # Include files without sub-directories hierarchy (variant #1)
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${proj}
)

## Install include files with sub-directories hierarchy (variant #2)
#install(DIRECTORY   ${PROJ_SRC_DIR}/Sub-directory/
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${proj}/Sub-directory
#        FILES_MATCHING
#        PATTERN "*.h*"
#)

install(EXPORT lib${proj}Config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)

get_filename_component(ABSOLUTE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} ABSOLUTE)

message("== ABSOLUTE_INSTALL_PREFIX : ${ABSOLUTE_INSTALL_PREFIX}")
message("== CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("== CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("== CMAKE_INSTALL_LIBDIR    : ${CMAKE_INSTALL_LIBDIR}")
message("== CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

set(prefix     : ${ABSOLUTE_INSTALL_PREFIX})
set(exec_prefix: ${ABSOLUTE_INSTALL_PREFIX})
set(libdir     : "\${prefix}/${CMAKE_INSTALL_LIBDIR}")
set(includedir : "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/libpro-gateway.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/libpro-gateway.pc
        @ONLY
)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/libpro-gateway.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

# ---------------------------------------------------
