cmake_minimum_required(VERSION 2.8) 

project(abettor-cc)

if (UNIX)
  add_definitions(-D__UNIX__)
  set(BIN_INSTALL_DIR "/usr/bin/" CACHE PATH "")
  set(HEADERS_INSTALL_DIR "/usr/include")
  set(LIB_INSTALL_DIR "/usr/lib")
  include_directories("/usr/include/postgresql")
  if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-writable-strings -Wno-deprecated-register -Wno-unused-function")
    add_defnitions(-D__MACOS__)
    link_directories("/opt/local/lib/")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-attributes -Wno-write-strings -Wno-unused-but-set-variable -Wno-sign-compare -Wno-unused-function")
    add_definitions(-D__LINUX__)
    link_directories("/usr/local/lib")
  endif()
endif()

if (WIN32)
  # Change these paths to whatever that is valid for your system
  # include_directories("../ir.ntnaeem.kawthar.lib.external/openssl/include")
  # include_directories("../ir.ntnaeem.kawthar.lib.external/iconv/include")
  include_directories("../ir.ntnaeem.kawthar.lib.external/pq/include")
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-DUNICODE -D_UNICODE)
  add_definitions(-D__WIN32__)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${PROJECT_INCLUDE_DIR})

add_library(abettor-cc-conf STATIC 
  ${PROJECT_SOURCE_DIR}/conf/config_manager.cc
)

add_library(abettor-cc-date STATIC 
  ${PROJECT_SOURCE_DIR}/date/helper.cc
)

add_library(abettor-cc-db STATIC 
  ${PROJECT_SOURCE_DIR}/db/pgsql/driver.cc
)

add_library(abettor-cc-os STATIC 
  ${PROJECT_SOURCE_DIR}/os/proc.cc
)

add_library(abettor-cc-string STATIC 
  ${PROJECT_SOURCE_DIR}/string/helper.cc
)

add_library(abettor-cc-unicode STATIC 
  ${PROJECT_SOURCE_DIR}/unicode/unicode.cc
)

# install(DIRECTORY 
#   ${PROJECT_INCLUDE_DIR}/org 
#   DESTINATION 
#   ${HEADERS_INSTALL_DIR} 
#   FILES_MATCHING 
#   PATTERN "*.h"
# )
# 
# install(TARGETS
#   abettor-cc-conf
#   abettor-cc-date
#   abettor-cc-db
#   abettor-cc-os
#   abettor-cc-string
#   abettor-cc-unicode
#   DESTINATION
#   ${LIB_INSTALL_DIR}
# )
# 
# add_custom_target(uninstall
#   COMMAND rm -rfv ${LIB_INSTALL_DIR}/libabettor-cc*
#   COMMAND rm -rfv ${HEADERS_INSTALL_DIR}/org/labcrypto/abettor
# )
