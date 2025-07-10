project(driver_factory LANGUAGES CXX)

# Настройки видимости символов
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)

add_library(driver_factory SHARED driver_factory.cpp)

target_include_directories(driver_factory PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(driver_factory PUBLIC cxx_std_17)

# Экспорт символов
if(WIN32)
    target_compile_definitions(driver_factory PRIVATE DRIVER_API_EXPORTS)
endif()