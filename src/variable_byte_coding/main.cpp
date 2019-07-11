#include <iostream>
#include <vector>
#include "gtest/gtest.h"

/*
 * 整数压缩 (variable bytes conding)
 * 对于32bit整数，如果其值较小，占不满所有bits (高位为0)
 * 鉴于这个特点，我们可以对整数进行压缩
 * https://nlp.stanford.edu/IR-book/html/htmledition/variable-byte-codes-1.html
 * Vint压缩策略是，
 *  用每个字节的最高位做标志位，后7位为有效数据位，
 *  如果标志位为0，则说明后一个字节和当前字节隶属于同一个uint32
 *  为1说明这是当前整数的最后一个字节
 *
 *  例如 : 8985的二进制表达是 00100011 00011001  (我们只考虑uint32_t)
 *      如果表达为uint32_t, 需要占用4个字节
 *      而实际上, 最高位1处于第 13 bit (从第0bit开始算，右侧是低位)
 *      更高的18bit全部为0
 *
 *      如果表达为vint，需要占用2个字节，达到50%的压缩率
 *      output vec[0] 包含 高7bit : 01000110
 *      output vec[1] 包含 低7bit : 10011001
 *      这两个Bytes的最高位都是flag, 低7bit才是有效载荷
 */

/* 
 * 输入 {824, 5, 214577}
 * 输出的二进制表达是 {00000110, 10111000, 10000101, 00001101, 00001100, 10110001}
 * 实际输出的vector是 {6, 184, 133, 13, 12, 177}
 * 这样， 原本需要占用 12 个字节的三个整数，被压缩为6个字节，压缩率是50%
 */
std::vector<unsigned char> compress(const std::vector<uint32_t>& raw_integers) {
    // make your codes here
    return std::vector<unsigned char>();
}

// compress的反函数
// 输入压缩后的字符串 (密文)
// 输出原始整数数组 (明文)
std::vector<uint32_t> decompress(const std::vector<unsigned char>& compressed_integers) {
    // make your codes here
    return std::vector<uint32_t>();
}

TEST(VBC_TESTER, case1) {
    std::vector<unsigned char> compressed_vec = compress(std::vector<uint32_t>(8985));
    std::vector<unsigned char> ans_vec = {70, 153};

    ASSERT_EQ(ans_vec.size(), compressed_vec.size());
    for (size_t idx = 0; idx < compressed_vec.size(); ++idx) {
        ASSERT_EQ(ans_vec[idx], compressed_vec[idx]) <<
            "You get wrong byte at index[" << idx << "]";
    }
}

TEST(VBC_TESTER, case2) {
    std::vector<unsigned char> compressed_vec = compress(
        std::vector<uint32_t>({824, 5, 214577}));
    std::vector<unsigned char> ans_vec = {6, 184, 133, 13, 12, 177};

    ASSERT_EQ(ans_vec.size(), compressed_vec.size());
    for (size_t idx = 0; idx < compressed_vec.size(); ++idx) {
        ASSERT_EQ(ans_vec[idx], compressed_vec[idx]) <<
            "You get wrong byte at index[" << idx << "]";
    }
}

TEST(VBD_TESTER, case1) {
    std::vector<uint32_t> decompressed_vec = decompress(std::vector<unsigned char>({70, 153}));
    std::vector<uint32_t> ans_vec = {8985};

    ASSERT_EQ(ans_vec.size(), decompressed_vec.size());
    for (size_t idx = 0; idx < decompressed_vec.size(); ++idx) {
        ASSERT_EQ(ans_vec[idx], decompressed_vec[idx]) <<
            "You get wrong integer at index[" << idx << "]";
    }
}

TEST(VBD_TESTER, case2) {
    std::vector<uint32_t> decompressed_vec = decompress(std::vector<unsigned char>(
        {6, 184, 133, 13, 12, 177}));
    std::vector<uint32_t> ans_vec = {824, 5, 214577};

    ASSERT_EQ(ans_vec.size(), decompressed_vec.size());
    for (size_t idx = 0; idx < decompressed_vec.size(); ++idx) {
        ASSERT_EQ(ans_vec[idx], decompressed_vec[idx]) <<
            "You get wrong integer at index[" << idx << "]";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

