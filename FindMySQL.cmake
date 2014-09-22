################################################################################
# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.
################################################################################

set ( MYSQL_LIBRARIES_NAMES
      mysqlclient
      mysqlclient_r
)

set( MYSQL_LIB_PATHS
     /usr/lib
     /usr/local/lib
     /opt/lib
     /opt/mysql/lib
)

set( MYSQL_INCLUDE_PATHS
     /usr/include
     /usr/local/include
     /opt/include
     /opt/mysql/include
)

find_library( MYSQL_LIBRARY
              NAMES ${MYSQL_LIBRARIES_NAMES}
              PATHS ${MYSQL_LIB_PATHS}
              PATH_SUFFIXES mysql
)

find_path( MYSQL_INCLUDE_DIR
           NAMES mysql.h
           PATHS ${MYSQL_INCLUDE_PATHS}
           PATH_SUFFIXES mysql
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
