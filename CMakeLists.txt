PROJECT(Dlibs)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
#if you don't want the full compiler output, remove the following line

MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY)
# allow more human readable "if then else" constructs
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )
SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR})
#CMAKE_ROOT
#this is just a basic CMakeLists.txt, for more information see the cmake manpage

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

option(WITH_TESTS "Enable building of unit tests" ON)
option(WITH_CXX11 "Build with the C++ 11 standard" ON)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-common -fstack-protector --param=ssp-buffer-size=4")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wundef -Wpointer-arith -Wno-long-long")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat=2 -Wmissing-format-attribute")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wchar-subscripts -Wwrite-strings")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align")
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -fstack-protector --param=ssp-buffer-size=4")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wpointer-arith -Wno-long-long")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -fno-rtti")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
  
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-add-needed -Wl,--as-needed -Wl,--no-undefined")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,relro")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-add-needed -Wl,--as-needed")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,relro")

IF(COMMAND CMAKE_POLICY)
   CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

FIND_PACKAGE (LibXml2 REQUIRED)
FIND_PACKAGE (Mysql QUIET)
#FIND_PACKAGE (PostgreSQL QUIET)
FIND_PACKAGE(Threads REQUIRED)
FIND_LIBRARY(REALTIME_LIBRARY NAMES rt PATH /usr/lib /usr/local/lib REQUIRED)


add_subdirectory(test)

# add a target to generate API documentation with Doxygen
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(doc
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      COMMENT "Generating API documentation with Doxygen" VERBATIM
                     )
ENDIF(DOXYGEN_FOUND)

# project version
SET( Dlibs_MAJOR_VERSION 1 )
SET( Dlibs_MINOR_VERSION 2 )
SET( Dlibs_PATCH_LEVEL 0 )
SET( Dlibs_SOVERSION 0 )
SET( Dlibs_VERSION ${Dlibs_MAJOR_VERSION}.${Dlibs_MINOR_VERSION}.${Dlibs_PATCH_LEVEL} )
SET( Dlibs_BUGREPORT "didier.fabert@gmail.com" )

# project options
OPTION( BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON )
IF( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE "Release" )
ENDIF()

IF(MYSQL_FOUND)
   SET( DMYSQL_SRCS dmysql.cpp )
   SET( DMYSQL_HEADERS_INSTALL dmysql.h )
   SET( DMYSQL_TEST_SRCS testdmysql.cpp )
   SET( HAVE_MYSQL TRUE )
   SET( DLIBS_HAVE_MYSQL TRUE )
ELSE(MYSQL_FOUND)
   UNSET( DMYSQL_SRCS )
   UNSET( DMYSQL_HEADERS_INSTALL )
   UNSET( DMYSQL_SRCS )
   UNSET( DMYSQL_TEST_SRCS )
   UNSET( HAVE_MYSQL )
   UNSET( DLIBS_HAVE_MYSQL )
   MESSAGE(STATUS "DMySQL will not be build, mysql include file or library was not found")
ENDIF(MYSQL_FOUND)

IF(POSTGRESQL_FOUND)
   SET( DPGSQL_SRCS dpgsql.cpp )
   SET( DPGSQL_HEADERS_INSTALL dpgsql.h )
   SET( DPGSQL_TEST_SRCS testdpgsql.cpp )
   SET( HAVE_PGSQL TRUE )
   SET( DLIBS_HAVE_PGSQL TRUE )
ELSE(POSTGRESQL_FOUND)
  UNSET( DPGSQL_SRCS )
  UNSET( DPGSQL_HEADERS_INSTALL )
  UNSET( DPGSQL_TEST_SRCS )
  UNSET( DPGSQL_SRCS )
  UNSET( HAVE_PGSQL )
  MESSAGE(STATUS "DPgSQL will not be build, pgsql include file or library was not found")
ENDIF(POSTGRESQL_FOUND)

INCLUDE_DIRECTORIES (${Dlibs_BINARY_DIR}
                     ${LIBXML2_INCLUDE_DIR}
                     ${MYSQL_INCLUDE_DIR}
                     ${POSTGRESQL_INCLUDE_DIR}
                     ${CMAKE_SOURCE_DIR}
                    )

