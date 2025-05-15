cmake_minimum_required(VERSION 3.20)
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

#message("== PROJ_DIR:     ${PROJ_DIR}")
#message("== CMAKE_DIR:    ${CMAKE_DIR}")
#message("== PROJ_INS_DIR: ${PROJ_INS_DIR}")
#message("== PROJ_SUB_DIR: ${PROJ_SUB_DIR}")
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
#include(${CMAKE_DIR}/find_tools.cmake)
#find_package(modbus     REQUIRED)
#find_package(can_master REQUIRED)

#-------------------------------------------------------------------------------
# Подключаемые модули
#-------------------------------------------------------------------------------
# Включаем необходимые модули
include(FetchContent)
include(ExternalProject)  # <- Критически важная строка

## 1. Настройка путей для ZMQ и OpenSSL
#set(ZMQ_SOURCE_DIR      ${PROJ_SUB_DIR}/libzmq)
#set(OPENSSL_SOURCE_DIR  ${PROJ_SUB_DIR}/openssl)  # Путь к исходникам
#
#set(ZMQ_INSTALL_DIR     ${PROJ_INS_DIR}/zmq)
#set(OPENSSL_INSTALL_DIR ${PROJ_INS_DIR}/openssl) # Каталог установки
#
## 2. Добавление OpenSSL как подпроекта
#ExternalProject_Add(
#        openssl
#        SOURCE_DIR ${OPENSSL_SOURCE_DIR}
#        CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/config
#        --prefix=${OPENSSL_INSTALL_DIR}
#        --openssldir=${OPENSSL_INSTALL_DIR}/ssl
#        no-shared
#        no-zlib
#        BUILD_COMMAND make -j${CMAKE_BUILD_PARALLEL_LEVEL}
#        INSTALL_COMMAND make install
#        BUILD_IN_SOURCE TRUE
#        INSTALL_DIR ${OPENSSL_INSTALL_DIR}
#)
#
## 3. Настройка путей для основного проекта
#set(OPENSSL_ROOT_DIR ${PROJ_SUB_DIR}/openssl)
#set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
##set(OPENSSL_INCLUDE_DIR ${OPENSSL_INSTALL_DIR}/include)
#set(OPENSSL_LIBRARIES
#        ${OPENSSL_INSTALL_DIR}/lib/libssl.so
#        ${OPENSSL_INSTALL_DIR}/lib/libcrypto.so
#)
#
## 4. Создание импортируемых целей
#add_library(OpenSSL::SSL STATIC IMPORTED)
#set_target_properties(OpenSSL::SSL PROPERTIES
#        IMPORTED_LOCATION ${OPENSSL_INSTALL_DIR}/lib/libssl.so
#        INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR}
#)
#
#add_library(OpenSSL::Crypto STATIC IMPORTED)
#set_target_properties(OpenSSL::Crypto PROPERTIES
#        IMPORTED_LOCATION ${OPENSSL_INSTALL_DIR}/lib/libcrypto.so
#        INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR}
#)
#
## 5. Настройки libzmq
#set(WITH_TLS ON CACHE BOOL "Enable TLS")
#set(WITH_LIBSODIUM OFF CACHE BOOL "Disable libsodium")
#set(ZMQ_TLS_ENGINE "openssl" CACHE STRING "Use OpenSSL")
#
## 6. Сборка ZeroMQ
#ExternalProject_Add(
#        libzmq
#        SOURCE_DIR ${ZMQ_SOURCE_DIR}
#        DEPENDS openssl
#        CMAKE_ARGS
#        -DCMAKE_INSTALL_PREFIX=${ZMQ_INSTALL_DIR}
#        -DWITH_TLS=ON
#        -DZMQ_TLS_ENGINE=openssl
#        -DOPENSSL_ROOT_DIR=${ZMQ_INSTALL_DIR}
#)
#
## 7. Создаем интерфейсные цели для удобного использования
#target_include_directories(openssl_interface INTERFACE
#        ${OPENSSL_INSTALL_DIR}/include
#)
#
#add_library(zmq_interface INTERFACE)
#target_include_directories(zmq_interface INTERFACE
#        ${ZMQ_INSTALL_DIR}/include
#)

# Настройка путей
set(OPENSSL_ROOT_DIR ${PROJ_SUB_DIR}/openssl)
set(ZMQ_ROOT_DIR ${PROJ_SUB_DIR}/libzmq)

# Сборка OpenSSL
ExternalProject_Add(
        openssl
        SOURCE_DIR ${OPENSSL_ROOT_DIR}
        CONFIGURE_COMMAND ${OPENSSL_ROOT_DIR}/config --prefix=${PROJ_INS_DIR}/openssl
        BUILD_COMMAND make -j${CMAKE_BUILD_PARALLEL_LEVEL}
        INSTALL_COMMAND make install
)

# Сборка ZeroMQ
ExternalProject_Add(
        libzmq
        SOURCE_DIR ${ZMQ_ROOT_DIR}
        DEPENDS openssl
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${PROJ_INS_DIR}/zmq
        -DWITH_TLS=ON
        -DZMQ_TLS_ENGINE=openssl
        -DOPENSSL_ROOT_DIR=${PROJ_INS_DIR}/openssl
)

# Создаем интерфейсные цели для удобного использования
add_library(openssl_interface INTERFACE)
target_include_directories(openssl_interface INTERFACE
        ${PROJ_INS_DIR}/openssl/include
)

add_library(zmq_interface INTERFACE)
target_include_directories(zmq_interface INTERFACE
        ${PROJ_INS_DIR}/zmq/include
)

#add_subdirectory(${PROJ_SUB_DIR}/libzmq)    # --- libzmq
add_subdirectory(${PROJ_SUB_DIR}/Gateway)    # --- gateway
add_subdirectory(${PROJ_SUB_DIR}/libmodbus)  # --- modbus
add_subdirectory(${PROJ_SUB_DIR}/CANopen)    # --- CANopen tester

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
        ${PROJ_SUB_DIR}/libzmq/include
    SRCS
        ${PROJ_IEC_DIR}/glueVars.cpp
        :MASK ${PROJ_SRC_DIR}/*.cpp
        :MASK ${PROJ_IEC_DIR}/*.o
    LNKS
        #openssl_interface
        #${PROJ_INS_DIR}/openssl/lib/libssl.a
        #${PROJ_INS_DIR}/openssl/lib/libcrypto.a

        #zmq
        zmq_interface
        #${PROJ_INS_DIR}/zmq/lib64/libzmq.so

        pro-gateway
        modbus      #${modbus_LIBRARIES}
        can_master  #${can_master_LIBRARIES}
)

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE -D_GNU_SOURCE -Wall -Wextra)
endif()

#-------------------------------------------------------------------------------
### Dependencies ###
#-------------------------------------------------------------------------------
add_dependencies(${proj} build_iec)
add_dependencies(${proj} libzmq)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

#------------------------------------------------------------------------------