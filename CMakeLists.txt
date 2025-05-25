cmake_minimum_required(VERSION 3.25)
project( PROCONT-EX
         VERSION 1.0.1
         DESCRIPTION "Procont execution environment"
         LANGUAGES CXX
)
MESSAGE("------------------- PROJECT: ${PROJECT_NAME} BEGIN")

string( TOLOWER ${PROJECT_NAME}  proj )      # proj = project name in lowercase
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          17   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( PROJ_DIR  ${CMAKE_CURRENT_SOURCE_DIR} ) # PROJ project directory
set( CMAKE_DIR ${PROJ_DIR}/.cmake          ) # PROJ cmake files directory

# === SET CMAKE_PREFIX_PATH ===
if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH   "/home/master/Qt/6.7.1/gcc_64/")
    MESSAGE(STATUS "SET CMAKE_PREFIX_PATH to ${CMAKE_PREFIX_PATH}")
endif()

# === SET ST_FILE param ===
if(NOT DEFINED ST_FILE)
    MESSAGE(STATUS "SET ST_FILE to DEFAULT \"./st_files/plc.st\"")
    set(ST_FILE ${PROJ_DIR}/st_files/plc.st) # DEFAULT ST source file
else()
    if((NOT EXISTS "${ST_FILE}") OR (IS_DIRECTORY "${ST_FILE}"))
        #MESSAGE(STATUS "(1) ST_FILE = ${ST_FILE}")
        if(NOT ("${ST_FILE}" STREQUAL ""))
            set (ST_FILE ${PROJ_DIR}/st_files/${ST_FILE})
        endif()
        #MESSAGE(STATUS "(2) ST_FILE = ${ST_FILE}")
        if((NOT EXISTS "${ST_FILE}") OR (IS_DIRECTORY "${ST_FILE}"))
            MESSAGE(FATAL_ERROR "- ${ST_FILE} is not a file")
        endif()
    endif()
endif()

# === rem this lines for cross-compiling ===
# set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")

# Set the installation path to the prefix path so that "find_package" looks into it
#file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_INSTALL_PREFIX})
# ==========================================
message(STATUS "C++   COMPILER  : ${CMAKE_CXX_COMPILER}!")
message(STATUS "CMake GENERATOR : ${CMAKE_GENERATOR}")
message(STATUS "CMake BUILD_TYPE: ${CMAKE_BUILD_TYPE}\n")

message(STATUS "CMake prefix  path: \"${CMAKE_PREFIX_PATH}\"")
message(STATUS "CMake project path: \"${CMAKE_SOURCE_DIR}\"")
message(STATUS "CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")

#-------------------------------------------------------------------------------
# PROJ Project specific PVs
set( PROJ_SRC_DIR   ${PROJ_DIR}           ) # PROJ sources directory
set( PROJ_IEC_DIR   ${PROJ_DIR}/iec       ) # PROJ iec2c directory
set( PROJ_LIB_DIR   ${PROJ_DIR}/lib       ) # PROJ includes directory
set( PROJ_SUB_DIR   ${PROJ_DIR}/utils     ) # PROJ submodule directory
set( PROJ_CMP_DIR   ${PROJ_DIR}/matiec    ) # IEC to C compiler directory
set( PROJ_INS_DIR   ${PROJ_DIR}/$install  ) # local install directory
set( PROJ_IEC2C     ${PROJ_CMP_DIR}/iec2c ) # IEC to C compiler
set( PROJ_ST_FILE   ${ST_FILE}            ) # SOURCE ST_FILE

set( CMAKE_INSTALL_PREFIX ${PROJ_INS_DIR} )
set( CMAKE_MODULE_PATH ${CMAKE_DIR} ${CMAKE_DIR}/find )

include_directories (${PROJ_INS_DIR}/include)
link_directories    (${PROJ_INS_DIR}/lib)
link_directories    (${PROJ_INS_DIR}/lib64)

message("== PROJ_DIR:     ${PROJ_DIR}")
message("== CMAKE_DIR:    ${CMAKE_DIR}")
message("== PROJ_INS_DIR: ${PROJ_INS_DIR}")
message("== PROJ_SUB_DIR: ${PROJ_SUB_DIR}")
message("== CMAKE_BINARY_DIR: ${PROJ_SUB_DIR}")
#message("== PROJ_ST_FILE: ${PROJ_ST_FILE}")
#message("== PROJ_IEC2C:   ${PROJ_IEC2C}")
#message("== PROJ_IEC_DIR: ${PROJ_IEC_DIR}")
#message("== PROJ_ST_FILE: ${PROJ_ST_FILE}\n")

