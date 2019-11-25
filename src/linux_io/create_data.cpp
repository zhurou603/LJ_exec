#include<random>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

using namespace std;

//每行不超过k个,有line行
const size_t k = 4;
const size_t line = 500;
const char* file_name = "file.txt";

//返回生成文件的句柄fd 
int create_file(const char* file_name){
	//create a new file,owner可以对其读写
	int fd = creat(file_name, 0644);
	if(fd == -1){
		cout << "create file failed" << endl;
		return fd;
	}
	//生成随机字符
	default_random_engine random;
	uniform_int_distribution<unsigned> char_range(97,122);
	//每行[2,k]个
	uniform_int_distribution<unsigned> number_range(2,k);
	for(size_t i = 0; i < line; i++){
		int number = number_range(random);
		string content = "\n";
		for(int i = 0; i < number; i++){
			content = (char)char_range(random) + content;
		}
		//写入文件
		ssize_t success_test2 = 0;
		success_test2 = write(fd, content.c_str(), content.length());
		if(success_test2 == -1){
			cout << "write failed, may partial write or failed" << endl;
		}
	}
	close(fd);
	return fd;
}

int main(){
	int file = create_file(file_name);	
	return 0;
}
