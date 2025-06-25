cmake_minimum_required(VERSION 3.25)
project(procont_gluegenerator)

option(WERROR "Set all warnings to errors" ON)
set(CMAKE_CXX_STANDARD 11)

# Основной исполняемый файл
add_executable(glue_generator glue_generator_new.cpp)

# Установка, экспорт цели
set(INSTALL_DIR "/custom/install/path")  # Ваш кастомный путь

install(TARGETS glue_generator
        EXPORT glue_generatorTargets
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
#        LIBRARY DESTINATION ${INSTALL_DIR}/lib
#        ARCHIVE DESTINATION ${INSTALL_DIR}/lib
#        PUBLIC_HEADER DESTINATION ${INSTALL_DIR}/include
)

#cmake_minimum_required(VERSION 3.0.0)
#
## CMake build for Procont glue generator. The glue generator takes
## generated C code from the MATIEC compiler and then generates necessary
## glue to bind the MATIEC code with the OpenPLC runtime.
#project(procont_gluegenerator)
#
#option(WERROR "Set all warnings to errors" ON)
#
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#
## Optional build capabilities
#option(OPLCGLUE_ALL "Build all optional projects (tests)" OFF)
#option(OPLCGLUE_TEST "Build tests" OFF)
#
#if(OPLCGLUE_ALL)
#	message("enabling all optional	 components")
#	set(OPLCGLUE_TEST ON)
#endif()
#
## The main application that we always build
#add_executable(glue_generator glue_generator_new.cpp)
#
#if(OPLCGLUE_TEST)
#	add_executable(glue_generator_test ./test/glue_generator_test.cpp)
#endif()
