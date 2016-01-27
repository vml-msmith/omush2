CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )
SET( PROJ_NAME       "omush" )
SET( PROJ_PATH       ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH   ${CMAKE_BINARY_DIR} )
SET( PROJ_SOURCES    "" )
SET( PROJ_INCLUDES   "hdrs" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -D_WEBSOCKETPP_CPP11_STL_ -ggdb" )
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FALGS}")
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")

SET( PROJ_MAIN       "src/main.cc" )

FILE( GLOB_RECURSE PROJ_SOURCES src/*.cc )
FILE( GLOB_RECURSE PROJ_HEADERS hdrs/${PROJ_NAME}/*.h )
SET( PROJ_HEADERS "${PROJ_HEADERS}")

PROJECT( ${PROJ_NAME} )


## Add Libraries
add_subdirectory(lib)

## Add the C++11 flags for the compiler.
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


#set(Boost_USE_STATIC_LIBS        ON) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
#FIND_PACKAGE( Boost 1.55 COMPONENTS system filesystem serialization thread regex REQUIRED)

#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#SET( PROJ_LIBRARIES  "${Boost_LIBRARIES}" )
#INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

ADD_LIBRARY( ${PROJ_NAME}_lib ${PROJ_SOURCES} )
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_MAIN} )

SET( PROJ_LIBRARIES ${PROJ_NAME}_lib ${Boost_LIBRARIES} )


TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${PROJ_LIBRARIES} )


# Testing.
enable_testing()
add_subdirectory(test)
add_subdirectory(src)