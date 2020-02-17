# LIBCONFIG_INCLUDE_DIR, where to find LibConfig headers
# LIBCONFIG_LIB, LibConfig libraries
# LibConfig_FOUND, If false, do not try to use libwslay

set(LibConfig_EXTRA_PREFIXES /usr/local /opt/local "$ENV{HOME}")
foreach(prefix ${LibConfig_EXTRA_PREFIXES})
  list(APPEND LibConfig_INCLUDE_PATHS "${prefix}/include")
  list(APPEND LibConfig_LIB_PATHS "${prefix}/lib")
endforeach()

find_path(LIBCONFIG_INCLUDE_DIR libconfig.h PATHS ${LibConfig_INCLUDE_PATHS})
find_library(LIBCONFIG_LIB NAMES libconfig.a PATHS ${LibConfig_LIB_PATHS})

if (LIBCONFIG_LIB AND LIBCONFIG_INCLUDE_DIR)
  set(LibConfig_FOUND TRUE)
  set(LIBCONFIG_LIB ${LIBCONFIG_LIB} ${LIBCONFIG_PTHREAD_LIB})
else ()
  set(LibConfig_FOUND FALSE)
endif ()

if (LibConfig_FOUND)
  if (NOT LibConfig_FIND_QUIETLY)
    message(STATUS "Found libconfig: ${LIBCONFIG_LIB}")
  endif ()
else ()
  if (LibConfig_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find libconfig.")
  endif ()
  message(STATUS "libconfig NOT found.")
endif ()

mark_as_advanced(
    LIBCONFIG_LIB
    LIBCONFIG_INCLUDE_DIR
)

