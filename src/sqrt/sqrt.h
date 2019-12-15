#include<stdint.h>
#include<iostream>

using namespace std;
//set presision 10e-3
const float EPSINON = 0.001;


// float my_sqrt(uint32_t value){
// 	float low = 0;
// 	float high = value;
// 	float mid = value;
// 	while((high - low) > EPSINON){
// 		mid = low + (high - low) / 2;
// 		//如果还未收敛，则二分
// 		if(mid*mid > value){
// 			high = mid;	
// 		}else{
// 			low = mid;
// 		}
// 	}
// 	return mid;
// }

float my_sqrt(uint32_t value){
  //转化为单精度浮点
  float f_val = (float)value;
  //牛顿迭代参数
  float xhalf = 0.5f*f_val;
  float y = f_val;
  //将浮点转化为整型,便于右移1位（除2）
  long i = *(long*)&y;
  //初值估计
  i = 0x5f3759df - (i >> 1);
  //转回浮点
  y = *(float*)&i;
  //两次牛顿迭代提升精度
  y = y*(1.5f - (xhalf*y*y));
  y = y*(1.5f - (xhalf*y*y));
  //y为平方根倒数，所以返回f_val*y为平方根
  return f_val*y;
}