enable_testing()

find_path( CPPTEST_INCLUDE_DIR
           "cpptest.h"
           CMAKE_INCLUDE_PATH
         )

find_library(CPPTEST_LIBRARY NAMES cpptest)

configure_file(test.h.cmake
               ${Dlibs_BINARY_DIR}/test.h
              )

include_directories (.
                     ${Dlibs_BINARY_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${CPPTEST_INCLUDE_DIR}
                     ${LIBXML2_INCLUDE_DIR}
                     ${MYSQL_INCLUDE_DIR}
                     ${POSTGRESQL_INCLUDE_DIR}
                    )
                    
set( ALL_TEST_PARTS
     dstring
     dsingleton
     denv
     dappcmdline
     devent
     dprototype
     dfactory
     dobs
     dpoint
     dprocess
     drect
     dthread
     dtimer
     durl
     dsocket
     dsmtp
     dsqlite
     dexception
     dsettings
     dlog
     dbase64
   )

FOREACH( PART ${ALL_TEST_PARTS} )
    add_executable( "test${PART}" "test${PART}.cpp" )
    target_link_libraries( "test${PART}" dlibs ${CPPTEST_LIBRARY} ${REALTIME_LIBRARY})
    add_test(${PART} "${CMAKE_CURRENT_BINARY_DIR}/test${PART}" )
ENDFOREACH( PART )

if(MYSQL_FOUND)
  add_executable(testdmysql testdmysql.cpp)
  target_link_libraries(testdmysql dlibs ${CPPTEST_LIBRARY} ${MYSQL_LIBRARIES} ${REALTIME_LIBRARY})
  add_test(dmysql ${CMAKE_CURRENT_BINARY_DIR}/testdmysql)
endif(MYSQL_FOUND)
if(POSTGRESQL_FOUND)
  add_executable(testdpgsql testdpgsql.cpp)
  target_link_libraries(testdpgsql dlibs ${CPPTEST_LIBRARY} ${POSTGRESQL_LIBRARIES} ${REALTIME_LIBRARY})
  add_test(dpgsql ${CMAKE_CURRENT_BINARY_DIR}/testdpgsql)
endif(POSTGRESQL_FOUND)
