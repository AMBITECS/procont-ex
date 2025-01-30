cmake_minimum_required(VERSION 3.20)
project( PROCONT-EX
         VERSION 1.0.1
         DESCRIPTION "Procont execution environment"
         LANGUAGES C CXX
)
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          11   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( PROJ ${PROJECT_NAME} )         # PROJ = project name in orig case
string( TOLOWER ${PROJ} proj )      # proj = project name in lowercase

# PROJ Project specific PVs
set( PROJ_DIR                       ${CMAKE_CURRENT_SOURCE_DIR}     ) # PROJ project directory
set( CMAKE_DIR                      ${PROJ_DIR}/cmake               ) # PROJ cmake files directory

set( PROJ_SRC_DIR                   ${PROJ_DIR}                     ) # PROJ sources directory
set( PROJ_MOD_DIR                   ${PROJ_DIR}/utils               ) # PROJ iec2c directory
set( PROJ_IEC_DIR                   ${PROJ_DIR}/iec                 ) # PROJ iec2c directory
set( PROJ_LIB_DIR                   ${PROJ_DIR}/lib                 ) # PROJ includes directory
set( PROJ_CMP_DIR                   ${PROJ_DIR}/matiec              ) # IEC to C compiler directory
set( PROJ_IEC2C                     ${PROJ_CMP_DIR}/iec2c           ) # IEC to C compiler

set( CMAKE_MODULE_PATH              ${CMAKE_DIR} ${CMAKE_DIR}/find  )
set( PROJ_ST_FILE                   ${PROJ_DIR}/st_files/plc.st     ) # ST source file

#message("== PROJ_DIR:     ${PROJ_DIR}")
#message("== CMAKE_DIR:    ${CMAKE_DIR}")
#message("== PROJ_ST_FILE: ${PROJ_ST_FILE}")
#message("== PROJ_IEC2C:   ${PROJ_IEC2C}")
#message("== PROJ_IEC_DIR: ${PROJ_IEC_DIR}")
#message("== CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
#message("== CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Libmodbus library (сделан через include, т.к. нет своего CMakeLists.txt)
include(${CMAKE_DIR}/build-modbus.cmake)

# dnp3 library
add_subdirectory(${PROJ_MOD_DIR}/dnp3_src)

################################
# Запуск cmake для сборки target build-iec
execute_process(
        WORKING_DIRECTORY "${PROJ_IEC_DIR}"
        COMMAND ${CMAKE_COMMAND}
        -G "${CMAKE_GENERATOR}"
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
        -DPROJ_ST_FILE=${PROJ_ST_FILE}
        ${PROJ_IEC_DIR}
)

execute_process(
    WORKING_DIRECTORY "${PROJ_IEC_DIR}"
    COMMAND ${CMAKE_COMMAND} --build . --target build-iec
)
################################

##-------------------------------------------------------------------------------
## 4) Главный исполняемый модуль ${proj} = 'procont-ex'
##-------------------------------------------------------------------------------
include(${CMAKE_DIR}/build-tools.cmake)

#-------------------------------------------------------------------------------
# Используемые стандартные библиотеки
#-------------------------------------------------------------------------------
find_package(AsioPAL  REQUIRED)
find_package(AsioDNP3 REQUIRED)
find_package(OpenPAL  REQUIRED)
find_package(OpenDNP3 REQUIRED)
find_package(modbus   REQUIRED)

message(STATUS "dist_include = \"${dist_include}\"")

#-------------------------------------------------------------------------------
# Главный исполняемый модуль ${proj}
#-------------------------------------------------------------------------------
build_target(
    ${proj}
    EXE
    OPTS -g -O0 -w -fPIC
    INCS
        ${dist_include}
        ${PROJ_SRC_DIR}
        ${PROJ_LIB_DIR}
        ${PROJ_IEC_DIR}
        ${modbus_INCLUDE_DIRS}  #"~/.local/include/modbus"

    SRCS
        ${PROJ_IEC_DIR}/glueVars.cpp
        :MASK ${PROJ_SRC_DIR}/*.cpp
        :MASK ${PROJ_IEC_DIR}/*.o

    LNKS
        #pthread
        modbus  #${modbus_LIBRARIES}

        ${AsioPAL_LIBRARIES}
        ${AsioDNP3_LIBRARIES}
        ${OpenPAL_LIBRARIES}
        ${OpenDNP3_LIBRARIES}
)

#add_dependencies(${proj} dnp3)

#-------------------------------------------------------------------------------
#add_custom_command(
#        TARGET ${proj} PRE_BUILD
#        DEPENDS ${PROJ_IEC_DIR}/glueVars.cpp
#        WORKING_DIRECTORY ${PROJ_SRC_DIR}
#        COMMAND ${CMAKE_COMMAND} -E echo "PRE_BUILD: ${proj}"
#)

#-------------------------------------------------------------------------------