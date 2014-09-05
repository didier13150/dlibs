################################################################################
# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.
################################################################################

SET( MYSQL_LIB_NAMES mysqlclient mysqlclient_r )
find_library( MYSQL_LIBRARY
              NAMES ${MYSQL_LIB_NAMES}
              PATH /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64 /opt/mysql/lib /opt/mysql/lib64
)
             
find_path( MYSQL_INCLUDE_DIR
           mysql.h
           /usr/include
           /usr/include/mysql
           /usr/local/include
           /usr/local/include/mysql
           /opt/mysql/include
           
)
          
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