set(Dlibs_HEADERS_INSTALL
    dstring.h
	dexception.h
	dlog.h
	dpoint.h
	drect.h
	dsettings.h
	dsmtp.h
	dsocket.h
	dtimer.h
	durl.h
	dsingleton.h
	dthread.h
	ddatabase.h
	dskeleton.h
	dprototype.h
	dsqlite.h
	dfactory.h
	dobs.h
	devent.h
	dappcmdline.h
	denv.h
	dprocess.h
	${DMYSQL_HEADERS_INSTALL}
	${DPGSQL_HEADERS_INSTALL}
   )

foreach(HFILE ${Dlibs_HEADERS_INSTALL})
	set(Dlibs_all_include "${Dlibs_all_include}#include <${HFILE}>\n")
endforeach(HFILE)

configure_file(${Dlibs_SOURCE_DIR}/dlibs.h.cmake
               ${Dlibs_BINARY_DIR}/dlibs.h)

configure_file(${Dlibs_SOURCE_DIR}/Doxyfile.cmake
               ${Dlibs_BINARY_DIR}/Doxyfile)

set(Dlibs_LIBRARY_SRCS
	${Dlibs_HEADERS_INSTALL}
	dstring.cpp
	dlog.cpp
	dsettings.cpp
	dsmtp.cpp
	dsocket.cpp
	dtimer.cpp
	durl.cpp
	ddatabase.cpp
	dsqlite.cpp
	dthread.cpp
	sqlite3.c
	dobs.cpp
	devent.cpp
	dappcmdline.cpp
	denv.cpp
	dprocess.cpp
    ${DMYSQL_SRCS}
	${DPGSQL_SRCS}
   )

set(DLIBSTEST_EXE_SRCS
    dlibstest.cpp
    testdstring.cpp
    testdtimer.cpp
    testdurl.cpp
    testdsockserver.cpp
    testdsockclient.cpp
    testdlog.cpp
    testdsmtp.cpp
    testdsettings.cpp
    testdexception.cpp
    testdsingleton.cpp
    testdthread.cpp
    testdsqlite.cpp
    testdfactory.cpp
    testdobs.cpp
    testdappcmdline.cpp
    testdpoint.cpp
    testdrect.cpp
    testdenv.cpp
    testdprocess.cpp
    ${DMYSQL_TEST_SRCS}
    ${DPGSQL_TEST_SRCS}
   )

set(DLIBSPATH_EXE_SRCS
    dlibspath.cpp
   )

set(TESTSOCKCLIENT_EXE_SRCS
    testdsockclient.cpp
    client.cpp
   )

#build shared libraries
ADD_LIBRARY(dlibs SHARED ${Dlibs_LIBRARY_SRCS})
SET_TARGET_PROPERTIES( dlibs PROPERTIES VERSION "${Dlibs_MAJOR_VERSION}.${Dlibs_MINOR_VERSION}.${Dlibs_PATCH_LEVEL}" SOVERSION ${Dlibs_SOVERSION} )

#for testing the shared library you probably need some test app too
ADD_EXECUTABLE(dlibspath ${DLIBSPATH_EXE_SRCS})
ADD_EXECUTABLE(dlibstest ${DLIBSTEST_EXE_SRCS})
ADD_EXECUTABLE(dlibstestdsockclient ${TESTSOCKCLIENT_EXE_SRCS})

#need to link to some other libraries ? just add them here
TARGET_LINK_LIBRARIES(dlibs
                      ${REALTIME_LIBRARY}
                      ${LIBXML2_LIBRARIES}
                      ${POSTGRESQL_LIBRARIES}
                      ${MYSQL_LIBRARIES}
)
TARGET_LINK_LIBRARIES(dlibspath dlibs)
TARGET_LINK_LIBRARIES(dlibstest dlibs)
TARGET_LINK_LIBRARIES(dlibstestdsockclient dlibs)

#add an install target here
INSTALL( FILES ${Dlibs_HEADERS_INSTALL} ${Dlibs_BINARY_DIR}/dlibs.h DESTINATION include/dlibs)
INSTALL( TARGETS dlibs DESTINATION lib )
INSTALL( PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dlibstest ${CMAKE_CURRENT_BINARY_DIR}/dlibspath ${CMAKE_CURRENT_BINARY_DIR}/dlibstestdsockclient DESTINATION bin )
INSTALL( FILES FindDlibs.cmake DESTINATION ${CMAKE_ROOT}/Modules )