#-------------------------------------------------------------------------------
# 1) Компиляция ST- файла в *.c *.h
#-------------------------------------------------------------------------------
add_custom_command(
        COMMENT "(1) - Compiling the ST file into 'C' ..."
        OUTPUT
        ${PROJ_IEC_DIR}/iec-sources
        ${PROJ_IEC_DIR}/LOCATED_VARIABLES.h

        DEPENDS ${PROJ_ST_FILE}

        WORKING_DIRECTORY ${PROJ_CMP_DIR}
        COMMAND rm -rf *.c
        COMMAND "${PROJ_IEC2C}" -f -l -p -r -R -a "${PROJ_ST_FILE}"
        COMMAND mv -f VARIABLES.csv *.h *.c ${PROJ_IEC_DIR}
        COMMAND cd ${PROJ_IEC_DIR} && ls *.c > ${PROJ_IEC_DIR}/iec-sources
)

#-------------------------------------------------------------------------------
# 2) Склеивание PVs перед компиляцией и сборкой
#-------------------------------------------------------------------------------
add_custom_command(
        COMMENT "(2) - Glue generator: LOCATED_VARIABLES.h -> glueVars.cpp"
        OUTPUT  ${PROJ_IEC_DIR}/glueVars.cpp
        DEPENDS ${PROJ_IEC_DIR}/LOCATED_VARIABLES.h

        WORKING_DIRECTORY ${PROJ_IEC_DIR}

        COMMAND
        ${PROJ_SUB_DIR}/glue_generator/bin/glue_generator > ${PROJ_IEC_DIR}/glue_generator.out
)

