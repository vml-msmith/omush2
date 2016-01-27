set(libomushnetwork_SRCS
    server.h
    server.cc
    websocketserver.cc
    websocketserver.h
    isocketserver.h
    iserver.h
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