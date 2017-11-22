#include <sys/time.h>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include "gtest/gtest.h"

// Return the intersection of two ordered (ascending) int sequences
//  There is not any duplicated element in each input sequence
//  The returned vector should be in ascending order
//
//  intersection({1, 3, 5, 9}, {0, 3, 5, 10, 11}) returns {3, 5}
std::vector<uint64_t> intersection(const std::vector<uint64_t>& sequence_1,
                                   const std::vector<uint64_t>& sequence_2) {
    // make your codes here
    return std::vector<uint64_t>();
}

class IntersectionTester : public ::testing::Test {
};

TEST_F(IntersectionTester, empty_input) {
    std::vector<uint64_t> res_vec = intersection(
        std::vector<uint64_t>(), {1,5,7});
    ASSERT_EQ(0, res_vec.size()) << "You should give me empty result";
}

TEST_F(IntersectionTester, empty_intersection) {
    std::vector<uint64_t> res_vec = intersection(
        {1, 3, 5, 7, 9}, {2, 4, 6, 8, 10});
    ASSERT_EQ(0, res_vec.size()) << "You should give me empty result";
}

TEST_F(IntersectionTester, performance) {
    for (size_t input_length : std::vector<size_t>({1024, 102400, 10240000})) {
        std::cerr << "preparing input data with length [" <<
            input_length << "]..." << std::endl;
        std::default_random_engine rng(
            std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist(0, input_length * 10);

        // 随机生成两个大数组
        std::array<std::vector<uint64_t>, 2> double_vectors;
        for (size_t vec_idx = 0; vec_idx < 2; ++vec_idx) {
            // 填充随机数
            std::vector<uint64_t>& current_vec = double_vectors[vec_idx];
            current_vec.reserve(input_length); // 预留空间, 避免多次自动倍增
            for (size_t ele_idx = 0; ele_idx < input_length; ++ele_idx) {
                current_vec.push_back(dist(rng));
            }

            // 排序
            std::sort(current_vec.begin(), current_vec.end());

            // unique
            std::vector<uint64_t>::iterator new_end = std::unique(current_vec.begin(),
                                                                  current_vec.end());
            current_vec.resize(std::distance(current_vec.begin(), new_end));
        }

        // 调用你的实现
        std::cerr << "running your application..." << std::endl;
        struct timeval start_ts, finish_ts;
        gettimeofday(&start_ts, NULL);
        std::vector<uint64_t> res_vec = intersection(double_vectors[0],
                                                     double_vectors[1]);
        gettimeofday(&finish_ts, NULL);
        std::cerr << "Your application costs [" <<
            (finish_ts.tv_usec - start_ts.tv_usec) + 1000000 * (finish_ts.tv_sec - start_ts.tv_sec) <<
            "] microseconds under length[" << double_vectors[0].size() <<
            " vs " << double_vectors[1].size() << "]" << std::endl;

        // 获得正确答案
        std::cerr << "calculating correct ans..." << std::endl;
        std::vector<uint64_t> correct_vec(double_vectors[0].size());
        std::vector<uint64_t>::iterator new_end = std::set_intersection(
            double_vectors[0].begin(), double_vectors[0].end(),
            double_vectors[1].begin(), double_vectors[1].end(),
            correct_vec.begin());
        correct_vec.resize(std::distance(correct_vec.begin(), new_end));

        // 验证答案
        std::cerr << "checking your ans..." << std::endl;
        ASSERT_EQ(correct_vec.size(), res_vec.size()) << "intersection size not correct";
        for (size_t ele_idx = 0; ele_idx < correct_vec.size(); ++ele_idx) {
            ASSERT_EQ(correct_vec[ele_idx], res_vec[ele_idx]) << "particular element not correct";
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

