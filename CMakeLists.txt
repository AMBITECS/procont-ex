cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PNME "procont")
set(PNME_AUTHOR "ambitecs")
set(PNME_ADDRESS "https://ambi.biz/")

project(${PNME} VERSION 0.0.1 DESCRIPTION "${PNME} - integrated development environment for programming controller applications according to the international industrial standard IEC 61131-3" LANGUAGES C CXX)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Prefix.cmake")
#-------------------------------------------------------------------------------
# Set Production path (CMAKE_INSTALL_PREFIX) =>
#-------------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(
            # Set Project production install directory
            CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local/${proj}"
            # CMAKE_INSTALL_PREFIX "D:/Peter/.local/${proj}"
            CACHE PATH "Default install directory"
            FORCE
    )
    message("-- CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")
endif()

#-------------------------------------------------------------------------------
message(STATUS "C++ COMPILER == ${CMAKE_CXX_COMPILER_ID}!")
message("-- CMake prefix  path: \"${CMAKE_PREFIX_PATH}\"")
message("-- CMake project path: \"${CMAKE_SOURCE_DIR}\"")
message("-- CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")

#-------------------------------------------------------------------------------
# PROJ - Project specific vars
#-------------------------------------------------------------------------------
SET( PACKAGE "${proj}" )                            # "Name of package"
SET( PACKAGE_NAME "${NAME}" )                       # "Define full name of this package"
SET( PACKAGE_TARNAME "${PACKAGE}")                  # "Define short name of this package"
SET( PACKAGE_URL "ambi.biz/${PACKAGE}" )            # "Define home page for this package"
SET( PACKAGE_BUGREPORT "admin@${ambi.biz}" )        # "Define address where bug reports for this package"
SET( PACKAGE_STRING "${NAME} ${VERSION}" )          # "Define full name and version of this package"
SET( PACKAGE_VERSION "${VERSION}")                  # "Define version of this package"

# Install prefixes
SET( prefix            "${CMAKE_INSTALL_PREFIX}" )  # "Project install location"
SET( bindir_full       "${prefix}/bin" )            # "Binaries location"
SET( libdir_full       "${prefix}/lib" )            # "Libraries location"
SET( incdir_full       "${prefix}/include" )        # "Include files"
SET( datadir_full      "${prefix}/share" )          # "Data location"
SET( localedir_full    "${prefix}/share/locale" )   # "I18N locales"
SET( sysconfdir_full   "${prefix}/etc" )            # "Configure location"

SET( proj_bindir_full  "${bindir_full}" )           # "Binaries location for configurations"
SET( proj_libdir_full  "${libdir_full}" )           # "libraries location for configurations"
SET( proj_moddir_full  "${libdir_full}/${proj}" )   # "modules location for configurations"
SET( proj_incdir_full  "${incdir_full}/${proj}" )   # "Include files location for configurations"
SET( proj_datadir_full "${datadir_full}/${proj}")   # "data location for configurations"

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
add_subdirectory("src/procont-app-conf")
add_subdirectory("src/common/threads")

#-------------------------------------------------------------------------------
# Устанавливаем дополнительные цели (иконки, конфиги, документацию)
#-------------------------------------------------------------------------------
#install(DIRECTORY ${PROJ_DIR}/img DESTINATION ${prefix})
#install(DIRECTORY ${PROJ_DIR}/etc DESTINATION ${prefix})

#-------------------------------------------------------------------------------
#include(cmake/Postfix.cmake)
