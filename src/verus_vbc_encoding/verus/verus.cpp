#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<chrono>

using namespace std;
using namespace chrono;

const string file_name = "../data.txt";
const string encode_name = "../encode.txt";
const string decode_name = "../decode.txt";
const int x = 11;
const uint32_t data_size[x] = {1000,10000,100000,200000,500000,800000,1000000,3000000,5000000,7000000,10000000};


//读取数据
vector<vector<uint32_t>> read_data(const string& file_name){
	vector<vector<uint32_t>> test_data;
	ifstream in;
	in.open(file_name, ios::in);
	if(!in){
		cout << "open failed" << endl;
		exit(1);
	}
	uint32_t capacity = 0;
	for(int i = 0; i < x; i++){
		capacity = data_size[i];
		vector<uint32_t> x_data;
		uint32_t number = 0;
		while((in >> number) && capacity > 0){
			x_data.push_back(number);
			capacity--;
		}
		test_data.push_back(x_data);
	}
	return test_data;
}



//GVE
//分组进行encode
string encode_single_group(const vector<uint32_t>& integers){	
	string encoded;	
	//该组的tag	
	char tags = 0;
	size_t offset = 6;
	//对于每一个数据进行encode
	for(int i = 0; i < integers.size(); i++){
		uint32_t number = integers[i];
		//每个数据有一个子标签count记录需要多少个Byte
		char count = 0x0;
		//为0则不需要取，直接添加至encoded
		if(number != 0){
			char current_byte = 0xFF;
			//当还有字节可以编码时：取出字节-》计数增加-》加入编码
			while(number != 0){
				current_byte = current_byte & number;
				count++;
				encoded += current_byte;
				number = number >> 8;
				current_byte = 0xFF;	
			}
			tags = tags | (count-1 << offset);
		}else{
			encoded += (char)0x00;
			tags = tags | (count << offset);	
		}
		offset -= 2;
	}
	return (tags + encoded);
}

//对未编码数组进行group_varint_encode
//return encoded string
string group_varint_encode(const vector<uint32_t> &original_integers){
	//为空返回空字符串	
	if(original_integers.empty()) return "";
	string encoded;
	//分组器
	int group_count = 0;
	vector<uint32_t> group;
	for(int i = 0; i < original_integers.size(); i++){
		group_count++;
		group.push_back(original_integers[i]);
		//若能填满四个数据则编码
		if((group_count & 3) == 0){
			encoded += encode_single_group(group);
			group_count = 0;
			group.clear();
		}
	}
	//若数据数量不为4的倍数则再单独编码
	if(group_count != 0) encoded += encode_single_group(group);
	return encoded;
}

uint32_t get_value(const string& encoded_byte_stream, const vector<uint32_t>& masks, size_t current_tag, uint32_t* address, int& index){
	uint32_t value = 0;	
	address = (uint32_t*)&encoded_byte_stream[index];
	value = *address & masks[current_tag];
	index += current_tag + 1;
	return value;

}

//decode操作，返回uint32_t的vector
vector<uint32_t> group_varint_decode(const string& encoded_byte_stream){
	if(encoded_byte_stream.empty()) return {};
	vector<uint32_t> decoded;	
	const int len = encoded_byte_stream.length();
	int index = 0;
	const vector<uint32_t> masks = {0xff, 0xffff, 0xffffff, 0xffffffff};
	while(index < len){
		//取当前tag
		char tags = encoded_byte_stream[index++];
		int number = (tags & 3) + ((tags >> 2) & 3) + ((tags >> 4) & 3) + ((tags >> 6) & 3) + 4;
		uint32_t* address = (uint32_t*)&encoded_byte_stream[index];
		size_t current_tag = (tags >> 6) & 3; 
		//最后一个		
		if((index + number) >= len){
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));
			if(index >= len) break;
			
			current_tag = (tags >> 4) & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));
			if(index >= len) break;

			current_tag = (tags >> 2) & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));
			if(index >= len) break;
		
			current_tag = tags & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));
			if(index >= len) break;

		}else{
					
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));

			current_tag = (tags >> 4) & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));

			current_tag = (tags >> 2) & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));

			current_tag = tags & 3;
			decoded.push_back(get_value(encoded_byte_stream,masks, current_tag, address, index));
		}
	}		
	return decoded;
}

