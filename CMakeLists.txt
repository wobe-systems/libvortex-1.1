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
## LINUX 64 bit
#######################################################
if (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)

  set(PROJECT linux_x86-64)

  set(IS64BIT true)
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  include (CPack)

  set (CMAKE_FIND_LIBRARY_PREFIXES lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .so)

  set (LIBSSL_LOCATION /usr/lib/x86_64-linux-gnu)
  set (LIBAXL_LOCATION /home/akristmann/libaxl/build/lib)

  set (PLATFORM_FOUND true)  

endif (${VORTEX_TARGET_PLATFORM} STREQUAL linux_x86-64)
#######################################################

if (${PLATFORM_FOUND} STREQUAL true)

  MESSAGE(PLATFORM FOUND)

  #######################################################
  ## Project / Solution- File:
  #######################################################
  PROJECT( vortex )
  find_package (Threads)
  find_library (LIBAXL NAMES axl PATHS ${LIBAXL_LOCATION} NO_DEFAULT_PATH)
  find_library (LIBSSL NAMES ssl PATHS ${LIBSSL_LOCATION} NO_DEFAULT_PATH)
  MESSAGE (STATUS "CMAKE_LIBRARY_PATH  ${LIBSSL_LOCATION}")

  #######################################################
  ## Source and destination directories:
  #######################################################
  ADD_SUBDIRECTORY(src)
  ADD_SUBDIRECTORY(tls)
  ADD_SUBDIRECTORY(test)
 
else (${PLATFORM_FOUND} STREQUAL true)
  message( SEND_ERROR "Unknown target platform / please check \"AXL_TARGET_PLATFORM\"" )
endif (${PLATFORM_FOUND} STREQUAL true)


























