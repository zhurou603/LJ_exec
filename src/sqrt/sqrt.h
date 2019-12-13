#include<stdint.h>

//set presision 10e-3
const float EPSINON = 0.001;

float my_sqrt(uint32_t value){
	float low = 0;
	float high = value;
	float mid = value;
	while((high - low) > EPSINON){
		mid = low + (high - low) / 2;
		//如果还未收敛，则二分
		if(mid*mid > value){
			high = mid;	
		}else{
			low = mid;
		}
	}
	return mid;
}
