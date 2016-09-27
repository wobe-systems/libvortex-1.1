#  libTML:  A BEEP based Messaging Suite
#  Copyright (C) 2015 wobe-systems GmbH
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation; either version 2.1
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this program; if not, write to the Free
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307 USA
#  
#  You may find a copy of the license under this software is released
#  at COPYING file. This is LGPL software: you are welcome to develop
#  proprietary applications using this library without any royalty or
#  fee but returning back any change, improvement or addition in the
#  form of source code, project image, documentation patches, etc.
#
#  Homepage:
#    http://www.libtml.org
#
#  For professional support contact us:
#
#    wobe-systems GmbH
#    support@libtml.org
#  
# Contributors:
#    wobe-systems GmbH

set(CMAKE_VERBOSE_MAKEFILE on)

#######################################################
## minimum required cmake version 
cmake_minimum_required(VERSION 3.1)

#######################################################
## set build parameter
#######################################################
SET (VORTEX_TARGET_PLATFORM win_x86-64 CACHE STRING "set the build target")
SET (USE_TEST no CACHE STRING "use regressiontest")
#######################################################
## Vortex - Version (used in subdirectory cMake)
## You can set this attribute calling cmake with
## an aditional option for example: 
## CMake ..... -DVORTEXVER=1.1.17x
#######################################################
SET (VORTEXVER 1.1.17 CACHE STRING "set Vortex version")
SET (SSL_INST_PATH / CACHE STRING "ssl installation path")

#######################################################
## set version parameter
#######################################################
set (VORTEX_MAJOR_VERSION 1)
set (VORTEX_MINOR_VERSION 1)
set (VORTEX_MICRO_VERSION 16)

set (CPACK_PACKAGE_VERSION_MAJOR "${VORTEX_MAJOR_VERSION}")
set (CPACK_PACKAGE_VERSION_MINOR "${VORTEX_MINOR_VERSION}")
set (CPACK_PACKAGE_VERSION_PATCH "${VORTEX_MICRO_VERSION}")
set (PLATFORM_FOUND false)

#######################################################
## Windows 64 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-64)
  set(PROJECT win_x86-64)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .dll)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/win_x86-64/axl/Release")
  LINK_DIRECTORIES("${SSL_INST_PATH}/release/win64")
  
  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-64)

#######################################################
## Windows 32 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-32)
  set(PROJECT win_x86-32)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .dll)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/win_x86-32/axl/Release")
  LINK_DIRECTORIES("${SSL_INST_PATH}/release/win32")

  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

  set(PROJECT linux_x86-64)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)

  set(PROJECT linux_x86-32)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)

  set(PROJECT linux_arm32)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_arm32)
#######################################################
## FreeBSD 32
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)

  set(PROJECT freeBSD_x86-32)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  
 
endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)

#######################################################
## FreeBSD 64
#######################################################

if (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)

  set(PROJECT freeBSD_x86-64)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  
 
endif (${VORTEX_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)

#######################################################
## OSX 32 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-32)

  set(PROJECT osx_x86-32)
  
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .dylib)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  
  
endif (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-32)

#######################################################
## OSX 64 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-64)

  set(PROJECT osx_x86-64)
  
  
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  
  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .dylib)

  include (CPack)

  LINK_DIRECTORIES("../libaxl/build/lib")
  LINK_DIRECTORIES("./build/lib")

  set (PLATFORM_FOUND true)  
  
endif (${VORTEX_TARGET_PLATFORM} STREQUAL osx_x86-64)

#######################################################

if (${PLATFORM_FOUND} STREQUAL true)

  MESSAGE(PLATFORM FOUND)

  #######################################################
  ## SSL autodetection:
  #######################################################
  find_library(SSL_LIB_PATH NAMES ssl)
  if (SSL_LIB_PATH AND EXISTS "${SSL_LIB_PATH}")
    get_filename_component(SSL_LIB_PATH ${SSL_LIB_PATH} DIRECTORY)
  endif()
  find_path(SSL_INCLUDE_DIR openssl/x509v3.h)
  if (SSL_INCLUDE_DIR AND EXISTS "${SSL_INCLUDE_DIR}/openssl/x509v3.h")
    set(SSL_INCLUDE_DIR ${SSL_INCLUDE_DIR})
  endif()
  message("-- ---------------------------------------------------------------")
  message("-- Automatic path detection:")
  message(STATUS "SSL_LIB_PATH:       " ${SSL_LIB_PATH})
  message(STATUS "SSL_INCLUDE_DIR:    " ${SSL_INCLUDE_DIR})

  #######################################################
  ## Project / Solution- File:
  #######################################################
  PROJECT( vortex )
  find_package (Threads)

  #######################################################
  ## Source and destination directories:
  #######################################################
  ADD_SUBDIRECTORY(src ${PROJECT}/src)
  ADD_SUBDIRECTORY(tls ${PROJECT}/tls)
  #############################
  # With regressiontest:
  if (${USE_TEST} STREQUAL yes)
    ADD_SUBDIRECTORY(test)
  endif (${USE_TEST} STREQUAL yes)
 
else (${PLATFORM_FOUND} STREQUAL true)
  message( SEND_ERROR "Unknown target platform / please check \"VORTEX_TARGET_PLATFORM\"" )
endif (${PLATFORM_FOUND} STREQUAL true)


























