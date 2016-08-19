cmake_minimum_required(VERSION 2.8) 

project(LabCryptoOrg-abettor-cc)

if (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

set(BIN_INSTALL_DIR "/usr/bin/" CACHE PATH "")
set(HEADERS_INSTALL_DIR "/usr/include")
set(LIB_INSTALL_DIR "/usr/lib")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

link_directories("/usr/local/lib")
if (APPLE)
  link_directories("/opt/local/lib/")
endif()

include_directories(${PROJECT_INCLUDE_DIR})
include_directories("/usr/include/postgresql")

if (APPLE)
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wno-writable-strings -Wno-deprecated-register -Wno-unused-function")
elseif (UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes -Wno-write-strings -Wno-unused-but-set-variable -Wno-sign-compare -Wno-unused-function")
endif()

add_library(abettor-cc-conf SHARED 
  ${PROJECT_SOURCE_DIR}/conf/config_manager.cc
)

add_library(abettor-cc-date SHARED 
  ${PROJECT_SOURCE_DIR}/date/helper.cc
)

add_library(abettor-cc-db SHARED 
  ${PROJECT_SOURCE_DIR}/db/pgsql/driver.cc
)

add_library(abettor-cc-os SHARED 
  ${PROJECT_SOURCE_DIR}/os/proc.cc
)

add_library(abettor-cc-string SHARED 
  ${PROJECT_SOURCE_DIR}/string/helper.cc
)

add_library(abettor-cc-unicode SHARED 
  ${PROJECT_SOURCE_DIR}/unicode/unicode.cc
)

install(DIRECTORY 
  ${PROJECT_INCLUDE_DIR}/org 
  DESTINATION 
  ${HEADERS_INSTALL_DIR} 
  FILES_MATCHING 
  PATTERN "*.h"
)

install(TARGETS
  abettor-cc-conf
  abettor-cc-date
  abettor-cc-db
  abettor-cc-os
  abettor-cc-string
  abettor-cc-unicode
  DESTINATION
  ${LIB_INSTALL_DIR}
)

add_custom_target(uninstall
  COMMAND rm -rfv ${LIB_INSTALL_DIR}/libabettor-cc*
  COMMAND rm -rfv ${HEADERS_INSTALL_DIR}/org/labcrypto/abettor
)
