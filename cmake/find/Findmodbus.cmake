include(${CMAKE_DIR}/PROJ-libfind.cmake)
find_mod(modbus
        NAMES modbus
        PATHS
                ./utils/libmodbus/$install/lib/
#                ./utils/libmodbus/$install/lib64/

        INAMES modbus.h
        IPATHS ./utils/libmodbus/$install/include/modbus
#        IPATHS /usr/local/include/modbus ~/.local/include/modbus ./$install/include/modbus
        )
