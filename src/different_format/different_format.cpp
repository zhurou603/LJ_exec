#include<string>
#include<iostream>
#include<vector>

using namespace std;

//思路：一个loop:十六进制——》二进制——》十进制——》十六进制

string bin_to_dec(const string& bin){
	int result = 0;
	const int len = bin.length();
	for(int i = 1; i < len; i++){
		result = (result << 1) | (bin[i] - '0');
	}
	return to_string(result);
}

string hex_to_bin(const string& hex){
	vector<string> binary({"0000","0001","0010","0011","0100","0101","0110","0111",
		"1000","1001","1010","1011","1100","1101","1110","1111"});
	const int len = hex.length();
	string result("b");
	for(int i = 2; i < len; i++){
		if(hex[i] >= 65){
			result += binary[hex[i]-'A' + 10];
		}else{
			result += binary[hex[i]-'0'];
		}
	}
	return result;
}

string dec_to_hex(const string& dec){
	int result = 0;
	const int len = dec.length();
	for(int i = 0; i < len; i++){
		result = 10*result + (dec[i] - '0');
	}
	string hex;
	while(result){
		int current = result & 0xf;
		if(current < 10){
			hex = (char)('0' + current) + hex;
		}else{
			hex = (char)('A' + current-10) + hex;
		}
		result >>= 4;
	}
	return "0x" + hex;
}

void print_format(const string& number){
	string hex,dec,bin;	
	if('b' == number[0]){
		bin = number;
		dec = bin_to_dec(number);
		hex = dec_to_hex(dec);
	}
	else if(number.length() > 2 && '0' == number[0] && 'x' == number[1]){
		hex = number;
		bin = hex_to_bin(number);
		dec = bin_to_dec(bin);
	}else{
		dec = number;
		hex = dec_to_hex(number);
		bin = hex_to_bin(hex);
	}
	cout << hex << endl;
	cout << dec << endl;
	cout << bin << endl;
}

int main(){
	string input1 = "b01011001";
	string input2 = "465715";
	string input3 = "0x478AEF";
	print_format(input1);
	print_format(input2);
	print_format(input3);
	return 0;
}
