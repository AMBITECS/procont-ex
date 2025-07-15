cmake_minimum_required(VERSION 3.25)
project( PROCONT-EX VERSION 1.0.1 DESCRIPTION "Procont execution environment" LANGUAGES CXX )
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Опция для выбора способа получения OpenSSL
option(BUILD_OPENSSL_FROM_SOURCE "Build OpenSSL from source instead of using system package" OFF)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} BEGIN")

string( TOLOWER ${PROJECT_NAME}  proj )      # proj = project name in lowercase
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          17   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

#--------------------------------------------------------------
# Определение платформы и архитектуры
#--------------------------------------------------------------
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(LIB_ARCH "linux-arm64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(LIB_ARCH "linux-x86_64")
elseif(WIN32)
    set(LIB_ARCH "win64")
endif()
message(STATUS "Target platform: ${LIB_ARCH}")

# === SET CMAKE_PREFIX_PATH ===
#if(NOT DEFINED CMAKE_PREFIX_PATH)
#    set(CMAKE_PREFIX_PATH   "/home/master/Qt/6.7.1/gcc_64/")
#    MESSAGE(STATUS "SET CMAKE_PREFIX_PATH to ${CMAKE_PREFIX_PATH}")
#endif()

#--------------------------------------------------------------
# PROJ Project specific PVs
#--------------------------------------------------------------
set( PROJ_DIR     ${CMAKE_CURRENT_SOURCE_DIR} ) # PROJ project
set( CMAKE_DIR    ${PROJ_DIR}/.cmake          ) # PROJ cmake
set( PROJ_INS_DIR ${PROJ_DIR}/.install        ) # PROJ install (local)
set( PROJ_SRC_DIR ${PROJ_DIR}/src             ) # PROJ sources
set( PROJ_INC_DIR ${PROJ_DIR}/include         ) # PROJ includes
set( PROJ_LIB_DIR ${PROJ_DIR}/libs            ) # PROJ libraries
set( PROJ_SUB_DIR ${PROJ_DIR}/utils           ) # PROJ submodule


set( CMAKE_MODULE_PATH ${CMAKE_DIR} ${CMAKE_DIR}/find )
set( CMAKE_INSTALL_PREFIX ${PROJ_INS_DIR} CACHE PATH "Installation directory" FORCE )

include_directories (${PROJ_INS_DIR}/include)

#link_directories(
#        ${PROJ_INS_DIR}/lib
#        ${PROJ_INS_DIR}/lib64
#        ${PROJ_DIR}/libs/factory
#        ${PROJ_DIR}/libs/program
#)

#--------------------------------------------------------------
# Настройка путей к библиотекам
#--------------------------------------------------------------
set(PLC_MAIN_LIB_DIR "${PROJ_DIR}/libs/${LIB_ARCH}/program")
link_directories(
        ${PROJ_INS_DIR}/lib
        ${PROJ_INS_DIR}/lib64
        ${PROJ_DIR}/libs/factory
        ${PLC_MAIN_LIB_DIR}  # Новый платформозависимый путь
)

if(UNIX AND NOT APPLE)
    # Для Linux используем $ORIGIN
    # \$ORIGIN/../lib означает:
    # "ищи библиотеки в папке ../libs относительно расположения исполняемого файла"
    set(CMAKE_INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../lib:\$ORIGIN/../libs/program")
    # Прописывает RPATH в исполняемый файл: readelf -d исполняемый_файл | grep RPATH
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    message(STATUS "RPATH settings: ${CMAKE_INSTALL_RPATH}")
endif()

#--------------------------------------------------------------
# ==== CMake symbols ===
#--------------------------------------------------------------
message(STATUS "C++   COMPILER  : ${CMAKE_CXX_COMPILER}!")
message(STATUS "CMake GENERATOR : ${CMAKE_GENERATOR}")
message(STATUS "CMake BUILD_TYPE: ${CMAKE_BUILD_TYPE}\n")

message(STATUS "CMake prefix  path: \"${CMAKE_PREFIX_PATH}\"")
message(STATUS "CMake project path: \"${CMAKE_SOURCE_DIR}\"")
message(STATUS "CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")

message("== PROJ_DIR:         ${PROJ_DIR}")
message("== CMAKE_DIR:        ${CMAKE_DIR}")
message("== PROJ_INS_DIR:     ${PROJ_INS_DIR}")
message("== PROJ_SUB_DIR:     ${PROJ_SUB_DIR}")
message("== CMAKE_BINARY_DIR: ${PROJ_SUB_DIR}")

#--------------------------------------------------------------
# Используемые стандартные библиотеки
#--------------------------------------------------------------
include(${CMAKE_DIR}/find_tools.cmake)
include(${CMAKE_DIR}/build_tools.cmake)

#--------------------------------------------------------------
# Подключаемые модули
#--------------------------------------------------------------
# Включаем необходимые вспомогательные модули
include(FetchContent)
include(ExternalProject)  # <- Критически важная строка

#--------------------------------------------------------------
# (-1-) Сборка OpenSSL
#--------------------------------------------------------------
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

#--------------------------------------------------------------
## (-2-) Сборка ZeroMQ
#--------------------------------------------------------------
set(ZMQ_ROOT_DIR ${PROJ_SUB_DIR}/libzmq)
set(ZMQ_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

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

# Указываем путь установки (уже установлено выше)
#set(CMAKE_INSTALL_PREFIX ${ZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем libzmq как подпроект с явными зависимостями
set(ZMQ_BUILD_TESTS OFF CACHE BOOL "Disable ZMQ tests" FORCE)
add_subdirectory(${ZMQ_ROOT_DIR})

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

#--------------------------------------------------------------
### (3) Настройка и установка cppzmq
#--------------------------------------------------------------
set(CPPZMQ_ROOT_DIR ${PROJ_SUB_DIR}/cppzmq)
set(CPPZMQ_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

set(CPPZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_EXAMPLES OFF)

# Указываем путь установки
#set(CMAKE_INSTALL_PREFIX ${CPPZMQ_INSTALL_DIR} CACHE PATH "Installation directory" FORCE)

# Добавляем cppzmq как подпроект
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "Disable CppZMQ tests" FORCE)
set(CPPZMQ_BUILD_EXAMPLES OFF CACHE BOOL "Disable CppZMQ examples" FORCE)
add_subdirectory(${CPPZMQ_ROOT_DIR})

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
add_subdirectory(${PROJ_SUB_DIR}/json)              # --- JSON
add_subdirectory(${PROJ_LIB_DIR}/factory)           # --- driver factory

# библиотеки драйверов
#add_subdirectory(${PROJ_OUT_DIR}/procont-plc)       # --- PLC program

add_subdirectory(${PROJ_SUB_DIR}/libmodbus)         # --- modbus
add_subdirectory(${PROJ_SUB_DIR}/CANopen)           # --- CANopen
add_subdirectory(${PROJ_SUB_DIR}/EtherCAT)          # --- EtherCAT

# Копирование конфигов в директорию сборки
configure_file( ${PROJ_DIR}/modules_config.json ${CMAKE_CURRENT_BINARY_DIR}/modules_config.json COPYONLY )
configure_file( ${PROJ_DIR}/zmq.properties ${CMAKE_CURRENT_BINARY_DIR}/zmq.properties COPYONLY )

#--------------------------------------------------------------
# 4) Главный исполняемый модуль ${proj} = 'procont-ex'
#--------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${proj} PRIVATE  -D_GNU_SOURCE -Wall -Wextra)
endif()

#set_target_properties(${proj} PROPERTIES CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
#target_compile_definitions(${proj} PRIVATE _GLIBCXX_DEBUG=1)

build_target( ${proj} EXE
    OPTS
        -g -O0 -w -fPIC

    PRPS
        CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"

    INCS
        ${PROJ_INC_DIR}
        ${PROJ_INC_DIR}/sd
        ${PROJ_INC_DIR}/zmq
        ${PROJ_SRC_DIR}/main
        ${PROJ_SUB_DIR}/json/include
        ${PROJ_SRC_DIR}/service/zmq

    SRCS
        :MASK ${PROJ_SRC_DIR}/main/*.cpp
        :MASK ${PROJ_SRC_DIR}/service/*.cpp
        :MASK ${PROJ_SRC_DIR}/service/zmq/*.cpp

    LNKS
        plc_main
        nlohmann_json
        libzmq
        cppzmq
        driver_factory
        modbus
        can_master
)

#--------------------------------------------------------------
### Dependencies ###
#--------------------------------------------------------------
# Устанавливаем связь с библиотекой plc_main
#--------------------------------------------------------------
#find_library(PLC_MAIN_LIB plc_main PATHS ${PROJ_DIR}/libs/program NO_DEFAULT_PATH)
#if(NOT PLC_MAIN_LIB)
#    message(FATAL_ERROR "plc_main library not found! Rebuild procont-plc subproject")
#else()
#    message(STATUS "Found plc_main at: ${PLC_MAIN_LIB}")
#    target_link_libraries(${proj} PRIVATE ${PLC_MAIN_LIB})
#endif()
#message(STATUS "Library search paths: ${CMAKE_LIBRARY_PATH}")

# Поиск платформозависимой версии библиотеки
find_library(PLC_MAIN_LIB plc_main
        PATHS ${PLC_MAIN_LIB_DIR}
        NO_DEFAULT_PATH
)

if(NOT PLC_MAIN_LIB)
    message(FATAL_ERROR "plc_main library not found for ${LIB_ARCH} at ${PLC_MAIN_LIB_DIR}")
else()
    message(STATUS "Found plc_main at: ${PLC_MAIN_LIB}")

    # Для динамической загрузки добавляем путь к библиотеке в RPATH
    set_target_properties(${proj} PROPERTIES
            INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../lib:\$ORIGIN/../libs/${LIB_ARCH}/program"
    )
    target_link_libraries(${proj} PRIVATE ${PLC_MAIN_LIB})
endif()


# Устанавливаем связь с библиотекой systemd
#--------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD libsystemd)

if(SYSTEMD_FOUND AND LINUX)
    message(STATUS "Systemd development files found")
    target_compile_definitions(${proj} PRIVATE HAVE_SYSTEMD=1)
    target_include_directories(${proj} PRIVATE ${SYSTEMD_INCLUDE_DIRS})
    target_link_libraries(${proj} PRIVATE ${SYSTEMD_LIBRARIES})
else()
    message(WARNING "Systemd development files not found - sd_notify will be disabled")
    #target_compile_definitions(${proj} PRIVATE NO_SYSTEMD=1)
endif()

#--------------------------------------------------------------
# Установка компонентов
#--------------------------------------------------------------
install(TARGETS ${proj}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# Создаем каталог для service файлов внутри .install
set(SYSTEMD_LOCAL_DIR "${PROJ_INS_DIR}/systemd")
file(MAKE_DIRECTORY "${SYSTEMD_LOCAL_DIR}")

install(DIRECTORY
        DESTINATION "${PROJ_INS_DIR}/etc"
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
install(FILES ${PROJ_DIR}/modules_config.json DESTINATION "${PROJ_INS_DIR}/etc")
install(FILES ${PROJ_DIR}/zmq.properties DESTINATION "${PROJ_INS_DIR}/etc")

# Добавить сообщение для логирования
message(STATUS "Service configs will be in: ${PROJ_INS_DIR}/etc")

##--------------------------------------------------------------
## Systemd service installation
##--------------------------------------------------------------
if(UNIX AND NOT APPLE)
    # 1. Генерация файла окружения
    configure_file(
            ${PROJ_DIR}/procont-environment.in
            ${CMAKE_BINARY_DIR}/procont-environment
            @ONLY
    )

    # Установка
    install(FILES
            ${CMAKE_BINARY_DIR}/procont-environment
            DESTINATION "${PROJ_INS_DIR}/etc"
            PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ
    )

    # 2. Configure service file (from template)
    # Определяем пользователя сервиса
    set(SERVICE_USER "master")  # Или другое значение
    configure_file(
            ${PROJ_DIR}/${PROJECT_NAME}.service.in
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
            @ONLY
    )

    # Install service file локально
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
            DESTINATION "${SYSTEMD_LOCAL_DIR}"
    )

    # 3. Install startup script локально
    install(PROGRAMS
            ${PROJ_DIR}/${PROJECT_NAME}-startup.sh
            DESTINATION "${PROJ_INS_DIR}/bin"
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE
    )

    # 4. Генерация скрипта для установки сервиса
    file(GENERATE
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/install_service.sh"
            CONTENT
"#!/bin/bash
sudo cp \"${SYSTEMD_LOCAL_DIR}/${PROJECT_NAME}.service\" /lib/systemd/system/
sudo systemctl daemon-reload
echo \"Service installed. Run manually:\"
echo \"  sudo systemctl enable ${PROJECT_NAME}.service\"
echo \"  sudo systemctl start ${PROJECT_NAME}.service\""
    )

    # Устанавливаем скрипт в /bin
    install(PROGRAMS
            "${CMAKE_CURRENT_BINARY_DIR}/install_service.sh"
            DESTINATION "${PROJ_INS_DIR}/bin"
    )

    message(STATUS "Systemd service will be installed locally to: ${SYSTEMD_LOCAL_DIR}")
    message(STATUS "Use ${PROJ_INS_DIR}/bin/install_service.sh for system installation")

endif()

#--------------------------------------------------------------
### post-install скрипт для автоматического включения службы:
### - Закомментировано в связи с локальной установкой без sudo
#--------------------------------------------------------------
#if(LINUX)
#install(CODE "
#        execute_process(
#            COMMAND systemctl daemon-reload
#            COMMAND systemctl enable ${PROJECT_NAME}.service
#            WORKING_DIRECTORY /
#        )
#    ")
#endif()

#--------------------------------------------------------------
MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")

#--------------------------------------------------------------
