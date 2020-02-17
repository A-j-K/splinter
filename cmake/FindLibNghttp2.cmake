# LIBNGHTTP2_INCLUDE_DIR
# LIBNGHTTP2_LIB
# LibNghttp2_FOUND

set(LibNghttp2_EXTRA_PREFIXES /usr /usr/local /opt/local "$ENV{HOME}")
foreach(prefix ${LibNghttp2_EXTRA_PREFIXES})
  list(APPEND LibNghttp2_INCLUDE_PATHS "${prefix}/include")
  list(APPEND LibNghttp2_LIB_PATHS "${prefix}/lib")
endforeach()

find_path(LIBNGHTTP2_INCLUDE_DIR nghttp2/nghttp2.h PATHS ${LibNghttp2_INCLUDE_PATHS})
find_library(LIBNGHTTP2_LIB NAMES libnghttp2.a PATHS ${LibNghttp2_LIB_PATHS})

if (LIBNGHTTP2_INCLUDE_DIR)
  message(STATUS "Found nghttp2 include: ${LIBNGHTTP2_INCLUDE_DIR}")
else ()
  message(STATUS "Not found nghttp2 include")
endif ()

if (LIBNGHTTP2_LIB)
  message(STATUS "Found nghttp2 lib: ${LIBNGHTTP2_LIB}")
else()
  message(STATUS "Not found nghttp2 lib")
endif ()

if (LIBNGHTTP2_LIB AND LIBNGHTTP2_INCLUDE_DIR)
  set(LibNghttp2_FOUND TRUE)
  set(LIBNGHTTP2_LIB ${LIBNGHTTP2_LIB} ${LIBNGHTTP2_PTHREAD_LIB})
else ()
  set(LibNghttp2_FOUND FALSE)
endif ()

if (LibNghttp2_FOUND)
  if (NOT LibNghttp2_FIND_QUIETLY)
    message(STATUS "Found libnghttp2: ${LIBNGHTTP2_LIB}")
  endif ()
else ()
  if (LibNghttp2_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find libnghttp2.")
  endif ()
  message(STATUS "libnghttp2 NOT found.")
endif ()

mark_as_advanced(
    LIBNGHTTP2_LIB
    LIBNGHTTP2_INCLUDE_DIR
  )

