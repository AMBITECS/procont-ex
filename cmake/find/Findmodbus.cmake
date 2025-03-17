include(${CMAKE_DIR}/PROJ-libfind.cmake)
find_mod(modbus
        NAMES modbus
        PATHS ./$install/lib64/
        INAMES modbus.h
        IPATHS ./$install/include/modbus
#        IPATHS /usr/local/include/modbus ~/.local/include/modbus ./$install/include/modbus
        )
