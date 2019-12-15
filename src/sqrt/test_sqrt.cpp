#include"sqrt.h"
#include<gtest/gtest.h>
#include<algorithm>
#include<random>
#include<math.h>

using namespace std;

TEST(my_sqrt, compare_with_stl){
	default_random_engine random;
	uniform_real_distribution<> range(0,10000);
	uint32_t number = 0;
	for(int i = 0; i < 10; i++){
		number = range(random);
		//与math库sqrt函数进行精度比较
		ASSERT_EQ(fabs(sqrt(number) - my_sqrt(number)) <= EPSINON, true);
	}
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
