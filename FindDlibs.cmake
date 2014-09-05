################################################################################
# Find the DLibs includes and library
#
#  DLIBS_INCLUDE_DIR - where to find dlibs.h, etc.
#  DLIBS_LIBRARY     - Library when using DLibs.
#  DLIBS_FOUND       - True if DLibs found.
################################################################################

find_library( DLIBS_LIBRARY
              NAMES dlibs
              PATH /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
)
             
find_path( DLIBS_INCLUDE_DIR
           dstring.h
           /usr/include
           /usr/include/dlibs
           /usr/local/include
           /usr/local/include/dlibs
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
