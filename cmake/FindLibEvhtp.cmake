# LIBEVHTP_INCLUDE_DIR
# LIBEVHTP_LIB
# LibEvhtp_FOUND

set(LibEvhtp_EXTRA_PREFIXES /usr /usr/local /opt/local "$ENV{HOME}")
foreach(prefix ${LibEvhtp_EXTRA_PREFIXES})
  list(APPEND LibEvhtp_INCLUDE_PATHS "${prefix}/include")
  list(APPEND LibEvhtp_LIB_PATHS "${prefix}/lib")
endforeach()

find_path(LIBEVHTP_INCLUDE_DIR evhtp/evhtp.h PATHS ${LibEvhtp_INCLUDE_PATHS})
find_library(LIBEVHTP_LIB NAMES evhtp PATHS ${LibEvhtp_LIB_PATHS})

if (LIBEVHTP_INCLUDE_DIR)
  message(STATUS "Found evhtp include: ${LIBEVHTP_INCLUDE_DIR}")
else ()
  message(STATUS "Not found evhtp include")
endif ()

if (LIBEVHTP_LIB)
  message(STATUS "Found evhtp lib: ${LIBEVHTP_LIB}")
else()
  message(STATUS "Not found evhtp lib")
endif ()

if (LIBEVHTP_LIB AND LIBEVHTP_INCLUDE_DIR)
  set(LibEvhtp_FOUND TRUE)
  set(LIBEVHTP_LIB ${LIBEVHTP_LIB} ${LIBEVHTP_PTHREAD_LIB})
else ()
  set(LibEvhtp_FOUND FALSE)
endif ()

if (LibEvhtp_FOUND)
  if (NOT LibEvhtp_FIND_QUIETLY)
    message(STATUS "Found libevhtp: ${LIBEVHTP_LIB}")
  endif ()
else ()
  if (LibEvhtp_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find libevhtp.")
  endif ()
  message(STATUS "libevhtp NOT found.")
endif ()

mark_as_advanced(
    LIBEVHTP_LIB
    LIBEVHTP_INCLUDE_DIR
  )