//vbc
string encode_number(uint32_t n){
	char current_byte;
	string byte;
	while (1) {
		current_byte = n & 0x7f;
		byte = current_byte + byte;
		if (n < 128) break;
		n = n >> 7;
	}
	byte[byte.size()-1] += 128;
	//将每个char(8位)倒序放入string容器中
	return byte;
}

//将vector<uint32_t>整数流序列化
//返回string,string中每一个char代表一个Byte
string encode(const vector<uint32_t>& in_sequence){
	string serialized_integers;
	const int size = in_sequence.size();
	for (int i = 0; i < size; i++) {
		serialized_integers += encode_number(in_sequence[i]);
	}
	return serialized_integers;
}
//将序列化后的string解码为若干整数
//从高位向低位按字节处理,直到遇到某一Byte最高位为１，判定为一个整数
vector<uint32_t> decode(const string& serialized_integers){
	vector<uint32_t> numbers;
	uint32_t current_number = 0;
	int index = 0;
  while (index < serialized_integers.length()) {
		//用unsigned char而不是char
		//因为char(-128~128),unsigned char(0~255),与无符号整数相对应
		unsigned char current_byte = serialized_integers[index];
		uint32_t part = (uint32_t)current_byte;
		if (part < 128) {
			current_number = (current_number << 7) + part;
		}else {
			current_number = (current_number << 7) + (part - 128);
			numbers.push_back(current_number);
			current_number = 0;
		}
		index++;
	}
	return numbers;	
}

//encode
//size(number of data) vbc(MB/s) gve(MB/s)
bool encode_verus(const vector<vector<uint32_t>>& test_data, const string& encode_name, vector<string>& vbc, vector<string>& gve){
	ofstream out;
	out.open(encode_name, ios::out);
	out << "size(number) vbc(MB/s) gve(MB/s) vbc-gve(MB/s)" << endl;
	for(int i = 0; i < test_data.size(); i++){
		time_point<system_clock> start, end;
		//vbc
		string vbc_encoded;		
		start = system_clock::now();
		vbc_encoded = encode(test_data[i]);
		end = system_clock::now();
		float vbc_time = duration_cast<microseconds>(end - start).count();
		vbc.push_back(vbc_encoded);
		//gve
		string gve_encoded;		
		start = system_clock::now();
		gve_encoded = group_varint_encode(test_data[i]);
		end = system_clock::now();
		float gve_time = duration_cast<microseconds>(end - start).count();
		gve.push_back(gve_encoded);
		//写入
		uint64_t total = test_data[i].size();
		out << test_data[i].size() << " " << (4*total/vbc_time) << " " << (4*total/gve_time) << " " << (4*total/vbc_time) - (4*total/gve_time) << endl; 
	} 
	out.close();
}

bool decode_verus(const string& decode_name, const vector<string>& vbc, const vector<string>& gve){
	ofstream out;
	out.open(decode_name, ios::out);
	if(!out){
		cout << "open failed" << endl;
		return false;
	}
	out << "size(number) vbc(MB/s) gve(MB/s) vbc-gve(MB/s)" << endl;
	cout << vbc.size() << " " << gve.size() << endl;
	for(int i = 0; i < x; i++){
		time_point<system_clock> start, end;
		//vbc
		//cout << "vbc_size" << vbc[i].size() << endl;		
		start = system_clock::now();
		decode(vbc[i]);
		end = system_clock::now();
		float vbc_decode = duration_cast<microseconds>(end - start).count();
		
		//gve
		//cout << "gve_size" << gve[i].size() << endl;			
		start = system_clock::now();
		group_varint_decode(gve[i]);
		end = system_clock::now();
		float gve_decode = duration_cast<microseconds>(end - start).count();
		//处理uint32_t的数量
		uint64_t total = data_size[i];
		out << total << " " << (4*total/vbc_decode) << " " << (4*total/gve_decode) << " " << (4*total/vbc_decode) - (4*total/gve_decode) << endl;
	} 
	out.close();
	return true;
}

int main(){
	vector<vector<uint32_t>> test_data = read_data(file_name);
	vector<string> vbc;
	vector<string> gve;
	bool encode_success = encode_verus(test_data,encode_name,vbc,gve);
	bool decode_success = false;
	if(encode_success){
		decode_success = decode_verus(decode_name,vbc,gve);
	}
	if(decode_success){
		cout << "成功" << endl;	
	}
	return 0;
}






