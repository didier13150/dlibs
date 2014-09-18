project(Dlibs)

# project version
set( Dlibs_MAJOR_VERSION 1 )
set( Dlibs_MINOR_VERSION 2 )
set( Dlibs_PATCH_LEVEL 1 )
set( Dlibs_SOVERSION 0 )
set( Dlibs_VERSION ${Dlibs_MAJOR_VERSION}.${Dlibs_MINOR_VERSION}.${Dlibs_PATCH_LEVEL} )
set( Dlibs_BUGREPORT "didier.fabert@gmail.com" )

cmake_minimum_required(VERSION 2.4)
#if you don't want the full compiler output, remove the following line
mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)
# allow more human readable "if then else" constructs
set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH})

option(WITH_TESTS "Enable building of unit tests" ON)
option(WITH_CXX11 "Build with the C++ 11 standard" ON)
option(WITH_EXCEPTIONS "Build with exceptions enabled" ON)
option( BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON )
option( WITH_LCOV "Set to ON to build with code coverage" OFF )

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

if(WITH_EXCEPTIONS)
  add_definitions( -fexceptions )
endif(WITH_EXCEPTIONS)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-common -fstack-protector --param=ssp-buffer-size=4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wundef -Wpointer-arith -Wno-long-long")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat=2 -Wmissing-format-attribute")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wchar-subscripts -Wwrite-strings")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -fstack-protector --param=ssp-buffer-size=4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wpointer-arith -Wno-long-long")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
  
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-add-needed -Wl,--as-needed -Wl,--no-undefined")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,relro")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-add-needed -Wl,--as-needed")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,relro")

find_package (LibXml2 REQUIRED)
find_package (MySQL QUIET)
#find_package (PostgreSQL QUIET)
find_package(Threads REQUIRED)
find_library(REALTIME_LIBRARY NAMES rt PATH /usr/lib /usr/local/lib REQUIRED)

message(STATUS "Looking for utf8cpp")
find_path( UTF8CPP_INCLUDE_DIR "utf8.h" CMAKE_INCLUDE_PATH )
if(UTF8CPP_INCLUDE_DIR)
message(STATUS "utf8cpp found")
else()
message(FATAL_ERROR "utf8cpp library not found (install utf8cpp-devel).")
endif()

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    find_program(DOT_EXECUTABLE dot PATH)
    add_custom_target(doc
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      COMMENT "Generating API documentation with Doxygen" VERBATIM
                     )
endif(DOXYGEN_FOUND)

find_program(GIT_EXECUTABLE git PATH)
add_custom_target(changelog
                  ${GIT_EXECUTABLE} log --graph --decorate --abbrev-commit > ChangeLog
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  COMMENT "Regenerating ChangeLog" VERBATIM
                 )

if(WITH_LCOV)
    include(CodeCoverage)  
    set( CMAKE_BUILD_TYPE "Debug" )
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -O0 --coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    SETUP_TARGET_FOR_COVERAGE( lcov test ../lcov )
    message(STATUS "Build with code coverage")
else()
    if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O2" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2" )
    message(STATUS "Build with lcov")
endif(WITH_LCOV)
                 
# project options

if(MYSQL_FOUND)
   message(STATUS "MySQL found")
   set( DMYSQL_SRCS dmysql.cpp )
   set( DMYSQL_HEADERS_INSTALL dmysql.h )
   set( DMYSQL_TEST_SRCS testdmysql.cpp )
   set( HAVE_MYSQL TRUE )
   set( DLIBS_HAVE_MYSQL TRUE )
else(MYSQL_FOUND)
   unset( DMYSQL_SRCS )
   unset( DMYSQL_HEADERS_INSTALL )
   unset( DMYSQL_SRCS )
   unset( DMYSQL_TEST_SRCS )
   unset( HAVE_MYSQL )
   unset( DLIBS_HAVE_MYSQL )
   message(STATUS "DMySQL will not be build, mysql include file or library was not found")
endif(MYSQL_FOUND)

if(POSTGRESQL_FOUND)
   message(STATUS "DPgSQL found")
   set( DPGSQL_SRCS dpgsql.cpp )
   set( DPGSQL_HEADERS_INSTALL dpgsql.h )
   set( DPGSQL_TEST_SRCS testdpgsql.cpp )
   set( HAVE_PGSQL TRUE )
   set( DLIBS_HAVE_PGSQL TRUE )
else(POSTGRESQL_FOUND)
   unset( DPGSQL_SRCS )
   unset( DPGSQL_HEADERS_INSTALL )
   unset( DPGSQL_TEST_SRCS )
   unset( DPGSQL_SRCS )
   unset( HAVE_PGSQL )
   message(STATUS "DPgSQL will not be build, pgsql include file or library was not found")
endif(POSTGRESQL_FOUND)

configure_file(${Dlibs_SOURCE_DIR}/Doxyfile.cmake
               ${Dlibs_BINARY_DIR}/Doxyfile
               @ONLY
              )

configure_file(test-settings.xml.cmake
               ${Dlibs_BINARY_DIR}/tests/test-settings.xml
               @ONLY
              )

configure_file(lcov.sh.cmake
               ${Dlibs_BINARY_DIR}/lcov.sh
               @ONLY
              )

if(WITH_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(WITH_TESTS)
add_subdirectory(src)

install( FILES FindDlibs.cmake DESTINATION ${CMAKE_ROOT}/Modules )
