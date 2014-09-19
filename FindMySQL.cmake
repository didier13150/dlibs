################################################################################
# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.
################################################################################

SET( MYSQL_LIB_PATHS
     /usr/lib
     /usr/lib64
     /usr/lib/mysql
     /usr/lib64/mysql
     /usr/local/lib
     /usr/local/lib64
     /usr/local/lib/mysql
     /usr/local/lib64/mysql
     /opt/mysql/lib
     /opt/mysql/lib64
)

SET( MYSQL_INCLUDE_PATHS
     /usr/include
     /usr/include/mysql
     /usr/local/include
     /usr/local/include/mysql
     /opt/mysql/include
)

find_library( MYSQL_LIBRARY mysqlclient ${MYSQL_LIB_PATHS} )
if( NOT MYSQL_LIBRARY )
    find_library( MYSQL_LIBRARY mysqlclient_r ${MYSQL_LIB_PATHS} )
endif( NOT MYSQL_LIBRARY )

find_path( MYSQL_INCLUDE_DIR mysql.h ${MYSQL_INCLUDE_PATHS} )

include( ${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( MYSQL REQUIRED_VARS MYSQL_LIBRARY MYSQL_INCLUDE_DIR )

IF (MYSQL_FOUND)
  set( MYSQL_LIBRARIES
       ${MYSQL_LIBRARY}
  )
  set( MYSQL_LIBRARY
       ${MYSQL_LIBRARIES}
  )
  set( MYSQL_INCLUDE_DIR
       ${MYSQL_INCLUDE_DIR}
  )
ENDIF (MYSQL_FOUND)

MARK_AS_ADVANCED(
  MYSQL_LIBRARY
  MYSQL_INCLUDE_DIR
)
