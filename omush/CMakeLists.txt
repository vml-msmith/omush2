CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

SET( PROJ_NAME       "omush" )
SET( PROJ_PATH       ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH   ${CMAKE_BINARY_DIR} )
SET( PROJ_SOURCES    "" )
SET( PROJ_HEADERS    "vendor/SQLiteCpp" )
SET( PROJ_INCLUDES   "hdrs" "vendor" "lib" "vendor/SQLiteCpp/include")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -ggdb" )
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FALGS}")
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")

SET( PROJ_MAIN       "main.cc" )

FILE( GLOB_RECURSE PROJ_SOURCES src/*.cc )
FILE( GLOB_RECURSE PROJ_HEADERS hdrs/${PROJ_NAME}/*.h )
SET( PROJ_HEADERS "${PROJ_HEADERS}")

message("system: ${CMAKE_SYSTEM_PREFIX_PATH}")

PROJECT( ${PROJ_NAME} )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
FIND_PACKAGE( Boost COMPONENTS system filesystem serialization thread regex REQUIRED)

IF (Boost_FOUND)
  message(STATUS "Found boost")
ENDIF()


FIND_PATH(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)

# Look for the library.
FIND_LIBRARY(SQLITE3_LIBRARY NAMES sqlite3)

# Handle the QUIETLY and REQUIRED arguments and set SQLITE3_FOUND to TRUE if all
# listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SQLITE3 DEFAULT_MSG SQLITE3_LIBRARY
SQLITE3_INCLUDE_DIR)

#copy the results to the output variables.
IF(SQLITE3_FOUND)
  SET(SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})
  SET(SQLITE3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})
ELSE(SQLITE3_FOUND)
  SET(SQLITE3_LIBRARIES)
  SET(SQLITE3_INCLUDE_DIRS)
ENDIF(SQLITE3_FOUND)


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${SQLITE3_INCLUDE_DIR})
SET( PROJ_LIBRARIES  "${Boost_LIBRARIES} ${SQLITE3_LIBRARY} SQLiteCpp" )
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

ADD_LIBRARY( ${PROJ_NAME}_lib ${PROJ_SOURCES} )
ADD_SUBDIRECTORY("vendor/SQLiteCpp")
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_MAIN} )

SET( PROJ_LIBRARIES ${PROJ_NAME}_lib ${Boost_LIBRARIES} ${SQLITE3_LIBRARY} SQLiteCpp)


TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${PROJ_LIBRARIES} )

################################
# Testing
################################
if (true)
   add_subdirectory(test)
endif()
