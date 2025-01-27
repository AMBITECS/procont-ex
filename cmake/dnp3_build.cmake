#
# Builds the modbus library
#
# Outputs the following target:
#   dnp3
#
include(ExternalProject)

set(DNP3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils/dnp3_src)
set(DNP3_BIN ${CMAKE_CURRENT_BINARY_DIR}/utils/dnp3_src)

set(DNP3_DIST ${CMAKE_INSTALL_PREFIX})

set(DNP3_INCLUDES   ${DNP3_DIST}/include)
set(DNP3_LIB        ${DNP3_DIST}/lib)

#message("== MODBUS_DIST:         ${MODBUS_DIST}")

file(MAKE_DIRECTORY ${DNP3_INCLUDES})

ExternalProject_Add(
        libdnp3
        PREFIX ${DNP3_BIN}
        SOURCE_DIR ${DNP3_DIR}

        DOWNLOAD_COMMAND cd ${DNP3_DIR}
            #&& git clean -dfX

        COMMAND make distclean || /bin/true

#        CONFIGURE_COMMAND
#            ${MODBUS_DIR}/autogen.sh &&
#            ${MODBUS_DIR}/configure
#                --srcdir=${MODBUS_DIR}
#                --prefix=${MODBUS_DIST}
#                --enable-static=yes
#                --disable-shared

        BUILD_COMMAND ${CMAKE_COMMAND} --build . --target opendnp3
        INSTALL_COMMAND ${CMAKE_COMMAND} --install ${DNP3_BIN}

#        BUILD_BYPRODUCTS ${MODBUS_STATIC_LIB}
)

add_library(dnp3 STATIC IMPORTED GLOBAL)

add_dependencies(dnp3 libdnp3)

set_target_properties(dnp3 PROPERTIES IMPORTED_LOCATION ${DNP3_LIB})
set_target_properties(dnp3 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${DNP3_INCLUDES})