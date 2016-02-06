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


function(add_sources)
  get_property(is_defined GLOBAL PROPERTY SRCS_LIST DEFINED)
  if(NOT is_defined)
    define_property(GLOBAL PROPERTY SRCS_LIST
      BRIEF_DOCS "List of source files"
      FULL_DOCS "List of all source files in the entire project")
  endif()
  # make absolute paths
  set(SRCS)
  foreach(s IN LISTS ARGN)
    if(NOT IS_ABSOLUTE "${s}")
      get_filename_component(s "${s}" ABSOLUTE)
    endif()
    list(APPEND SRCS "${s}")
  endforeach()
  # append to global list
  set_property(GLOBAL APPEND PROPERTY SRCS_LIST "${SRCS}")
endfunction(add_sources)

set(header_directory "include/omushnetwork/")

file(GLOB sources "[a-zA-Z]*.cc")
file(GLOB_RECURSE public_headers "include/omushnetwork/[a-zA-Z]*.h")
file(GLOB private_headers "[a-zA-Z]*.h")

set(library_sources "")
add_sources(${library_sources})
	message(STATUS "sources: ${sources}")
set(libomushnetwork_SRCS
${sources}
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
