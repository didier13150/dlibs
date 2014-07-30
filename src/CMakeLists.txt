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

set(DLIBSPATH_EXE_SRCS
    dlibspath.cpp
   )

foreach(HFILE ${Dlibs_HEADERS_INSTALL})
	set(Dlibs_all_include "${Dlibs_all_include}#include <${HFILE}>\n")
endforeach(HFILE)

configure_file(dlibs.h.cmake
               ${Dlibs_BINARY_DIR}/dlibs.h
              )
configure_file(config.h.cmake
               ${Dlibs_BINARY_DIR}/config.h
              )
              
include_directories (${Dlibs_BINARY_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${LIBXML2_INCLUDE_DIR}
                     ${MYSQL_INCLUDE_DIR}
                     ${POSTGRESQL_INCLUDE_DIR}
                    )
                    
#build shared libraries
add_library(dlibs SHARED ${Dlibs_LIBRARY_SRCS})
set_target_properties( dlibs PROPERTIES VERSION "${Dlibs_MAJOR_VERSION}.${Dlibs_MINOR_VERSION}.${Dlibs_PATCH_LEVEL}" SOVERSION ${Dlibs_SOVERSION} )

#for testing the shared library you probably need some test app too
add_executable(dlibspath ${DLIBSPATH_EXE_SRCS})

#need to link to some other libraries ? just add them here
target_link_libraries(dlibs
                      ${REALTIME_LIBRARY}
                      ${LIBXML2_LIBRARIES}
                      ${POSTGRESQL_LIBRARIES}
                      ${MYSQL_LIBRARIES}
)
target_link_libraries(dlibspath dlibs)
   
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

#add an install target here
install( FILES ${Dlibs_HEADERS_INSTALL} ${Dlibs_BINARY_DIR}/dlibs.h DESTINATION include/dlibs)
install( TARGETS dlibs DESTINATION lib )
install( PROGRAMS ${Dlibs_BINARY_DIR}/src/dlibspath DESTINATION bin )
