#include <iostream>
#include <string>
#include "gtest/gtest.h"

// Returns literal expression for the input integer
//
// longlong_to_str(1234) returns "1234"
std::string longlong_to_str(const uint64_t integer) {
    // make your codes here
    return "";
}

// Returns longlong for the input string
//   the input string follows these rules:
//      - contains only decimal numbers
//      - will not be empty
//      - will not exceeds the range of uint64_t
//
//  str_to_longlong("1234") returns 1234
//  str_to_longlong("001234") returns 1234
uint64_t str_to_longlong(const std::string& str) {
    return 0;
}

TEST(longlong_to_str, small) {
    ASSERT_EQ(std::string("1"), longlong_to_str(1));
    ASSERT_EQ(std::string("22"), longlong_to_str(22));
    ASSERT_EQ(std::string("996"), longlong_to_str(996));
    ASSERT_EQ(std::string("9094"), longlong_to_str(9094));
}

TEST(longlong_to_str, large) {
    ASSERT_EQ(std::string("3278965691"), longlong_to_str(3278965691));
    ASSERT_EQ(std::string("9754946231790"), longlong_to_str(9754946231790));
}

TEST(str_to_longlong, small) {
    ASSERT_EQ(1, str_to_longlong("1"));
    ASSERT_EQ(1, str_to_longlong("01"));
    ASSERT_EQ(901, str_to_longlong("901"));
}

TEST(str_to_longlong, large) {
    ASSERT_EQ(3278965691, str_to_longlong("3278965691"));
    ASSERT_EQ(9754946231790, str_to_longlong("9754946231790"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

