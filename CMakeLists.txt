cmake_minimum_required(VERSION 3.14)

set(PNME "procont")
set(PNME_AUTHOR "ambitecs")
set(PNME_ADDRESS "https://ambi.biz/")

project(${PNME} VERSION 0.0.1 DESCRIPTION "${PNME} - integrated development environment for programming controller applications according to the international industrial standard IEC 61131-3" LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/PROJ-helpers.cmake")
ASSERT_OUT_OF_SOURCE_BUILD("Fatal! ${PROJ} - Requires an out-of-source build!")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/qt_translate.cmake")

#add_subdirectory("matiec")
add_subdirectory("src/procont-app-conf")
add_subdirectory("src/common/threads")
