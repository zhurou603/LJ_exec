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

string read_file(const string& file_name){
	//打开文件,以只读权限打开	
	int fd = open(file_name.c_str(), O_RDONLY);
	if(-1 == fd){
		cout << "open file " << file_name << " failed" << endl;
		exit(1);
	}
	//读取文件
	ssize_t ret = 0;
	//get size
	struct stat st;
	if(fstat(fd, &st)){
		cout << "get information failed" << endl;
		exit(1);	
	}
	ssize_t len = st.st_size;
	//申请一块len+1长度空间(0,len-1)放文件，len放'\0'
	char* buf = (char*)malloc(sizeof(char)*(len+1));
	buf[len] = '\0';
	//保存指针，读取所有文件数据到file
	char* file = buf;
	while(len != 0 && (ret = read(fd, buf, len)) != 0){
		if(ret == -1){
			if(errno == EINTR){
				continue;			
			}
			perror("read");
			break;
		}
		len -= ret;
		buf += ret;
	}
	
	return file;
}

//完成分片和去重
set<string> slice(string& data){
	set<string> sliced_data;	
	string element;
	istringstream tokens(data);
	while(getline(tokens, element,'\n')){
		sliced_data.insert(element+"\n");
	}
	return sliced_data;
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
	for(auto it = sliced.begin(); it != sliced.end(); it++){
		len = write(fd, (*it).c_str(), (*it).length());
		if(len <= 0){
			cout << "write failed" << endl;
			exit(1);
		}
	}
	return fd;
}

int main(){
	string data = read_file(file_name);
	set<string> sliced = slice(data);
	write_file(sliced,write_name);
	return 0;
}

