MESSAGE("ENTERED VORTEX SOURCE DIRECTORY")

set (VORTEX_SOURCES vortex.c
                    vortex_channel_pool.c
                    vortex_ctx.c   
                    vortex_errno.c
                    vortex_greetings.c
                    vortex_hash.c  
                    vortex_listener.c
                    vortex_profiles.c
                    vortex_reader.c   
                    vortex_support.c 
                    vortex_thread_pool.c
                    vortex_channel.c  
                    vortex_connection.c  
                    vortex_dtds.c  
                    vortex_frame_factory.c 
                    vortex_handlers.c 
                    vortex_io.c   
                    vortex_payload_feeder.c 
                    vortex_queue.c   
                    vortex_sequencer.c 
                    vortex_thread.c  
                    vortex_win32.c)

set (VORTEX_SOURCES_HEADER 
                    vortex-channel.dtd.h
                    vortex_channel.h
                    vortex_channel_pool.h
                    vortex_connection.h
                    vortex_connection_private.h
                    vortex_ctx.h
                    vortex_ctx_private.h
                    vortex_dtds.h
                    vortex_dtds_private.h
                    vortex_errno.h
                    vortex_frame_factory.h
                    vortex_greetings.h
                    vortex.h
                    vortex_handlers.h
                    vortex_hash.h
                    vortex_hash_private.h
                    vortex_io.h
                    vortex-listener-conf.dtd.h
                    vortex_listener.h
                    vortex_payload_feeder.h
                    vortex_payload_feeder_private.h
                    vortex_profiles.h
                    vortex_queue.h
                    vortex_reader.h
                    vortex_sequencer.h
                    vortex_support.h
                    vortex_thread.h
                    vortex_thread_pool.h
                    vortex_types.h
                    vortex_win32.h)

source_group("Headerfiles" FILES ${VORTEX_SOURCES_HEADER})
source_group("Sourcefiles" FILES ${VORTEX_SOURCES})

#######################################################
## LINUX 64 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"1.1.17.b2333\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ -D__axl_disable_broken_bool_def__ -DENABLE_VORTEX_LOG -DPIC )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(IS64BIT true)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (..)
INCLUDE_DIRECTORIES (../../libaxl/src)

ADD_DEFINITIONS (${COMPILE_ARGS} ${PREPROCESSOR_DEF})

ADD_LIBRARY( ${VORTEX_LOCAL}        SHARED ${VORTEX_SOURCES_HEADER} ${VORTEX_SOURCES})
#ADD_LIBRARY( ${VORTEX_LOCAL_STATIC} STATIC ${VORTEX_SOURCES_HEADER} ${VORTEX_SOURCES})

TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL}         ${LIBAXL} ${CMAKE_THREAD_LIBS_INIT})
#TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL_STATIC}  ${LIBAXL} ${CMAKE_THREAD_LIBS_INIT})

#set_target_properties(${VORTEX_LOCAL_STATIC}  PROPERTIES OUTPUT_NAME ${VORTEX_LOCAL})

INSTALL (TARGETS ${VORTEX_LOCAL}       DESTINATION ${CMAKE_BINARY_DIR}/build/lib)
#INSTALL (TARGETS ${VORTEXLOCAL_STATIC} DESTINATION ${CMAKE_BINARY_DIR}/build/static)

























