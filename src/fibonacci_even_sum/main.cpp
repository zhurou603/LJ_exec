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
    if(length <= 2){
        return 0ull;
    }
    else{
        uint64_t even_sum = 0; 
        std::vector<uint64_t> f_s(length);
        f_s[0] = 0;
        f_s[1] = 1;
        for(uint64_t i = 2; i < length; ++i){
            f_s[i] = f_s[i-1] + f_s[i-2];
        }
        for(uint64_t j = 0; j < length; ++j){
            if(f_s[j] % 2 == 0){
                even_sum += f_s[j];
            }
        }
        return even_sum;
    }
}

uint64_t wakensky_get_even_sum_of_fibonacci_sequence(const size_t length) {
    if (length <= 2) {
        return 0;
    }

    uint64_t first = 0;
    uint64_t second = 1;
    uint64_t even_sum = 0;
    for (size_t i = 3; i <= length; ++i) {
        uint64_t new_second = first + second;
        first = second;
        second = new_second;

        // 判断偶数
        if ((second & 0x1) == 0) {
            even_sum += second;
        }
    }
    return even_sum;
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
    ASSERT_EQ(0ull, get_even_sum_of_fibonacci_sequence(0));
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

