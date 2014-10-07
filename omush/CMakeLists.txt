CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

SET( PROJ_NAME       "omush" )
SET( PROJ_PATH       ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH   ${CMAKE_BINARY_DIR} )
SET( PROJ_SOURCES    "" )
SET( PROJ_HEADERS    "" )
SET( PROJ_INCLUDES   "hdrs" "vendor" "lib" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -ggdb -fprofile-arcs -ftest-coverage" )
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage --verbose")
SET( PROJ_MAIN       "main.cc" )
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.
Please use a different C++ compiler.")
endif()

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


################################
# Testing
################################
if (true)
   add_subdirectory(test)
endif()
