file(GLOB SRCS *.cc)

ADD_EXECUTABLE(testomushnetwork ${SRCS})

TARGET_LINK_LIBRARIES(testomushnetwork
  libomushnetwork
  libgtest
  libgmock
)

add_test(NAME testomushnetwork
         COMMAND testomushnetwork)
