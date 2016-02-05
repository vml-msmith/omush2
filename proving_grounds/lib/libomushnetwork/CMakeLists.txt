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

set(libomushnetwork_SRCS
    server.cc
    websocketserver.cc
    networkmanager.cc
)

# Declare the library
add_library(libomushnetwork STATIC
    ${libomushnetwork_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libomushnetwork PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
