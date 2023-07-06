#ifndef MATH_H
#define MATH_H

#include <math.h>


float rad(float angle){
	float radian = M_PI / 180 * angle;
	return radian;
}

float deg(float rad){
	float angle = 180 / M_PI * rad;
	return angle;
}


#endif