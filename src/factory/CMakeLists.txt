cmake_minimum_required(VERSION 3.25)
project(driver_factory VERSION 1.0.1 DESCRIPTION "Driver factory lib" LANGUAGES CXX)

#--------------------------------------------------------------
# Настройки видимости символов и стандартов
#--------------------------------------------------------------
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

#--------------------------------------------------------------
# Создание и настройка библиотеки
#--------------------------------------------------------------
add_library(driver_factory SHARED driver_factory.cpp)

# Явное указание свойств библиотеки
set_target_properties(driver_factory PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        OUTPUT_NAME "driver_factory"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "\$ORIGIN"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)

#--------------------------------------------------------------
# Настройки компиляции
#--------------------------------------------------------------
target_include_directories(driver_factory PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(driver_factory PUBLIC cxx_std_17)

# Экспорт символов (кросс-платформенный вариант)
target_compile_definitions(driver_factory PRIVATE
        $<$<BOOL:${WIN32}>:DRIVER_API_EXPORTS>
        $<$<NOT:$<BOOL:${WIN32}>>:DRIVER_API_VISIBILITY>
)

#--------------------------------------------------------------
# Установка библиотеки (с унифицированными путями)
#--------------------------------------------------------------
install(TARGETS driver_factory
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

#--------------------------------------------------------------
# Платформо-специфичные настройки
#--------------------------------------------------------------
if(UNIX AND NOT APPLE)
    target_compile_options(driver_factory PRIVATE
            -fPIC
            -Wall
            -Wextra
    )
    target_link_options(driver_factory PRIVATE
            -Wl,--no-undefined
            -Wl,--as-needed
    )

    # Для отладки зависимостей
    add_custom_command(TARGET driver_factory POST_BUILD
            COMMAND ${CMAKE_OBJDUMP} -p $<TARGET_FILE:driver_factory> | grep NEEDED
            COMMENT "Checking library dependencies"
    )
endif()

#--------------------------------------------------------------
# Дополнительные цели для разработки
#--------------------------------------------------------------
add_custom_target(driver_factory_debug
        COMMAND ${CMAKE_COMMAND} -E echo "=== Driver Factory Info ==="
        COMMAND ${CMAKE_COMMAND} -E echo "Library: $<TARGET_FILE:driver_factory>"
        COMMAND ${CMAKE_COMMAND} -E echo "Install path: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
        DEPENDS driver_factory
)
