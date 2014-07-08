enable_testing()

find_path( CPPTEST_INCLUDE
           "cpptest.h"
           CMAKE_INCLUDE_PATH
         )

find_library(CPPTEST_LIBRARY NAMES cpptest)
include_directories (.
                     ${Dlibs_BINARY_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${CPPTEST_INCLUDE}
                    ) 
                    
add_executable(testdstring testdstring.cpp)

target_link_libraries(testdstring dlibs ${CPPTEST_LIBRARY})

add_test(testdstring ${CMAKE_CURRENT_BINARY_DIR}/testdstring)
