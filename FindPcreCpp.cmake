# Try to find libpcrecpp (Perl Compatible Regular Expressions)
#
# Once done this will define
#
# PCRECPP_FOUND - system has libpcre
# PCRECPP_INCLUDE_DIR - the libpcre include directory
# PCRECPP_LIBRARIES - Link these to use libpcre

if(PCRECPP_INCLUDE_DIR AND PCRECPP_LIBRARIES)
	# in cache already
	set(PCRECPP_FOUND TRUE)
else(PCRECPP_INCLUDE_DIR AND PCRECPP_LIBRARIES)
	if(NOT WIN32)
		# use pkg-config to get the directories and then use these values
		# in the FIND_PATH() and FIND_LIBRARY() calls
		find_package(PkgConfig)
		pkg_check_modules(PC_PCRE libpcre)
	endif(NOT WIN32)

	find_path(PCRECPP_INCLUDE_DIR
		NAMES
			pcrecpp.h
		HINTS
			${PCRE_PKG_INCLUDE_DIRS}
		PATHS
			/usr/include
			/usr/local/include
	)

	find_library(PCRECPP_LIBRARY
		NAMES
			pcrecpp
		HINTS
			${PCRE_PKG_LIBRARY_DIRS}
		PATHS
			/usr/lib
			/usr/local/lib
	)

	set(PCRECPP_LIBRARIES ${PCRECPP_LIBRARY})

	# handle the QUIETLY AND REQUIRED arguments AND set PCRE_FOUND to TRUE if
	# all listed variables are TRUE
	# include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(PCRECPP DEFAULT_MSG PCRECPP_LIBRARY PCRECPP_INCLUDE_DIR)

	mark_as_advanced(PCRECPP_INCLUDE_DIR PCRECPP_LIBRARY)
endif(PCRECPP_INCLUDE_DIR AND PCRECPP_LIBRARIES)
