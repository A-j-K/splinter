# LIBWSLAY_INCLUDE_DIR, where to find LibWslay headers
# LIBWSLAY_LIB, LibWslay libraries
# LibWslay_FOUND, If false, do not try to use libwslay

set(LibWslay_EXTRA_PREFIXES /usr/local /opt/local "$ENV{HOME}")
foreach(prefix ${LibWslay_EXTRA_PREFIXES})
  list(APPEND LibWslay_INCLUDE_PATHS "${prefix}/include")
  list(APPEND LibWslay_LIB_PATHS "${prefix}/lib")
endforeach()

find_path(LIBWSLAY_INCLUDE_DIR wslay/wslay.h PATHS ${LibWslay_INCLUDE_PATHS})
find_library(LIBWSLAY_LIB NAMES libwslay.a PATHS ${LibWslay_LIB_PATHS})

if (LIBWSLAY_LIB AND LIBWSLAY_INCLUDE_DIR)
  set(LibWslay_FOUND TRUE)
  set(LIBWSLAY_LIB ${LIBWSLAY_LIB} ${LIBWSLAY_PTHREAD_LIB})
else ()
  set(LibWslay_FOUND FALSE)
endif ()

if (LibWslay_FOUND)
  if (NOT LibWslay_FIND_QUIETLY)
    message(STATUS "Found libwslay: ${LIBWSLAY_LIB}")
  endif ()
else ()
  if (LibWslay_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find libwslay.")
  endif ()
  message(STATUS "libwslay NOT found.")
endif ()

mark_as_advanced(
    LIBJANSSON_LIB
    LIBJANSSON_INCLUDE_DIR
)