#-------------------------------------------------------------------------------
# 3) Компиляция C- файлов, полученных компиляцией iec2c
#-------------------------------------------------------------------------------
add_custom_command(
        COMMENT "(3) - Compiling 'C' to obj-files ..."
        OUTPUT  ${PROJ_IEC_DIR}/obj-sources
        DEPENDS
        ${PROJ_IEC_DIR}/iec-sources
        ${PROJ_IEC_DIR}/glueVars.cpp

        WORKING_DIRECTORY ${PROJ_IEC_DIR}
        COMMAND ${CMAKE_COMMAND}
        -D PROJ_IEC_DIR=${PROJ_IEC_DIR}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -D PROJ_LIB_DIR=${PROJ_LIB_DIR}
        -P ${CMAKE_DIR}/build_iec.cmake

        COMMAND ls ${PROJ_IEC_DIR}/*.o > ${PROJ_IEC_DIR}/obj-sources
)

#-------------------------------------------------------------------------------
add_custom_target( build_iec ALL DEPENDS ${PROJ_IEC_DIR}/obj-sources )

#-------------------------------------------------------------------------------
# Используемые стандартные библиотеки
#-------------------------------------------------------------------------------
include(${CMAKE_DIR}/find_tools.cmake)
#find_package(modbus     REQUIRED)
#find_package(can_master REQUIRED)

#-------------------------------------------------------------------------------
# Подключаемые модули
#-------------------------------------------------------------------------------
# Включаем необходимые вспомогательные модули
include(FetchContent)
include(ExternalProject)  # <- Критически важная строка

## (-1-) Сборка OpenSSL
set(OPENSSL_ROOT_DIR ${PROJ_SUB_DIR}/openssl)
set(OPENSSL_INSTALL_DIR ${PROJ_INS_DIR})
message(STATUS "OpenSSL root directory: ${OPENSSL_ROOT_DIR}")
message(STATUS "OpenSSL will be installed to: ${OPENSSL_INSTALL_DIR}")
file(MAKE_DIRECTORY "${OPENSSL_INSTALL_DIR}")

# Проверяем наличие исходников
if(NOT EXISTS "${OPENSSL_ROOT_DIR}/Configure")
    message(FATAL_ERROR "OpenSSL sources not found in ${OPENSSL_ROOT_DIR}")
endif()

ExternalProject_Add(
        openssl_external
        SOURCE_DIR ${OPENSSL_ROOT_DIR}
        PREFIX "${CMAKE_BINARY_DIR}/openssl_build"
        CONFIGURE_COMMAND ${OPENSSL_ROOT_DIR}/config
        --prefix=/usr/local
        --openssldir=/usr/local/ssl
        shared
        linux-x86_64
        no-asm
        BUILD_COMMAND make depend && make -j${CMAKE_BUILD_PARALLEL_LEVEL}
        INSTALL_COMMAND
        make install_sw DESTDIR=${CMAKE_BINARY_DIR}/temp_install &&
        cp -r ${CMAKE_BINARY_DIR}/temp_install/usr/local/. ${OPENSSL_INSTALL_DIR}/ &&
        #rsync -a ${CMAKE_BINARY_DIR}/temp_install/usr/local/ ${OPENSSL_INSTALL_DIR}/ &&
        rm -rf ${CMAKE_BINARY_DIR}/temp_install
        BUILD_IN_SOURCE TRUE
)

# Импортируем OpenSSL после сборки
find_package(OpenSSL REQUIRED PATHS "${OPENSSL_INSTALL_DIR}" NO_DEFAULT_PATH)

## Вручную задаем пути к OpenSSL
#add_library(OpenSSL::SSL SHARED IMPORTED)
#add_library(OpenSSL::Crypto SHARED IMPORTED)
#set_target_properties(OpenSSL::SSL PROPERTIES
#        IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/lib64/libssl.so"  # .so для Linux, .dll для Windows
#        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include/openssl"
#)
#set_target_properties(OpenSSL::Crypto PROPERTIES
#        IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/lib64/libcrypto.so"
#        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include/openssl"
#)

######################
## (-2-) Сборка ZeroMQ
set(ZMQ_ROOT_DIR ${PROJ_SUB_DIR}/libzmq)
set(ZMQ_INSTALL_DIR ${PROJ_INS_DIR})

# Проверка исходников
if(NOT EXISTS "${ZMQ_ROOT_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "libzmq sources not found in ${ZMQ_ROOT_DIR}")
endif()

# Настройка параметров
set(ZMQ_BUILD_TESTS OFF       CACHE BOOL    "Disable ZMQ tests")
set(WITH_TLS        ON        CACHE BOOL    "Enable TLS support")
set(ZMQ_TLS_ENGINE  "openssl" CACHE STRING  "Use OpenSSL for TLS")
set(BUILD_SHARED    ON        CACHE BOOL    "Build shared library")
set(BUILD_STATIC    OFF       CACHE BOOL    "Disable static library")
set(ENABLE_DRAFTS   OFF       CACHE BOOL    "Disable draft APIs")
set(WITH_PERF_TOOL  OFF       CACHE BOOL    "Disable perf tool")
set(WITH_LIBSODIUM  OFF       CACHE BOOL    "Disable libsodium")

# Указываем путь установки
set(CMAKE_INSTALL_PREFIX ${ZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем libzmq как подпроект
add_subdirectory(${PROJ_SUB_DIR}/libzmq)

## Корректная команда установки
add_custom_target(install_libzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/libzmq
        --prefix ${ZMQ_INSTALL_DIR}
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS libzmq
        COMMENT "Installing libzmq to ${ZMQ_INSTALL_DIR}"
        VERBATIM
)
## -- Альтернативный вариант через make
#add_custom_target(install_libzmq
#        COMMAND ${CMAKE_MAKE_PROGRAM} install DESTDIR=
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/utils/libzmq
#        DEPENDS libzmq
#        COMMENT "Installing libzmq using make"
#)

######################
### (3) Настройка и установка cppzmq
set(CPPZMQ_ROOT_DIR ${PROJ_SUB_DIR}/cppzmq)
set(CPPZMQ_INSTALL_DIR ${PROJ_INS_DIR})

set(CPPZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_EXAMPLES OFF)

# Указываем путь установки
set(CMAKE_INSTALL_PREFIX ${CPPZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем cppzmq как подпроект
add_subdirectory(${PROJ_SUB_DIR}/cppzmq)

## Корректная команда установки
add_custom_target(install_cppzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/cppzmq
        --prefix ${CPPZMQ_INSTALL_DIR}
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS libzmq
        COMMENT "Installing libzmq to ${CPPZMQ_INSTALL_DIR}"
        VERBATIM
)

######################
### (4) ...
add_subdirectory(${PROJ_SUB_DIR}/Gateway)   # --- gateway
add_subdirectory(${PROJ_SUB_DIR}/libmodbus) # --- modbus
add_subdirectory(${PROJ_SUB_DIR}/CANopen)   # --- CANopen
add_subdirectory(${PROJ_SUB_DIR}/json)      # --- JSON

#-------------------------------------------------------------------------------
# 4) Главный исполняемый модуль ${proj} = 'procont-ex'
#-------------------------------------------------------------------------------
include(${CMAKE_DIR}/build_tools.cmake)

build_target( ${proj} EXE
    OPTS -g -O0 -w -fPIC
    INCS
        ${PROJ_LIB_DIR}
        ${PROJ_SRC_DIR}
        ${PROJ_IEC_DIR}

    SRCS
        ${PROJ_IEC_DIR}/glueVars.cpp
        :MASK ${PROJ_SRC_DIR}/*.cpp
        :MASK ${PROJ_IEC_DIR}/*.o
    LNKS
        #libzmq
        #cppzmq
        pro-gateway
        modbus
        can_master
        #nlohmann_json::nlohmann_json
)

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE -D_GNU_SOURCE -Wall -Wextra)
endif()

#-------------------------------------------------------------------------------
### Dependencies ###
#-------------------------------------------------------------------------------
add_dependencies(${proj} build_iec)
add_dependencies(${proj} install_libzmq)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

#------------------------------------------------------------------------------