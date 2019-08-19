#ifndef FILE_SORT_H
#define FILE_SORT_H
#include"file_sort.h"
#endif

#ifndef GTEST_H
#define GTEST_H
#include<gtest/gtest.h>
#endif

TEST(create, try_to_create){
	string file = "test.txt";
	ASSERT_EQ(create(file), true) << "create an file failed";
}

TEST(create_ten_file, try_ten_file){
	ASSERT_EQ(create_ten_file(), true);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
