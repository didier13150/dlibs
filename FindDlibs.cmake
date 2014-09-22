################################################################################
# Find the DLibs includes and library
#
#  DLIBS_INCLUDE_DIR - where to find dlibs.h, etc.
#  DLIBS_LIBRARY     - Library when using DLibs.
#  DLIBS_FOUND       - True if DLibs found.
################################################################################

set( DLIBS_LIB_PATHS
     /usr/lib
     /usr/local/lib
     /opt/lib
     /opt/dlibs/lib
)

set( DLIBS_INCLUDE_PATHS
     /usr/include
     /usr/local/include
     /opt/include
     /opt/mysql/include
)

find_library( DLIBS_LIBRARY
              NAMES dlibs
              PATHS ${DLIBS_LIB_PATHS}
              PATH_SUFFIXES dlibs
)
             
find_path( DLIBS_INCLUDE_DIR
           NAMES dlibs.h
           PATHS ${DLIBS_INCLUDE_PATHS}
           PATH_SUFFIXES dlibs
)
          
include( ${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( DLIBS REQUIRED_VARS DLIBS_LIBRARY DLIBS_INCLUDE_DIR )

if( DLIBS_FOUND )
  set( DLIBS_LIBRARIES
       ${DLIBS_LIBRARY}
  )
  set( DLIBS_LIBRARY
       ${DLIBS_LIBRARIES}
  )
  set( DLIBS_INCLUDE_DIR
       ${DLIBS_INCLUDE_DIR}
  )
endif( DLIBS_FOUND )

mark_as_advanced(
  DLIBS_LIBRARY
  DLIBS_INCLUDE_DIR
)
