cmake_minimum_required(VERSION 3.19)
project( PROCONT-EX
         VERSION 1.0.1
         DESCRIPTION "Procont execution environment"
         LANGUAGES C CXX
)
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          11   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( PROJ ${PROJECT_NAME} )     # PROJ = project name in orig case
string( TOLOWER ${PROJ} proj )  # proj = project name in lowercase

# PROJ Project specific PVs
set( PROJ_DIR                       ${CMAKE_CURRENT_SOURCE_DIR}     ) # PROJ project directory
set( PROJ_SRC_DIR                   ${PROJ_DIR}                     ) # PROJ sources directory
set( PROJ_INC_DIR                   ${PROJ_DIR}/lib                 ) # PROJ includes directory
set( PROJ_MOD_DIR                   ${PROJ_DIR}/moduls              ) # PROJ modules directory
set( PROJ_DAT_DIR                   ${PROJ_DIR}/data                ) # PROJ data files directory
set( PROJ_UP0_DIR                   ${PROJ_DIR}                     ) # PROJ 1-level up directory
set( PROJ_UP1_DIR                   ${PROJ_DIR}/..                  ) # PROJ 1-level up directory
set( PROJ_UP2_DIR                   ${PROJ_DIR}/../..               ) # PROJ 2-level up directory

set( PROJ_IEC2C                     ${PROJ_DIR}/matiec/iec2c        ) # IEC to C compiler
set( PROJ_ST_FILE                   ${PROJ_DIR}/st_files/wmt.st     ) # ST source file

#-------------------------------------------------------------------------------
# Используемые стандартные библиотеки
#-------------------------------------------------------------------------------
find_package(AsioPAL REQUIRED)
find_package(AsioDNP3 REQUIRED)
find_package(OpenPAL REQUIRED)
find_package(OpenDNP3 REQUIRED)
find_package(modbus REQUIRED)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive") # errors to warnings conversion

#-------------------------------------------------------------------------------
# 1) Компиляция C-шных файлов, полученные компиляцией iec2c
#-------------------------------------------------------------------------------
# Компиляция *.st файла в *.c *.h
add_custom_command(
    OUTPUT  ${PROJ_SRC_DIR}/Config0.c ${PROJ_SRC_DIR}/Res0.c
    DEPENDS ${PROJ_ST_FILE}
    WORKING_DIRECTORY ${PROJ_DIR}/matiec
    COMMENT "Compiling the ST file into 'C' ..."
    COMMAND "${PROJ_IEC2C}" -f -l -p -r -R -a "${PROJ_ST_FILE}"
    COMMAND mv -f VARIABLES.csv *.h *.c ${PROJ_SRC_DIR}  #./core/
)

# Эти цели "устаревают" ВСЕГДА, поэтому их сборка всегда занимает время
#add_custom_target(Config0 g++ -o ${PROJ_SRC_DIR}/Config0.o -I ${PROJ_INC_DIR} -c ${PROJ_SRC_DIR}/Config0.c -w)
#add_custom_target(Res0 g++ -o ${PROJ_SRC_DIR}/Res0.o -I ${PROJ_INC_DIR} -c ${PROJ_SRC_DIR}/Res0.c -w)

# Применение add_custom_command позволяет внедрить зависимости (здесь - на уровне файлов)
add_custom_command(
    OUTPUT
        ${PROJ_SRC_DIR}/Config0.o
        ${PROJ_SRC_DIR}/Res0.o
    DEPENDS
        ${PROJ_SRC_DIR}/Config0.c
        ${PROJ_SRC_DIR}/Res0.c
    COMMAND g++ -o ${PROJ_SRC_DIR}/Config0.o -I ${PROJ_INC_DIR} -c ${PROJ_SRC_DIR}/Config0.c -w
    COMMAND g++ -o ${PROJ_SRC_DIR}/Res0.o    -I ${PROJ_INC_DIR} -c ${PROJ_SRC_DIR}/Res0.c    -w
)

#-------------------------------------------------------------------------------
# 2) Главный исполняемый модуль ${proj} = 'procont-ex'
#-------------------------------------------------------------------------------
add_module(${proj}
    INSTALL EXE
    OPTS -g -O0 -w -fPIC #-Wno-varargs -Wno-parentheses -Wno-parentheses-equality
    INCS ${PROJ_SRC_DIR}
    INCS ${PROJ_INC_DIR}
    INCS "/usr/local/include/modbus"
    #DEFS HAVE_CONFIG_H
    SRCS
        :MASK ${PROJ_SRC_DIR}/*.cpp
        # Распаковано ниже для разрешения зависимостей:
        ${PROJ_SRC_DIR}/Config0.o
        ${PROJ_SRC_DIR}/Res0.o
    LNKS
        pthread modbus
        ${AsioPAL_LIBRARIES}  #asiopal
        ${AsioDNP3_LIBRARIES} #asiodnp3
        ${OpenPAL_LIBRARIES}  #openpal
        ${OpenDNP3_LIBRARIES} #opendnp3
)

#add_dependencies(${proj} Config0 Res0)

#-------------------------------------------------------------------------------
# 3) Склеивание PVs перед компиляцией и сборкой ${proj} = 'procont-ex' (PRE_BUILD)
#-------------------------------------------------------------------------------
add_custom_command(TARGET ${proj} WORKING_DIRECTORY ${PROJ_SRC_DIR}
        COMMAND PRE_BUILD ./glue_generator > ${PROJ_SRC_DIR}/glue_generator.out
        COMMENT "Glue generator for PVs: glue_generator > glue_generator.out"
)

#-------------------------------------------------------------------------------