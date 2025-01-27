include(${CMAKE_DIR}/PROJ-libfind.cmake)
find_mod(modbus
        NAMES modbus
        INAMES modbus.h
        IPATHS /usr/local/include/modbus ~/.local/include/modbus
        )
