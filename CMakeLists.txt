cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PNME "procont")
set(PNME_AUTHOR "ambitecs")
set(PNME_ADDRESS "https://ambi.biz/")

project(${PNME}
        VERSION 0.0.1
        DESCRIPTION "${PNME} - integrated development environment for programming controller applications according to the international industrial standard IEC 61131-3" LANGUAGES C CXX)

set( PROJ ${PROJECT_NAME} )         # PROJ = project name in orig case
string( TOLOWER ${PROJ} proj )      # proj = project name in lowercase

SET( PACKAGE "${proj}" )                            # "Name of package"
SET( PACKAGE_NAME "${NAME}" )                       # "Define full name of this package"
SET( PACKAGE_TARNAME "${PACKAGE}")                  # "Define short name of this package"
SET( PACKAGE_URL "ambi.biz/${PACKAGE}" )            # "Define home page for this package"
SET( PACKAGE_BUGREPORT "admin@${ambi.biz}" )        # "Define address where bug reports for this package"
SET( PACKAGE_STRING "${NAME} ${VERSION}" )          # "Define full name and version of this package"
SET( PACKAGE_VERSION "${VERSION}")                  # "Define version of this package"

message(STATUS "PACKAGE == ${proj}")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Prefix.cmake")

#-------------------------------------------------------------------------------
# Set Production path (CMAKE_INSTALL_PREFIX)
#-------------------------------------------------------------------------------
#if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Set Project production install directory
#    if (WIN32)
#        set(CMAKE_INSTALL_PREFIX
#           "D:/Peter/.local/${proj}"
#        )
#    elseif(UNIX)
        set(CMAKE_INSTALL_PREFIX
                "$ENV{HOME}/.local" #/${proj}
        )
#    else()
#        message(FATAL_ERROR "Unknown System Platform - STOP!!!")
#    endif()
#endif()

#-------------------------------------------------------------------------------
message(STATUS "C++ COMPILER == ${CMAKE_CXX_COMPILER_ID}!")
message(STATUS "CMake prefix  path: \"${CMAKE_PREFIX_PATH}\"")
message(STATUS "CMake project path: \"${CMAKE_SOURCE_DIR}\"")
message(STATUS "CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")

# Set the installation path to the prefix path so that "find_package" looks into it
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_INSTALL_PREFIX})

#-------------------------------------------------------------------------------
# PROJ - Project specific vars
#-------------------------------------------------------------------------------
# Source prefixes
set( PROJ_DIR           ${CMAKE_SOURCE_DIR}     )   # PROJ project directory
set( PROJ_SRC_DIR       ${PROJ_DIR}/src         )   # PROJ sources directory
set( PROJ_INC_DIR       ${PROJ_DIR}/include     )   # PROJ includes directory
set( PROJ_MOD_DIR       ${PROJ_DIR}/src/modules )   # PROJ modules directory
set( PROJ_DAT_DIR       ${PROJ_DIR}/data        )   # PROJ data files directory
set( PROJ_UP1_DIR       ${PROJ_DIR}/..          )   # PROJ 1-level up directory
set( PROJ_UP2_DIR       ${PROJ_DIR}/../..       )   # PROJ 2-level up directory

# Target prefixes
set( PROJ_POT_PRX       "${name_short}_"            )   # target pot-files prefix
set( PROJ_MOD_PRX       "mod_"                      )   # target module filename prefix
set( PROJ_LIB_PRX       "lib"                       )   # target static library filename prefix
set( PROJ_DLL_PRX       "lib"                       )   # target dynamic library filename prefix

# Install prefixes
SET( prefix            "${CMAKE_INSTALL_PREFIX}" )  # "Project install location"
SET( dist_bin          "${prefix}/bin" )            # "Binaries location"
SET( dist_lib          "${prefix}/lib" )            # "Libraries location"
SET( dist_include      "${prefix}/include" )        # "Include files"
SET( dist_data         "${prefix}/share" )          # "Data location"
SET( dist_locale       "${prefix}/share/locale" )   # "I18N locales"
SET( dist_config       "${prefix}/etc" )            # "Configure location"

#SET( proj_bindir_full  "${dist_bin}" )              # "Binaries location for configurations"
#SET( proj_libdir_full  "${dist_lib}" )              # "libraries location for configurations"
#SET( proj_moddir_full  "${dist_lib}/${proj}" )      # "modules location for configurations"
#SET( proj_incdir_full  "${dist_include}/${proj}" )  # "Include files location for configurations"
#SET( proj_datadir_full "${dist_data}/${proj}")      # "data location for configurations"

#-------------------------------------------------------------------------------
# CMAKE module specific vars
#-------------------------------------------------------------------------------
set( CMAKE_DIR          ${PROJ_DIR}/cmake ) # CMAKE modules directory in project
set( CMAKE_FND_DIR      ${CMAKE_DIR}/find ) # CMAKE cmake find-modules directory
set( CMAKE_MODULE_PATH  ${CMAKE_DIR} ${CMAKE_FND_DIR} )

# CMAKE library prefixes
set( CMAKE_SHARED_MODULE_PREFIX     ${PROJ_MOD_PRX} )
set( CMAKE_STATIC_LIBRARY_PREFIX    ${PROJ_LIB_PRX} )
set( CMAKE_SHARED_LIBRARY_PREFIX    ${PROJ_DLL_PRX} )

# CMAKE binary outputs options directories
set( ARCHIVE_OUTPUT_PATH            ${CMAKE_BINARY_DIR}/${proj}/arc )
set( EXECUTABLE_OUTPUT_PATH         ${CMAKE_BINARY_DIR}/${proj}/bin )
set( LIBRARY_OUTPUT_PATH            ${CMAKE_BINARY_DIR}/${proj}/lib )
set( DB_OUTPUT_PATH                 ${CMAKE_BINARY_DIR}/${proj}/db  )

set( CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
# CMAKE target files permissions
#-------------------------------------------------------------------------------
set( PERM_FILE  OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ )
set( PERM_EXEC  OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
        WORLD_EXECUTE WORLD_READ )

#-------------------------------------------------------------------------------
# Include CMake options & helpers
#-------------------------------------------------------------------------------
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/PROJ-helpers.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/qt_translate.cmake")

ASSERT_OUT_OF_SOURCE_BUILD("Fatal! ${PROJ} - Requires an out-of-source build!")

# add_subdirectory("matiec")
add_subdirectory("src/common/threads")
add_subdirectory("src/procont-app-conf")
add_subdirectory("src/procont-ex")

#-------------------------------------------------------------------------------
# Устанавливаем дополнительные цели (иконки, конфиги, документацию)
#-------------------------------------------------------------------------------
#install(DIRECTORY ${PROJ_DIR}/img DESTINATION ${prefix})
#install(DIRECTORY ${PROJ_DIR}/etc DESTINATION ${prefix})

#-------------------------------------------------------------------------------
#include(cmake/Postfix.cmake)
