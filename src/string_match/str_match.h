#ifndef STR_MATCH_H
#define STR_MATCH_H

#include<vector>
#include<string>

using namespace std;

//字符串匹配算法类
//brute force算法两个版本：v1,v2
//基于brute force:推演KMP,BM
class StrMatch{
 public:
	StrMatch(const string& p) : pattern_(p) {};
	void set_pattern(const string& pattern){
		pattern_ = pattern;
	}
	//暴力法
	int bruteforce_v1(const string& text);
	//KMP
	int kmp(const string& text);

 private:
	vector<int> build_next(const string& pattern);
	string pattern_;
};

#endif
