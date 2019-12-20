#include"str_match.h"
#include<gtest/gtest.h>

int StrMatch::bruteforce_v1(const string& text){
	const int t_len = text.length();
	const int p_len = pattern_.length();
	int i = 0, j = 0;
	while(j < p_len && i < t_len){
		if(text[i] == pattern_[j]){
			i++;
			j++;
		}else{
			//退到这次匹配的开始的下一个字符
			i = i - j + 1;
			j = 0;
		}
	}
	if(p_len == j) return i-j;
	return -1;
}

int StrMatch::kmp(const string& text){
	//构造next表
	vector<int> next(build_next(pattern_));
	const int t_len = text.length();
	const int p_len = pattern_.length();
	int i = 0, j = 0;
	while(j < p_len && i < t_len){
		//特别要注意-1
		if(-1 == j || text[i] == pattern_[j]){
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
	if(p_len == j) return i-j;
	return -1;
}

//构造表
vector<int> StrMatch::build_next(const string& pattern){
	vector<int> next;
	const int len = pattern.length();
	next.resize(len);
	//自匹配主指针
	int i = 0;
	next[0] = -1;
	//自匹配模式指针
	int j = -1;
	while(j < len-1){
		if(j < 0 || pattern[i] == pattern[j]){
			i++;
			j++;
			next[i] = j;
		}else{
			//mismatch
			j = next[j];
		}
	}
	return next;
}

TEST(brute_force,case1){
	string text = "I am qlj who will be an engineer";
	StrMatch match("qlj");
	string answer1(text.substr(match.bruteforce_v1(text),3));
	string answer2(text.substr(match.kmp(text),3));
	ASSERT_EQ("qlj", answer1);
	ASSERT_EQ("qlj", answer2);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
