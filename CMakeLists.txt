cmake_minimum_required(VERSION 3.25)
project( PROCONT-EX
         VERSION 1.0.1
         DESCRIPTION "Procont execution environment"
         LANGUAGES CXX
)

# Опция для выбора способа получения OpenSSL
option(BUILD_OPENSSL_FROM_SOURCE "Build OpenSSL from source instead of using system package" OFF)

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
set( PROJ_INS_DIR   ${PROJ_DIR}/.install  ) # local install directory
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

file(MAKE_DIRECTORY ${PROJ_IEC_DIR})

##-------------------------------------------------------------------------------
## 0) glue_generator
##-------------------------------------------------------------------------------
#add_subdirectory(${PROJ_SUB_DIR}/glue_generator)
## Получаем путь к бинарнику (автоматически учитывает конфигурацию)
#set(GLUE_GENERATOR_EXE $<TARGET_FILE:glue_generator>)
#message(STATUS "Glue generator path: ${GLUE_GENERATOR_EXE}")

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
# 2) Склеивание PVs перед компиляцией и сборкой (нужен glue_generator)
#-------------------------------------------------------------------------------
add_custom_command(
        COMMENT "(2) - Glue generator: LOCATED_VARIABLES.h -> glueVars.cpp"
        OUTPUT  ${PROJ_IEC_DIR}/glueVars.cpp
        DEPENDS glue_generator ${PROJ_IEC_DIR}/LOCATED_VARIABLES.h

        WORKING_DIRECTORY ${PROJ_IEC_DIR}

        COMMAND
        #${GLUE_GENERATOR_EXE} > ${PROJ_IEC_DIR}/glue_generator.out
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
include(${CMAKE_DIR}/build_tools.cmake)

#-------------------------------------------------------------------------------
# Подключаемые модули
#-------------------------------------------------------------------------------
# Включаем необходимые вспомогательные модули
include(FetchContent)
include(ExternalProject)  # <- Критически важная строка

# -----------------------------------------------------------------------------
# (-1-) Сборка OpenSSL
# -----------------------------------------------------------------------------
# 1. Сначала определяем параметры сборки
set(OPENSSL_ROOT_DIR ${PROJ_SUB_DIR}/openssl)   # openssl source dir
set(OPENSSL_INSTALL_DIR ${PROJ_INS_DIR})        # openssl install dir
set(MAKE_DIRECTORY "${OPENSSL_INSTALL_DIR}")

if(BUILD_OPENSSL_FROM_SOURCE)
    # 2. Проверяем наличие исходников
    if(NOT EXISTS "${OPENSSL_ROOT_DIR}/Configure")
        message(FATAL_ERROR "OpenSSL sources not found in ${OPENSSL_ROOT_DIR}")
    endif()

    # 3. Сборка OpenSSL
    # Определение архитектуры
    set(BUILD_TARGET "linux-generic64")  # linux-aarch64 linux-x86_64
    set(CROSS_PREFIX "")

    # Создаем список команд для CONFIGURE_COMMAND
    set(OPENSSL_CONFIGURE_COMMAND ${OPENSSL_ROOT_DIR}/Configure
            --prefix=${OPENSSL_INSTALL_DIR}
            --openssldir=${OPENSSL_INSTALL_DIR}/ssl
            --cross-compile-prefix=${CROSS_PREFIX}
            ${BUILD_TARGET}
            -fPIC               # ← Для статической линковки в shared-библиотеки
            #-static             # ← Полностью статическая сборка
            no-shared           # ← Статическая сборка
            no-module           # ← Отключаем динамические модули
            #enable-fips         # ← Если нужен FIPS
            #enable-legacy       # ← Включаем legacy-провайдер
            no-legacy           # ← Полностью отключаем legacy-провайдер
            no-autoload-config  # ← Отключаем авто-подгрузку конфигурации
    )

    ExternalProject_Add(
            openssl_external
            SOURCE_DIR ${OPENSSL_ROOT_DIR}
            PREFIX "${CMAKE_BINARY_DIR}/openssl_build"
            CONFIGURE_COMMAND ${OPENSSL_CONFIGURE_COMMAND}
            BUILD_COMMAND make clean && make depend && make -j${CMAKE_BUILD_PARALLEL_LEVEL}
            INSTALL_COMMAND make install_sw
            BUILD_IN_SOURCE TRUE # Сборка в исходниках

            # Условное добавление переменных окружения
            #$<$<STREQUAL:${BUILD_TARGET},linux-aarch64>:
            ENV
            PATH "/usr/xcc/aarch64-unknown-linux-gnu/bin:$ENV{PATH}"
            CC aarch64-unknown-linux-gnu-gcc
            AR aarch64-unknown-linux-gnu-ar
            RANLIB aarch64-unknown-linux-gnu-ranlib
            #>

            BUILD_BYPRODUCTS
                "${OPENSSL_INSTALL_DIR}/lib64/libssl.so"
                "${OPENSSL_INSTALL_DIR}/lib64/libcrypto.so"
    )

    # 4. Создаем промежуточные импортированные цели
    add_library(OpenSSL::Crypto SHARED IMPORTED GLOBAL)
    add_library(OpenSSL::SSL    SHARED IMPORTED GLOBAL)

    # 5. Устанавливаем зависимости
    add_dependencies(OpenSSL::Crypto openssl_external)
    add_dependencies(OpenSSL::SSL    openssl_external)

    #ExternalProject_Get_Property(openssl_external BINARY_DIR)
    #message(STATUS "OpenSSL is building in: ${BINARY_DIR}")

    # 6. Откладываем установку свойств до момента сборки
    # Для Crypto
    set_target_properties(OpenSSL::Crypto PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/lib64/libcrypto.so"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include"
    )

    # Для SSL
    set_target_properties(OpenSSL::SSL PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/lib64/libssl.so"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include"
            INTERFACE_LINK_LIBRARIES OpenSSL::Crypto
    )

    # 7. Создаем псевдо-цель для удобства
    add_custom_target(openssl_all DEPENDS OpenSSL::SSL OpenSSL::Crypto)
else()
#    # Используем системный OpenSSL
#    find_package(OpenSSL REQUIRED)
#    if(NOT OpenSSL_FOUND)
#        message(FATAL_ERROR "System OpenSSL not found, consider enabling BUILD_OPENSSL_FROM_SOURCE")
#    endif()
#    message(STATUS "Using system OpenSSL: ${OPENSSL_VERSION}")

    add_custom_target(openssl_all)  # Пустая цель для совместимости

endif()

# 8. Создаем интерфейсную библиотеку для OpenSSL (если нужно)
#add_library(openssl_interface INTERFACE)
#target_link_libraries(openssl_interface INTERFACE OpenSSL::SSL OpenSSL::Crypto)

# 9. Включаем директории OpenSSL
include_directories(${OPENSSL_INCLUDE_DIR})

# -----------------------------------------------------------------------------
## (-2-) Сборка ZeroMQ
# -----------------------------------------------------------------------------
set(ZMQ_ROOT_DIR ${PROJ_SUB_DIR}/libzmq)
set(ZMQ_INSTALL_DIR ${PROJ_INS_DIR})

# Проверка исходников
if(NOT EXISTS "${ZMQ_ROOT_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "libzmq sources not found in ${ZMQ_ROOT_DIR}")
endif()

# Настройка параметров
set(ZMQ_BUILD_OPTIONS
        -DZMQ_BUILD_TESTS=OFF                       # Disable ZMQ tests
        -WITH_TLS=${BUILD_OPENSSL_FROM_SOURCE}      # TLS только с OpenSSL
        -DZMQ_TLS_ENGINE=openssl                    # Use OpenSSL for TLS
        -DBUILD_SHARED=ON                           # Build shared library
        -DBUILD_STATIC=OFF                          # Disable static library
        -DENABLE_DRAFTS=OFF                         # Disable draft APIs
        -DWITH_PERF_TOOL=OFF                        # Disable perf tool
        -DWITH_LIBSODIUM=OFF                        # Disable libsodium
        -DCMAKE_INSTALL_PREFIX=${ZMQ_INSTALL_DIR}
)

if(BUILD_OPENSSL_FROM_SOURCE)
    list(APPEND ZMQ_BUILD_OPTIONS
            -DOPENSSL_ROOT_DIR=${OPENSSL_INSTALL_DIR}
            -DOPENSSL_USE_STATIC_LIBS=ON
    )
endif()

# Указываем путь установки
set(CMAKE_INSTALL_PREFIX ${ZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем libzmq как подпроект с явными зависимостями
add_subdirectory(${PROJ_SUB_DIR}/libzmq) #EXCLUDE_FROM_ALL

# Устанавливаем зависимости
if(TARGET libzmq AND TARGET openssl_all)
    add_dependencies(libzmq openssl_all)
endif()

## Корректная команда установки
add_custom_target(install_libzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/libzmq
        --prefix ${ZMQ_INSTALL_DIR}
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS libzmq #openssl_all
        COMMENT "Installing libzmq to ${ZMQ_INSTALL_DIR}"
        VERBATIM
)

# Добавляем путь в цели
include_directories(${ZMQ_ROOT_DIR}/include)

# -----------------------------------------------------------------------------
### (3) Настройка и установка cppzmq
# -----------------------------------------------------------------------------
set(CPPZMQ_ROOT_DIR ${PROJ_SUB_DIR}/cppzmq)
set(CPPZMQ_INSTALL_DIR ${PROJ_INS_DIR})

set(CPPZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_EXAMPLES OFF)

# Указываем путь установки
set(CMAKE_INSTALL_PREFIX ${CPPZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем cppzmq как подпроект
add_subdirectory(${PROJ_SUB_DIR}/cppzmq)

# Устанавливаем зависимости
if(TARGET cppzmq AND TARGET libzmq)
    add_dependencies(cppzmq libzmq)
endif()

## Корректная команда установки
add_custom_target(install_cppzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/cppzmq
        --prefix ${CPPZMQ_INSTALL_DIR}
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS cppzmq
        COMMENT "Installing cppzmq to ${CPPZMQ_INSTALL_DIR}"
        VERBATIM
)

# Добавляем путь в цели
include_directories(${CPPZMQ_ROOT_DIR})

######################
### (4) ...
add_subdirectory(${PROJ_SUB_DIR}/json)      # --- JSON
add_subdirectory(${PROJ_SUB_DIR}/Gateway)   # --- gateway
add_subdirectory(${PROJ_SUB_DIR}/libmodbus) # --- modbus
add_subdirectory(${PROJ_SUB_DIR}/CANopen)   # --- CANopen
add_subdirectory(${PROJ_SUB_DIR}/EtherCAT)  # --- EtherCAT


# Копирование конфигов в директорию сборки
configure_file( ${PROJ_DIR}/drivers_config.json ${CMAKE_CURRENT_BINARY_DIR}/drivers_config.json COPYONLY )
configure_file( ${PROJ_DIR}/zmq.properties ${CMAKE_CURRENT_BINARY_DIR}/zmq.properties COPYONLY )

#-------------------------------------------------------------------------------
# 4) Главный исполняемый модуль ${proj} = 'procont-ex'
#-------------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE  -D_GNU_SOURCE -Wall -Wextra)
endif()
#set_target_properties(${proj} PROPERTIES CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
#target_compile_definitions(${proj} PRIVATE _GLIBCXX_DEBUG=1)

build_target( ${proj} EXE
    OPTS -g -O0 -w -fPIC
    PRPS CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    INCS
        ${PROJ_LIB_DIR}
        ${PROJ_IEC_DIR}
        ${PROJ_SRC_DIR}

    SRCS
        ${PROJ_IEC_DIR}/glueVars.cpp
        :MASK ${PROJ_SRC_DIR}/*.cpp
        :MASK ${PROJ_IEC_DIR}/*.o

    LNKS
        nlohmann_json
        libzmq
        cppzmq
        pro-gateway
        modbus
        can_master
        nlohmann_json::nlohmann_json
)

#-------------------------------------------------------------------------------
### Dependencies ###
#-------------------------------------------------------------------------------
add_dependencies(${proj} build_iec)

## Включение AddressSanitizer для всех конфигураций
#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#    message(STATUS "ADD: -fsanitize=address -O0 -g")
#    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
#    add_link_options(-fsanitize=address)
#endif()

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

# Для установки в систему drivers_config.json
install(FILES ${PROJ_DIR}/drivers_config.json DESTINATION ${PROJ_INS_DIR})

# Для установки в систему zmq.properties
install(FILES ${PROJ_DIR}/zmq.properties DESTINATION ${PROJ_INS_DIR})
#------------------------------------------------------------------------------