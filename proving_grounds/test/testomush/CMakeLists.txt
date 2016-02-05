file(GLOB SRCS *.cc)

ADD_EXECUTABLE(testomush ${SRCS})
INSTALL(TARGETS testomush DESTINATION ${CMAKE_BINARY_DIR}/tests)

TARGET_LINK_LIBRARIES(testomush
  omush_lib
  libgtest
  libgmock
)

add_test(NAME testomush
         COMMAND testomush)