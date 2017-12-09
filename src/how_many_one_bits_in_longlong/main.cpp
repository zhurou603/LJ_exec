#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "gtest/gtest.h"

// 返回一个64位整数中, 为1的bit个数
//
// get_count_of_one_bits(0) returns 0
// get_count_of_one_bits(4) returns 1
// get_count_of_one_bits(123456789) returns 16
size_t get_count_of_one_bits(const uint64_t integer) {
    // make your codes here
    uint64_t i = integer;
    i = (i & 0x5555555555555555) + ((i >> 1) & 0x5555555555555555);
    i = (i & 0x3333333333333333) + ((i >> 2) & 0x3333333333333333);
    i = (i & 0xf0f0f0f0f0f0f0f) + ((i >> 4) & 0xf0f0f0f0f0f0f0f);
    i = (i & 0xff00ff00ff00ff) + ((i >> 8) & 0xff00ff00ff00ff);
    i = i + (i >> 16);
    i = i + (i >> 32);
    size_t p = i & 0x000000000000007f;
    return p;

}

TEST(count_1_bits, count_1_bits) {
    ASSERT_EQ(0ull, get_count_of_one_bits(0));
    ASSERT_EQ(1ull, get_count_of_one_bits(4));
    ASSERT_EQ(16ull, get_count_of_one_bits(123456789));
    ASSERT_EQ(64ull, get_count_of_one_bits(std::numeric_limits<uint64_t>::max()));
    ASSERT_EQ(63ull,
              get_count_of_one_bits(std::numeric_limits<uint64_t>::max() & 0xFFFFFFFFFFFFFFFE));

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

