/*
  math.hpp

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee 
 Byeongjun Kim wrote this all
 Sangjin Lee 

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include <string>

constexpr double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781;

#include <vector>

double toRadians(double angle_degree);
double toDegrees(double angle_radians);

double getLength2D(const double& x1, const double& y1, const double& x2, const double& y2);
float absolute(const float& value);