#ifndef GROUP_VARINT_ENCODE_H
#include<vector>
#include<string>

using namespace std;

string encode_single_group(const vector<uint32_t>& integers);

//encode接口
string group_varint_encode(const vector<uint32_t> &original_integers);

//decode接口
vector<uint32_t> group_varint_decode(const string& encoded_byte_stream);
#endif
