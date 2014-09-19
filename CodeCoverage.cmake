#
# From Lars Bilke and Joakim Söderberg
#

FIND_PROGRAM( GCOV_PATH gcov )
FIND_PROGRAM( LCOV_PATH lcov )
FIND_PROGRAM( GENHTML_PATH genhtml )
FIND_PROGRAM( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)

IF(NOT GCOV_PATH)
	MESSAGE(FATAL_ERROR "gcov not found! Aborting...")
ENDIF() # NOT GCOV_PATH

IF(NOT CMAKE_COMPILER_IS_GNUCXX)
	# Clang version 3.0.0 and greater now supports gcov as well.
	MESSAGE(WARNING "Compiler is not GNU gcc! Clang Version 3.0.0 and greater supports gcov as well, but older versions don't.")
	
	IF(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		MESSAGE(FATAL_ERROR "Compiler is not GNU gcc! Aborting...")
	ENDIF()
ENDIF(NOT CMAKE_COMPILER_IS_GNUCXX)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -O0 --coverage")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")

IF ( NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Coverage"))
  MESSAGE( WARNING "Code coverage results with an optimized (non-Debug) build may be misleading" )
ENDIF()


# Param _coverage_target     The name of new coverage target
# Param _test_targetrunner   The name of the target which runs the tests.
# Param _output_path         lcov output is generated on _output_path directory
FUNCTION(SETUP_TARGET_FOR_COVERAGE _coverage_target _test_target _output_path)

	IF(NOT LCOV_PATH)
		MESSAGE(FATAL_ERROR "lcov not found! Aborting...")
	ENDIF(NOT LCOV_PATH) 

	IF(NOT GENHTML_PATH)
		MESSAGE(FATAL_ERROR "genhtml not found! Aborting...")
	ENDIF(NOT GENHTML_PATH) 

	# Setup target
	ADD_CUSTOM_TARGET(${_coverage_target}
		
		# Cleanup lcov
		COMMAND ${LCOV_PATH} --directory . --zerocounters
        COMMAND ${LCOV_PATH} --ignore-errors source --capture --initial --directory . --output-file base.info
		
		# Run tests
		COMMAND /usr/bin/make -k ${_test_target}
		
		# Capturing lcov counters and generating report
		COMMAND ${LCOV_PATH} --ignore-errors source --capture --directory . --output-file test.info
		COMMAND ${LCOV_PATH} --add-tracefile base.info --add-tracefile test.info --output-file total.info
		COMMAND ${LCOV_PATH} --remove total.info '/usr/*' 'src/sqlite3.*' 'src/dlibspath.cpp' --output-file filtered.info
		COMMAND ${GENHTML_PATH} --sort --highlight --show-details --quiet --frames --legend --title "DLibs libraries" --output-directory=${_output_path} filtered.info
		COMMAND ${CMAKE_COMMAND} -E remove base.info test.info total.info filtered.info
		
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
	)
	
	# Show info where to find the report
	ADD_CUSTOM_COMMAND(TARGET ${_coverage_target} POST_BUILD
		COMMAND ;
		COMMENT "Open ./${_output_path}/index.html in your browser to view the coverage report."
	)

ENDFUNCTION(SETUP_TARGET_FOR_COVERAGE)
