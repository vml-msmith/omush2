CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

SET( PROJ_NAME       "omush" )
SET( PROJ_PATH       ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH   ${CMAKE_BINARY_DIR} )
SET( PROJ_SOURCES    "" )
SET( PROJ_HEADERS    "" )
SET( PROJ_INCLUDES   "hdrs" "vendor" "lib" )
SET( CMAKE_C_FLAGS "Test")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -ggdb -fprofile-arcs -ftest-coverage" )
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FALGS}")
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")
message(STATUS "Here: ${CMAKE_CXX_FLAGS}")
SET( PROJ_MAIN       "main.cc" )

FILE( GLOB_RECURSE PROJ_SOURCES src/*.cc )
FILE( GLOB_RECURSE PROJ_HEADERS hdrs/${PROJ_NAME}/*.h )

PROJECT( ${PROJ_NAME} )

FIND_PACKAGE( Boost 1.55 COMPONENTS system filesystem serialization thread  regex REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${SQLITE3_INCLUDE_DIR})
SET( PROJ_LIBRARIES  ${Boost_LIBRARIES} ${SQLITE3_LIBRARY} )

INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

ADD_LIBRARY( ${PROJ_NAME}_lib ${PROJ_SOURCES} )

ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_MAIN} )

SET( PROJ_LIBRARIES ${PROJ_NAME}_lib ${Boost_LIBRARIES} ${SQLITE3_LIBRARY} )


TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${PROJ_LIBRARIES} )

message(STATUS "Here: ${CMAKE_CXX_FLAGS}")
################################
# Testing
################################
if (true)
   add_subdirectory(test)
endif()
