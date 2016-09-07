MESSAGE("ENTERED VORTEX TEST SOURCE DIRECTORY")

set (TEST_SOURCES vortex-regression-client.c)

source_group("Sourcefiles" FILES ${VORTEX_SOURCES})

#######################################################
## LINUX 64 bit
#######################################################

#gcc -DHAVE_CONFIG_H -I. -I.. -I../src -I../tunnel -I../pull -I../alive -I../xml-rpc -I../http -I../external  -I/usr/include/axl  -pthread -I/include -Wstrict-prototypes -Wall -Werror -g -fstack-#protector-all -Wstack-protector -D__axl_disable_broken_bool_def__ -DVERSION=\""1.1.17.b2333"\" -I../src -DVORTEX_HAVE_POLL=1 -DVORTEX_HAVE_EPOLL=1 -DENABLE_VORTEX_LOG -DENABLE_TUNNEL_SUPPORT -#DENABLE_PULL_SUPPORT  -DENABLE_XML_RPC_SUPPORT -DENABLE_SASL_SUPPORT -I../sasl -DENABLE_HTTP_SUPPORT -DENABLE_TLS_SUPPORT -I../tls    -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/#python2.7  -g -O2 -MT vortex-regression-client.o -MD -MP -MF .deps/vortex-regression-client.Tpo -c -o vortex-regression-client.o vortex-regression-client.c

if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(COMPILE_ARGS -Wall -Werror -g -pthread -Wstrict-prototypes -fstack-protector-all -Wstack-protector)
  set(PREPROCESSOR_DEF -DHAVE_CONFIG_H -D__axl_disable_broken_bool_def__ -DVERSION=\"1.1.17.b2333\" -DENABLE_VORTEX_LOG -DENABLE_TLS_SUPPORT) 

  set(TARGET_TEST vortex-regression-client)
  set(IS64BIT true)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (..)
INCLUDE_DIRECTORIES (../src)
INCLUDE_DIRECTORIES (../tls)
INCLUDE_DIRECTORIES (../tunnel)
INCLUDE_DIRECTORIES (../xml-rpc)
INCLUDE_DIRECTORIES (../pull)
INCLUDE_DIRECTORIES (../http)
INCLUDE_DIRECTORIES (../alive)
INCLUDE_DIRECTORIES (../external)
INCLUDE_DIRECTORIES (../../libaxl/src)


ADD_EXECUTABLE (${TARGET_TEST} ${TEST_SOURCES})

ADD_DEFINITIONS (${COMPILE_ARGS} ${PREPROCESSOR_DEF})

LINK_DIRECTORIES (${CMAKE_BINARY_DIR}/build/lib)

TARGET_LINK_LIBRARIES(${TARGET_TEST} ${ALIBAXL} ${VORTEX_LIB_NAME} ${VORTEX_LIB_NAME_TLS}) 

INSTALL (TARGETS ${TARGET_TEST} DESTINATION ${CMAKE_BINARY_DIR}/bin)
