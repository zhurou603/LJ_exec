#include"file_sort.h"

#include<gtest/gtest.h>


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
