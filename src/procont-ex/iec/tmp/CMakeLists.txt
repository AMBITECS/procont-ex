cmake_minimum_required(VERSION 3.20)
project( IEC-COMPILER
         VERSION 1.0.1
         DESCRIPTION "Procont iec st-file compiler"
         LANGUAGES C CXX
)
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          11   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( PROJ ${PROJECT_NAME} )     # PROJ = project name in orig case
string( TOLOWER ${PROJ} proj )  # proj = project name in lowercase

# PROJ Project specific PVs
set( PROJ_DIR       ${CMAKE_CURRENT_SOURCE_DIR}     ) # PROJ project

set( PROJ_IEC_DIR   ${PROJ_DIR}                     ) # PROJ IEC work
set( PROJ_SRC_DIR   ${PROJ_DIR}/..                  ) # PROJ up sources
#set( PROJ_LIB_DIR   ${PROJ_SRC_DIR}/lib            ) # PROJ includes
set( CMAKE_DIR      ${PROJ_SRC_DIR}/cmake           ) # PROJ cmake files
set( PROJ_CMP_DIR   ${PROJ_SRC_DIR}/matiec          ) # PROJ compiler
set( PROJ_IEC2C     ${PROJ_CMP_DIR}/iec2c           ) # IEC to C compiler

#set( PROJ_ST_FILE   ${PROJ_SRC_DIR}/st_files/plc.st ) # ST source file
message("== PROJ_ST_FILE: ${PROJ_ST_FILE}")

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
# 3) Компиляция C-шных файлов, полученные компиляцией iec2c
#-------------------------------------------------------------------------------
add_custom_command(
        COMMENT "(3) - Compiling 'C' to obj-files ..."
        OUTPUT  ${PROJ_IEC_DIR}/obj-sources
        DEPENDS ${PROJ_IEC_DIR}/iec-sources ${PROJ_IEC_DIR}/glueVars.cpp

        WORKING_DIRECTORY ${PROJ_IEC_DIR}
        COMMAND ${CMAKE_COMMAND}
            -D PROJ_IEC_DIR=${PROJ_IEC_DIR}
            -D PROJ_INC_DIR=${PROJ_INC_DIR}
            -P ${CMAKE_DIR}/iec_build.cmake

        COMMAND ls ${PROJ_IEC_DIR}/*.o > ${PROJ_IEC_DIR}/obj-sources
)

#-------------------------------------------------------------------------------
add_custom_target( build-iec ALL DEPENDS ${PROJ_IEC_DIR}/obj-sources )

#-------------------------------------------------------------------------------
