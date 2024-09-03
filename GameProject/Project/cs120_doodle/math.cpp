/*
  math.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "math.hpp"

// return the value in radians
double toRadians(double angle_degree) {
	return angle_degree * PI / 180.0f;
}

// return the value in degree
double toDegrees(double angle_radians) {
	return angle_radians * 180.0f / PI;
}

// return the length
double getLength2D(const double& x1, const double& y1, const double& x2, const double& y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// returns the absolute value
float absolute(const float& value)
{
    if (value < 0)
        return -value;
    return value;
}