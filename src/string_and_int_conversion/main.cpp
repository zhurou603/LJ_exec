#include <iostream>
#include <string>
#include "gtest/gtest.h"

// Returns literal expression for the input integer
//
// longlong_to_str(1234) returns "1234"
std::string longlong_to_str(const uint64_t integer) {
    // make your codes here
    std::string str;
    std::string str_rev;
    std::string num[10] = {"0","1","2","3","4","5","6","7","8","9"};
    uint64_t k = 0;
    for(uint64_t i = 1; i <= integer; i *= 10){
        k = (integer/i) % 10;
        str_rev += num[k];
    }
    uint64_t len = str_rev.length();
    for(size_t i = 0; i < len; ++i){
        str += str_rev[len - (i+1)];
    }
    return str;
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
    const char *p = str.c_str();
    uint64_t ll = 0;
    while(*p == '0'){
        ++p;
    }
    while(p){
        ll = ll * 10 + ((uint64_t)(*p) - 48);
        ++p;
    }
    return ll;
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
    ASSERT_EQ(1ull, str_to_longlong("1"));
    ASSERT_EQ(1ull, str_to_longlong("01"));
    ASSERT_EQ(901ull, str_to_longlong("901"));
}

TEST(str_to_longlong, large) {
    ASSERT_EQ(3278965691ull, str_to_longlong("3278965691"));
    ASSERT_EQ(9754946231790ull, str_to_longlong("9754946231790"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

