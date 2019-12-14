#include"big_int.h"

//获取BigInt的字符串数据
string BigInt::get_val() const{	
	return val_;
}


//大整数相加
BigInt BigInt::operator +(const BigInt& b) const{
	string val2(b.get_val());
	int i = val_.length() - 1;
	int j = val2.length() - 1;
	//empty case
	if(-1 == i && -1 == j) return BigInt();
	//carry为进位，tmp为个位相加结果(0~19)
	int carry = 0, tmp = 0;
	string result;
	while(0 <= i || 0 <= j){
		tmp = carry;
		tmp += (0 <= i) ? val_[i]-'0' : 0;
		tmp += (0 <= j) ? val2[j]-'0' : 0;
		carry = tmp / 10;
		result += ('0' + tmp % 10);
		i--;
		j--;
	}
	//如果最高位有进位
	if(carry) result += '1';
	//"1234" + "4562" = "5796"(reverse "6975")
	reverse(result.begin(), result.end());
	return BigInt(result);
}

//大整数相乘
BigInt BigInt::operator *(const BigInt& b) const{
	string val2(b.get_val());
	const int len1 = val_.length();
	const int	len2 = val2.length();
	string result(len1+len2, '0');
	int tmp = 0;
	//竖式乘法
	for(int i = len1-1; i >= 0; i--){
		for(int j = len2-1; j >= 0; j--){
			//取进位
			tmp = result[i+j+1] - '0';
			//乘法
			tmp += (val_[i] - '0')*(val2[j] - '0');
			//update
			result[i+j+1] = (tmp % 10) + '0';
			result[i+j] += tmp / 10;
		}
	}
	//取出非0part
	for(int i = 0; i < result.length(); i++){
		if('0' != result[i]) return BigInt(result.substr(i));
	}
	return BigInt("0");
}
