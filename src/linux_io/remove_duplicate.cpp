#include<set>
#include<unistd.h>
#include<string.h>
#include<string>
#include<iostream>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<vector>
#include<sstream>

using namespace std;

//要读取的文件
const string file_name= "file.txt";
const string write_name = "output.txt";
//每次读200Bytes
const size_t BUFFER_SIZE = 200;

//将文件以每次200Byte读入vector
vector<string> read_file(const string& file_name){
	//打开文件,以只读权限打开	
	int fd = open(file_name.c_str(), O_RDONLY);
	if(fd == -1){
		cout << "open file " << file_name << " failed" << endl;
		exit(1);
	}
	//读取文件
	//length为200或小于200的字符串
	vector<string> data;
	char buf[BUFFER_SIZE];
	memset(buf,0,sizeof(buf));
	ssize_t ret = 0;
	while(ret = read(fd, buf, BUFFER_SIZE) != 0){
		if(ret == -1){
			cout << "出错" << endl;
			perror("read");
			break;
		}
		data.push_back(buf);
		memset(buf,0,sizeof(buf));
	}
	return data;
}

//完成分片和去重
set<string> slice(vector<string>& data){
	vector<string> sliced_data;	
	string element;
	const size_t size = data.size();
	for(size_t i = 0; i < size; i++){
		istringstream tokens(data[i]);
		while(getline(tokens, element)){
			sliced_data.push_back(element);
		}
		//如果最后一个元素不是完整一行，则加入下一次读的数据
		//特别的，最后一次读入的数据最后一个元素一定是完整的一行,所以不会越界
		if(data[i][data[i].size()-1] != '\n'){
			data[i+1] = *sliced_data.end() + data[i+1];
			sliced_data.pop_back();
		}
	}
	set<string> unique{sliced_data.begin(), sliced_data.end()};
	return unique;
}

//将结果写入文件
int write_file(const set<string>& sliced, const string& file_name){
	//以只可写若不存在则新建，存在则清空的方式打开
	int fd = open(file_name.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if(fd == -1){
		cout << "open failed" << endl;
		exit(1);
	}
	//遍历每行不重复的内容
	ssize_t len = 0;
	set<string>::iterator it;
	for(it = sliced.begin(); it != sliced.end(); it++){
		len = write(fd, (*it).c_str(), (*it).length());
		write(fd,"\n",1);
		if(len < 0){
			cout << "wrong" << endl;			
			break;
		}
	}
	return fd;
}

int main(){
	vector<string> data = read_file(file_name);
	set<string> sliced = slice(data);
	write_file(sliced,write_name);
	return 0;
}

