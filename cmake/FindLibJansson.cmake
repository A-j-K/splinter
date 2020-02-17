# LIBJANSSON_INCLUDE_DIR, where to find LibJansson headers
# LIBJANSSON_LIB, LibJansson libraries
# LibJansson_FOUND, If false, do not try to use libevent

set(LibJansson_EXTRA_PREFIXES /usr/local /opt/local "$ENV{HOME}")
foreach(prefix ${LibJansson_EXTRA_PREFIXES})
  list(APPEND LibJansson_INCLUDE_PATHS "${prefix}/include")
  list(APPEND LibJansson_LIB_PATHS "${prefix}/lib")
endforeach()

find_path(LIBJANSSON_INCLUDE_DIR jansson.h PATHS ${LibJansson_INCLUDE_PATHS})
find_library(LIBJANSSON_LIB NAMES libjansson.a PATHS ${LibJansson_LIB_PATHS})

if (LIBJANSSON_LIB AND LIBJANSSON_INCLUDE_DIR)
  set(LibJansson_FOUND TRUE)
  set(LIBJANSSON_LIB ${LIBJANSSON_LIB} ${LIBJANSSON_PTHREAD_LIB})
else ()
  set(LibJansson_FOUND FALSE)
endif ()

if (LibJansson_FOUND)
  if (NOT LibJansson_FIND_QUIETLY)
    message(STATUS "Found libjansson: ${LIBJANSSON_LIB}")
  endif ()
else ()
  if (LibJansson_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find libjansson.")
  endif ()
  message(STATUS "libjansson NOT found.")
endif ()

mark_as_advanced(
    LIBJANSSON_LIB
    LIBJANSSON_INCLUDE_DIR
)

