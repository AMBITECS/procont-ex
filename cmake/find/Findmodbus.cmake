include(${CMAKE_DIR}/PROJ-libfind.cmake)
find_mod(modbus
        INAMES modbus.h
        IPATHS /usr/local/include/*
        )
