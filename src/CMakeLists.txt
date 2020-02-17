
SET(FIND_LIBRARY_USE_LIB64_PATHS 1)
SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
	/usr/local/lib
	/usr/lib
)

FIND_PACKAGE(Threads)

SET(AppLib_SRCS
	app.c
	prog_args.c
	prog_config.c
	utils/llist.c
	utils/queue.c
	utils/base64.c
	utils/inthash.c
	utils/hashmap.c
	utils/ws_magic.c
	utils/longhash.c
	http_parser/http_parser.c
)

ADD_LIBRARY(splinter_lib STATIC
	${AppLib_SRCS}
)

TARGET_LINK_LIBRARIES(splinter_lib
        ssl
        event
	crypto
        nghttp2
	libconfig.a
	libconfig++.a
	libjansson.a
	event_extra
	event_openssl
	event_pthreads
	${CMAKE_THREAD_LIBS_INIT}
)
