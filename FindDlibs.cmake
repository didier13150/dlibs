################################################################################
# Find the DLibs includes and library
#
#  DLIBS_INCLUDE_DIR - where to find dlibs.h, etc.
#  DLIBS_LIBRARY     - Library when using DLibs.
#  DLIBS_FOUND       - True if DLibs found.
################################################################################

IF (DLIBS_INCLUDE_DIR)
# Already in cache, be silent
  SET(DLIBS_INCLUDE_DIR TRUE)
ENDIF (DLIBS_INCLUDE_DIR)

FIND_PATH(DLIBS_INCLUDE_DIR
          dstring.h
          /usr/include/dlibs
          /usr/local/include/dlibs)

FIND_LIBRARY(DLIBS_LIBRARY
             NAMES dlibs
             PATH /usr/lib /usr/local/lib)

IF (DLIBS_INCLUDE_DIR AND DLIBS_LIBRARY)
   SET(DLIBS_FOUND TRUE)
ELSE (DLIBS_INCLUDE_DIR AND DLIBS_LIBRARY)
   SET(DLIBS_FOUND FALSE)
   SET( DLIBS_INCLUDE_DIR )
   SET( DLIBS_LIBRARY )
ENDIF (DLIBS_INCLUDE_DIR AND DLIBS_LIBRARY)


IF (DLIBS_FOUND)
   IF (NOT Dlibs_FIND_QUIETLY)
      MESSAGE(STATUS "Found DLibs: ${DLIBS_LIBRARY}")
   ENDIF (NOT Dlibs_FIND_QUIETLY)
ELSE (DLIBS_FOUND)
   IF (Dlibs_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find DLibs")
   ENDIF (Dlibs_FIND_REQUIRED)
ENDIF (DLIBS_FOUND)

MARK_AS_ADVANCED(
  DLIBS_LIBRARY
  DLIBS_INCLUDE_DIR
  )