# This adds another subdirectory, which has 'project(gtest)'.
# add_subdirectory(vendors/gtest-1.7.0)
add_subdirectory(vendors/gmock-1.7.0)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

##############
# Unit Tests
##############
SET( PROJ_TEST_SOURCES    "" )
FILE( GLOB_RECURSE PROJ_TEST_SOURCES src/*.cc )
add_executable(runUnitTests ${PROJ_TEST_SOURCES})

target_link_libraries(runUnitTests gtest gtest_main gmock)
target_link_libraries(runUnitTests  ${PROJ_LIBRARIES} )
