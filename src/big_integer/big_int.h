#ifndef BIGINT_H
#define BIGINT_H

#include<string>
#include<algorithm>

using namespace std;

//BigInt以字符串表示数据,数据长度不限
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
