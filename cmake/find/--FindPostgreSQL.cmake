include(${CMAKE_DIR}/ATOM-libfind.cmake)
if (WIN32)
    find_lib(PostgreSQL
            INAMES libpq-fe.h
            IPATHS ${CMAKE_INCLUDE_PATH}
            )
elseif(UNIX)
    find_lib(PostgreSQL
            INAMES libpq-fe.h
            IPATHS /usr/include/*
            )
else()
    MESSAGE(FATAL_ERROR "Unknown System Platform - STOP!!!")
endif()