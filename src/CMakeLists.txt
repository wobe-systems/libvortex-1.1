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
## Windows 64 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-64)

  set(PREPROCESSOR_DEF -DVERSION=\"${VORTEXVER}\" -D__axl_disable_broken_bool_def__ -DPIC -DHAVE_VSCPRINTF)
  # Additional library definition file in case of Visual Studio:
  set(VORTEX_DEF libvortex-1.1.def)

  set(VORTEX_LOCAL libvortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.dll)
  set(LIBWS2 ws2_32.dll)
  
  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-64)

#######################################################
## Windows 32 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-32)
  
  set(PREPROCESSOR_DEF -DVERSION=\"${VORTEXVER}\" -D__axl_disable_broken_bool_def__ -DPIC -DHAVE_VSCPRINTF)
  # Additional library definition file in case of Visual Studio:
  set(VORTEX_DEF libvortex-1.1.def)

  set(VORTEX_LOCAL libvortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

  set(LIBAXL libaxl.dll)
  set(LIBWS2 ws2_32.dll)
  
  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.so)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.so)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.so)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)

#######################################################
## FreeBSD 32
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.so)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)

#######################################################
## FreeBSD 64
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -ansi -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL vortex-1.1)
  set(VORTEX_LOCAL_STATIC vortex-1.1_static)
  set(VORTEX_LIB_NAME ${VORTEX_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.so)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)

#######################################################

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (..)
INCLUDE_DIRECTORIES (../../libaxl/src)

ADD_DEFINITIONS (${COMPILE_ARGS} ${PREPROCESSOR_DEF})

ADD_LIBRARY( ${VORTEX_LOCAL}        SHARED ${VORTEX_SOURCES_HEADER} ${VORTEX_SOURCES} ${VORTEX_DEF})
TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL}         ${LIBAXL} ${LIBWS2} ${CMAKE_THREAD_LIBS_INIT})

if (${BUILD_STATIC} STREQUAL true)
  ADD_LIBRARY( ${VORTEX_LOCAL_STATIC} STATIC ${VORTEX_SOURCES_HEADER} ${VORTEX_SOURCES} ${VORTEX_DEF})
  TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL_STATIC} ${LIBAXL} ${LIBWS2} ${CMAKE_THREAD_LIBS_INIT})
  set_target_properties(${VORTEX_LOCAL_STATIC}  PROPERTIES OUTPUT_NAME ${VORTEX_LOCAL})
endif (${BUILD_STATIC} STREQUAL true)

INSTALL (TARGETS ${VORTEX_LOCAL}       DESTINATION ${CMAKE_BINARY_DIR}/build/lib)
if (${BUILD_STATIC} STREQUAL true)
  INSTALL (TARGETS ${VORTEXLOCAL_STATIC} DESTINATION ${CMAKE_BINARY_DIR}/build/static)
endif (${BUILD_STATIC} STREQUAL true)


























