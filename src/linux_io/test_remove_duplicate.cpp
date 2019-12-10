#include<gtest/gtest.h>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

using namespace std;

const string test = "output.txt";
const string test_answer = "test_result.txt";

vector<string> read_and_sort(const string& file_name){
	vector<string> content;
	ifstream in;
	in.open(file_name, ios::in);
	if(!in){
		cout << "open failed" << endl;	
		exit(1);
	}
	string line;
	while(in >> line){
		content.push_back(line);
	}
	sort(content.begin(),content.end());
	return content;
}

TEST(remove_duplicate,compare_content){
	vector<string> test_content = read_and_sort(test);
	vector<string> answer = read_and_sort(test_answer);
	ASSERT_EQ(test_content, answer);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
