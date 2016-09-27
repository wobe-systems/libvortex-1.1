MESSAGE("ENTERED VORTEX TLS DIRECTORY")

set (VORTEX_TLS_SOURCES vortex-digest-tool.c
                        vortex_tls.c)

set (VORTEX_TLS_HEADERS vortex-tls.dtd.h
                        vortex_tls.h)

source_group("Headerfiles" FILES ${VORTEX_TLS_SOURCES})
source_group("Sourcefiles" FILES ${VORTEX_TLS_HEADERS})


#######################################################
## Windows 64 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-64)

  set(PREPROCESSOR_DEF -DVERSION=\"${VORTEXVER}\" -D__axl_disable_broken_bool_def__ -DPIC -DHAVE_VSCPRINTF)
  # Additional library definition file in case of Visual Studio:
  set(VORTEX_TLS_DEF libvortex-tls-1.1.def)

  set(VORTEX_LOCAL_TLS libvortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC libvortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(OPENSSL_INCLUDE_DIR ../${SSL_INST_PATH}/include/win64)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.dll)
  set(LIBSSL ssleay32.dll)
  set(LIBCRYPTO libeay32.dll)
  set(LIBVORTEX libvortex-1.1.dll)
  set(LIBWS2 ws2_32.dll)

  LINK_DIRECTORIES("../build/win_x86-64/src/Release")

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
  set(VORTEX_TLS_DEF libvortex-tls-1.1.def)

  set(VORTEX_LOCAL_TLS libvortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC libvortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(OPENSSL_INCLUDE_DIR ../${SSL_INST_PATH}/include/win32)
  set(BUILD_STATIC false)

  set(LIBAXL libaxl.dll)
  set(LIBSSL ssleay32.dll)
  set(LIBCRYPTO libeay32.dll)
  set(LIBVORTEX libvortex-1.1.dll)
  set(LIBWS2 ws2_32.dll)

  LINK_DIRECTORIES("../build/win_x86-32/src/Release")

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.so)
  set(LIBSSL libssl.so)
  set(LIBCRYPTO libcrypto.so)
  set(LIBVORTEX libvortex-1.1.so)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.so)
  set(LIBSSL libssl.so)
  set(LIBCRYPTO libcrypto.so)
  set(LIBVORTEX libvortex-1.1.so)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.so)
  set(LIBSSL libssl.so)
  set(LIBCRYPTO libcrypto.so)
  set(LIBVORTEX libvortex-1.1.so)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)

#######################################################
## FreeBSD 32
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.so)
  set(LIBSSL libssl.so)
  set(LIBCRYPTO libcrypto.so)
  set(LIBVORTEX libvortex-1.1.so)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)

#######################################################
## FreeBSD 64
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)
  
  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.so)
  set(LIBSSL libssl.so)
  set(LIBCRYPTO libcrypto.so)
  set(LIBVORTEX libvortex-1.1.so)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)

#######################################################
## OSX 32 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-32)

  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)

  ADD_DEFINITIONS ("-arch i386")
  set(CMAKE_C_FLAGS "-arch i386")

  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.dylib)
  set(LIBSSL libssl.dylib)
  set(LIBCRYPTO libcrypto.dylib)
  set(LIBVORTEX libvortex-1.1.dylib)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-32)

#######################################################
## OSX 64 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-64)

  set(COMPILE_ARGS     -Wall -Werror -g -O2 -Wstrict-prototypes -fstack-protector-all -Wstack-protector -pthread -fPIC)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -DVERSION=\"${VORTEXVER}\" -DPACKAGE_TOP_DIR=\"..\" -D__COMPILING_VORTEX__ )
  set(CMAKE_SHARED_LINKER_FLAGS -O2)

  ADD_DEFINITIONS ("-arch x86_64")
  set(CMAKE_C_FLAGS "-arch x86_64")

  set(VORTEX_LOCAL_TLS vortex-tls-1.1)
  set(VORTEX_LOCAL_TLS_STATIC vortex-tls-1.1_static)
  set(VORTEX_LIB_NAME_TLS ${VORTEX_LOCAL_TLS} PARENT_SCOPE)
  set(BUILD_STATIC false)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  set(LIBAXL libaxl.dylib)
  set(LIBSSL libssl.dylib)
  set(LIBCRYPTO libcrypto.dylib)
  set(LIBVORTEX libvortex-1.1.dylib)



  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-64)

#######################################################
## Include- directories:
if (SSL_INCLUDE_DIR)
  INCLUDE_DIRECTORIES (${SSL_INCLUDE_DIR})
endif()
INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (..)
INCLUDE_DIRECTORIES (../src)
INCLUDE_DIRECTORIES (../../libaxl/src)
INCLUDE_DIRECTORIES (${OPENSSL_INCLUDE_DIR})

ADD_DEFINITIONS (${COMPILE_ARGS} ${PREPROCESSOR_DEF})

ADD_LIBRARY( ${VORTEX_LOCAL_TLS}         SHARED ${VORTEX_TLS_HEADERS} ${VORTEX_TLS_SOURCES} ${VORTEX_TLS_DEF})
TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL_TLS}         ${LIBAXL} ${LIBVORTEX} ${CMAKE_THREAD_LIBS_INIT} ${LIBSSL} ${LIBCRYPTO} ${LIBWS2})

if (${BUILD_STATIC} STREQUAL true)
  ADD_LIBRARY( ${VORTEX_LOCAL_TLS_STATIC} STATIC ${VORTEX_TLS_HEADERS} ${VORTEX_TLS_SOURCES} ${VORTEX_TLS_DEF})
  TARGET_LINK_LIBRARIES( ${VORTEX_LOCAL_TLS_STATIC}  ${LIBAXL} ${LIBVORTEX} ${CMAKE_THREAD_LIBS_INIT} ${LIBSSL}${LIBCRYPTO} ${LIBWS2})
  set_target_properties(${VORTEX_LOCAL_TLS_STATIC}  PROPERTIES OUTPUT_NAME ${VORTEX_LOCAL_TLS})
endif (${BUILD_STATIC} STREQUAL true)

INSTALL (TARGETS ${VORTEX_LOCAL_TLS}       DESTINATION ${CMAKE_BINARY_DIR}/build/lib)
if (${BUILD_STATIC} STREQUAL true)
  INSTALL (TARGETS ${VORTEX_LOCAL_TLS_STATIC} DESTINATION ${CMAKE_BINARY_DIR}/build/static)
endif (${BUILD_STATIC} STREQUAL true)

