cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0121 OLD) # suppress warning on INDEX out-of-range

set(VERSION_SHORT "1.2.2")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(name_short "procont")
set(local_proj_name ${name_short}-threads)

project(${local_proj_name} VERSION ${VERSION_SHORT} )

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED) # QT_VERSION_MAJOR defined here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Xml)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
# PROJ target modules options sets
#-------------------------------------------------------------------------------
set(PROJ_OPTS_SETS STD)
set(PROJ_OPTS_STD -g -O2 -fPIC)             # Standard compiler options

# PROJ target modules definitions sets
set(PROJ_DEFS_SETS STD QT)
set(PROJ_DEFS_STD HAVE_CONFIG_H PIC)        # Standard defs set
set(PROJ_DEFS_QT                            # QT defs set
        QT_CORE_LIB
        QT_GUI_LIB
        QT_XML_LIB
        QT_WIDGETS_LIB
)

# PROJ target modules properties sets
set(PROJ_PRPS_SETS QTGEN)
set(PROJ_PRPS_QTGEN                         # Qt generation properties
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
)

#-------------------------------------------------------------------------------
add_module(${local_proj_name}
        INSTALL LIB
        OPTS -g -O0
        DEFS #:QT
        PRPS
            :QTGEN
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            VERSION ${VERSION_SHORT}
            EXPORT_NAME "Threads module"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${proj_PlatformDir}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${proj_PlatformDir}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${proj_PlatformDir}/bin"

        INCS  # Includes
            "${CMAKE_SOURCE_DIR}/src"

        SRCS  # Sources
        #:MASK ./*.qrc
        :MASK ./*.cpp

        LNKS  # Modules
            Qt::Core Qt::Gui Qt::Widgets Qt::Xml
)
