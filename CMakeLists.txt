cmake_minimum_required(VERSION 3.20)
project( PROCONT-EX
         VERSION 1.0.1
         DESCRIPTION "Procont execution environment"
         LANGUAGES CXX
)
MESSAGE("------------------- PROJECT: ${PROJECT_NAME} BEGIN")

set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          17   )
set( CMAKE_CXX_STANDARD_REQUIRED True )
string( TOLOWER ${PROJECT_NAME}  proj )      # proj = project name in lowercase

set( PROJ_DIR       ${CMAKE_CURRENT_SOURCE_DIR}     ) # PROJ project directory
set( CMAKE_DIR      ${PROJ_DIR}/cmake               ) # PROJ cmake files directory

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
set( PROJ_MOD_DIR   ${PROJ_DIR}/utils     ) # PROJ iec2c directory
set( PROJ_IEC_DIR   ${PROJ_DIR}/iec       ) # PROJ iec2c directory
set( PROJ_LIB_DIR   ${PROJ_DIR}/lib       ) # PROJ includes directory
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
#message("== PROJ_MOD_DIR: ${PROJ_MOD_DIR}")
#message("== PROJ_ST_FILE: ${PROJ_ST_FILE}")
#message("== PROJ_IEC2C:   ${PROJ_IEC2C}")
#message("== PROJ_IEC_DIR: ${PROJ_IEC_DIR}")
#message("== PROJ_ST_FILE: ${PROJ_ST_FILE}\n")

################################
# Запуск сборки конвейера cmake для build-iec
#execute_process(
#        WORKING_DIRECTORY "${PROJ_IEC_DIR}"
#        COMMAND ${CMAKE_COMMAND}
#        -G ${CMAKE_GENERATOR}
#        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
#        -DPROJ_ST_FILE=${PROJ_ST_FILE}
#        ${PROJ_IEC_DIR}
#)

# Запуск cmake для сборки target build-iec
#execute_process(
#    WORKING_DIRECTORY "${PROJ_IEC_DIR}"
#    COMMAND ${CMAKE_COMMAND}
#        --build . --target build-iec
#)
################################

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
        COMMAND ${PROJ_SRC_DIR}/glue_generator > ${PROJ_IEC_DIR}/glue_generator.out
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
        -P ${CMAKE_DIR}/build-iec.cmake

        COMMAND ls ${PROJ_IEC_DIR}/*.o > ${PROJ_IEC_DIR}/obj-sources
)

#-------------------------------------------------------------------------------
add_custom_target( build-iec ALL DEPENDS ${PROJ_IEC_DIR}/obj-sources )

##-------------------------------------------------------------------------------
## 4) Главный исполняемый модуль ${proj} = 'procont-ex'
##-------------------------------------------------------------------------------
include(${CMAKE_DIR}/build-tools.cmake)

#-------------------------------------------------------------------------------
# Используемые стандартные библиотеки
#-------------------------------------------------------------------------------
#find_package(modbus   REQUIRED)
#find_package(AsioDNP3 REQUIRED)
#find_package(AsioPAL  REQUIRED)
#find_package(OpenPAL  REQUIRED)
#find_package(OpenDNP3 REQUIRED)

#-------------------------------------------------------------------------------
# Подключаемые модули
#-------------------------------------------------------------------------------
add_subdirectory(${PROJ_MOD_DIR}/libmodbus)             # --- modbus
add_subdirectory(${PROJ_MOD_DIR}/CANopen/MasterQtFree)  # --- can_master

#add_subdirectory(${PROJ_MOD_DIR}/dnp3_src)             # --- dnp3

#-------------------------------------------------------------------------------
# Главный исполняемый модуль ${proj}
#-------------------------------------------------------------------------------
build_target( ${proj} EXE #OPTS -g -O0 -w -fPIC
    INCS
        ${PROJ_LIB_DIR}
        ${PROJ_SRC_DIR}
        ${PROJ_IEC_DIR}

        #${modbus_INCLUDE_DIRS}

    SRCS
        ${PROJ_IEC_DIR}/glueVars.cpp
        :MASK ${PROJ_SRC_DIR}/*.cpp
        :MASK ${PROJ_IEC_DIR}/*.o

    LNKS
        modbus      #${modbus_LIBRARIES}
        can_master  #${can_master_LIBRARIES}

        #${AsioPAL_LIBRARIES}
        #${AsioDNP3_LIBRARIES}
        #${OpenPAL_LIBRARIES}
        #${OpenDNP3_LIBRARIES}
)

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE -D_GNU_SOURCE -Wall -Wextra)
endif()

#-------------------------------------------------------------------------------
### Dependencies ###
#-------------------------------------------------------------------------------
add_dependencies(${proj} build-iec)
#add_dependencies(${proj} modbus)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

#------------------------------------------------------------------------------