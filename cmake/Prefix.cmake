if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif(POLICY CMP0091)

##-------------------------------------------------------------------------------
## By default, the version information is extracted from the git index. However,
## we can override this behavior by explicitly setting PROJ_VERSION and
## skipping the git checks. This is useful for cases where this project is being
## used independently of its original git repo (e.g. vendored in another project)
##-------------------------------------------------------------------------------
#if(NOT PROJ_VERSION)
#    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
#    include(PROJ_GitRevision)
#    git_describe(GitTagVersion --tags)
#    message(STATUS "GitTagVersion = \"${GitTagVersion}\"")
#    if(NOT ${GitTagVersion} MATCHES ".*-NOTFOUND") #if(NOT ${GitTagVersion} MATCHES "HEAD-HASH-NOTFOUND")
#        string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GitTagVersion}")
#        string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GitTagVersion}")
#        string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GitTagVersion}")
#        set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
#        set(PROJ_VERSION ${VERSION_SHORT})
#    else()
#        set(PROJ_VERSION 1.0.0)
#    endif()
#endif()
#
#string(REGEX MATCHALL "[\.]" VERSION_DOT_MATCHES ${PROJ_VERSION})
#list(LENGTH VERSION_DOT_MATCHES VERSION_DOT_COUNT)
#if(VERSION_DOT_COUNT EQUAL 2)
#    set(VERSION_SHORT ${PROJ_VERSION})
#else()
#    message(FATAL_ERROR "PROJ_VERSION must be in major.minor.patch format, e.g. 3.8.1. Got ${PROJ_VERSION}")
#endif()

#-------------------------------------------------------------------------------
# System platform specific
#-------------------------------------------------------------------------------
message(STATUS "Default CMAKE_PREFIX_PATH = \"${CMAKE_PREFIX_PATH}\"")

if (WIN32)
    message("-- OS WINDOWS detected!")

    # System environment paths for find_ functions
    set(FIND_USE_CMAKE_SYSTEM_PATH FALSE)

    set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} $ENV{Path})
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} $ENV{Lib})
    set(CMAKE_INCLUDE_PATH
            ${CMAKE_INCLUDE_PATH}
            $ENV{Include}
            #"C:/msys64/mingw64/x86_64-w64-mingw32/include"
            #"C:/msys64/usr/lib/gcc/x86_64-pc-msys/10.2.0/include"
    )
    include_directories(${CMAKE_INCLUDE_PATH})

    # Extend CMAKE_PREFIX_PATH
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/6.7.1/mingw_64")
    #set(QMAKE_LFLAGS_WINDOWS ${QMAKE_LFLAGS_WINDOWS} -Wl,--stack,32000000)

elseif(UNIX)

    message("-- OS of UNIX detected!")
    # Extend CMAKE_PREFIX_PATH
    set(CMAKE_PREFIX_PATH
            ${CMAKE_PREFIX_PATH}
            "$ENV{HOME}/Qt/5.15.2/gcc_64/"
            "$ENV{HOME}/Qt/6.7.1/gcc_64/"
    )

else()

    set(CMAKE_APPBUNDLE_PATH $ENV{PATH})
    set(CMAKE_FRAMEWORK_PATH $ENV{PATH})
    message(FATAL_ERROR "Unknown System Platform - STOP!!!")

endif()

#-------------------------------------------------------------------------------
# Detect platform x86|x64
#-------------------------------------------------------------------------------
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(proj_PlatformDir "x86")
else()
    set(proj_PlatformDir "x64")
endif()
message(STATUS "proj_PlatformDir - \'${proj_PlatformDir}\'")

#-------------------------------------------------------------------------------
