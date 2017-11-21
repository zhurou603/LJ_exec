#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

// Returns the sum of even elements in a Fibonacci sequence
// which contains length elements
//
// length is \in [0, 49]
// // For example:
//  get_even_sum_of_fibonacci_sequence(0) returns 0
//  get_even_sum_of_fibonacci_sequence(1) returns 0
//  get_even_sum_of_fibonacci_sequence(5) returns 2
//  get_even_sum_of_fibonacci_sequence(10) returns 44
//
// https://zh.wikipedia.org/wiki/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97
uint64_t get_even_sum_of_fibonacci_sequence(const size_t length) {
    // make your codes here
    return 0;
}

class FibEvenSumTester : public  ::testing::Test {
protected:
    virtual void SetUp() {
        std::ifstream ifs("fib.input");
        std::string line;
        while (std::getline(ifs, line)) {
            fib_sequence_.push_back(std::stoull(line));
        }
    }

    virtual void TearDown() {
        fib_sequence_.clear();
    }

protected:
    std::vector<uint64_t> fib_sequence_;
};

// 边界情况 : 实参为0
TEST_F(FibEvenSumTester, zero_length) {
    ASSERT_EQ(0, get_even_sum_of_fibonacci_sequence(0));
}

// 遍历正常情况
TEST_F(FibEvenSumTester, normal_cases) {
    size_t prev_even_sum = 0;
    for (size_t len = 1; len < 50; ++len) {
        const size_t your_ans = get_even_sum_of_fibonacci_sequence(len);
        const size_t correct_ans = (fib_sequence_[len-1] & 0x1) == 0 ? \
                                   (prev_even_sum + fib_sequence_[len-1]) : \
                                   prev_even_sum;
        prev_even_sum = correct_ans;
        ASSERT_EQ(correct_ans, your_ans) << "failed on length[" << len << "]";
        std::cout << correct_ans << std::endl;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

