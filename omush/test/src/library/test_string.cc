/**
 * \file test_string.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "gtest/gtest.h"
#include "omush/library/string.h"

class LibraryStringTest : public testing::Test {
};

TEST_F(LibraryStringTest, iequals) {
using omush::library::string::iequals;
EXPECT_TRUE(iequals("test", "test"));
EXPECT_TRUE(iequals("teSt", "test"));
EXPECT_TRUE(iequals("test", "TEST"));
EXPECT_FALSE(iequals("test", "other"));
}
