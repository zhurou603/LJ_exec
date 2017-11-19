#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

// Returns a vector of prime numbers
// It takes a maximal value as input parameter, indicating
// the maximum value may be contained in the returned vector.
//
// value_not_exceeded is less than 100001
//
// For example:
//  get_prime_numbers(6) returns {2, 3, 5}
//  get_prime_numbers(0) returns an empty vector
std::vector<uint32_t> get_prime_numbers(const uint32_t less_than_value) {
    // make your codes here
    return std::vector<uint32_t>();
}

class PrimeTester : public ::testing::Test {
protected:
    virtual void SetUp() {
        std::ifstream ifs("primes.input", std::ifstream::in);
        std::string line;
        while (std::getline(ifs, line)) {
            all_prime_numbers_.push_back(std::stoull(line));
        }
    }
    virtual void TearDown() {
        // do nothing
    }
    static void SetUpTestCase() {
        // do nothing
    }
    static void TearDownTestCase() {
        // do nothing
    }

protected:
    std::vector<uint32_t> all_prime_numbers_;
};

TEST_F(PrimeTester, below_a_certain_value) {
    std::vector<uint32_t> less_than_value_vec{0, 1, 2, 3, 6, 10, 20, 30, 50, 100};
    for (uint32_t less_than_value = 101; less_than_value < 100000; less_than_value += 500) {
        less_than_value_vec.push_back(less_than_value);
    }

    auto get_correct_result = [this](const uint32_t less_than_value) -> std::vector<uint32_t> {
        std::vector<uint32_t> res;
        for (size_t idx = 0; idx < all_prime_numbers_.size(); ++idx) {
            if (all_prime_numbers_[idx] < less_than_value) {
                res.push_back(all_prime_numbers_[idx]);
            } else {
                break;
            }
        }
        return res;
    };

    for (size_t idx = 0; idx < less_than_value_vec.size(); ++idx) {
        const uint32_t& less_than_value = less_than_value_vec[idx];
        std::vector<uint32_t> candidate_vec = get_prime_numbers(less_than_value);
        std::vector<uint32_t> correct_vec = get_correct_result(less_than_value);

        ASSERT_EQ(candidate_vec.size(), correct_vec.size()) <<
            "RESULT SIZE NOT MATCH; candidate[" << candidate_vec.size() <<
            "] correct[" << correct_vec.size() << "] less_than_value[" <<
            less_than_value << "]";
        for (size_t ans_idx = 0; ans_idx < correct_vec.size(); ++ans_idx) {
            ASSERT_EQ(candidate_vec[ans_idx], correct_vec[ans_idx]) <<
                "RESULT_IDX[" << ans_idx << "] NOT MATCH; candidate[" <<
                candidate_vec[ans_idx] << "] correct[" <<
                correct_vec[ans_idx] << "] less_than_value[" <<
                less_than_value << "]";
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

