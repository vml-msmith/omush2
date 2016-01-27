file(GLOB SRCS *.cc)

ADD_EXECUTABLE(testomushnetwork ${SRCS})
INSTALL(TARGETS testomushnetwork DESTINATION ${CMAKE_BINARY_DIR}/tests)

TARGET_LINK_LIBRARIES(testomushnetwork
  libomushnetwork
  libgtest
  libgmock
)

add_test(NAME testomushnetwork
         COMMAND testomushnetwork)
