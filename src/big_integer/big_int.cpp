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
