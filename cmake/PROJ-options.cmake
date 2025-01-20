if (WIN32)
    OPTION( __WINDOWS__ "=ON: if you have OS WINDOWS" ON )
endif()
if (UNIX)
    OPTION( __UNIX__ "=ON: if you have UNIX like OS" ON )
endif()

#-------------------------------------------------------------------------------
# === OPTIONS block
#-------------------------------------------------------------------------------
OPTION( HAVE_LIBINTL_H    "=ON: if you have the <libintl.h> header file"        OFF )
OPTION( BUILD_SHARED_LIBS "=ON: if your want to create SHARED libs as shared"   ON )
