#ifndef BIGINT_H
#define BIGINT_H

#include<string>
#include<algorithm>

using namespace std;

//BigInt以字符串表示数据,数据长度不限
//重载加法："1234" + "4562" = "5796"，返回一个BigInt对象，其值为相加结果
class BigInt{
 public:
	BigInt() {};	
	BigInt(const string& value) : val_(value) {}
	BigInt operator +(const BigInt& b) const;
	BigInt operator *(const BigInt& b) const;	
	string get_val() const;
 private:
	string val_;
};

#endif
