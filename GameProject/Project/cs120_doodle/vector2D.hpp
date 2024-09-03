/*
  vector2D.hpp

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "cmath"
#include "math.hpp"

class Vector_2D
{
private:
    float x = 0.f;
    float y = 0.f;

public:
	void initialization(const float x1, const float y1);

	void setAngle(float angle);
	void setLength(float length);

	float getX();
    float getY();

	float getAngle();
	float getLength();

	void add(Vector_2D& vec2); // add vector vec2 from current vector
	void addTo(const float x1, const float y1); // add values from current vector
	void subtract(Vector_2D& vec2); // subtract vector vec2 from current vector
	void subtractTo(const float x1, const float y1); // subtract values from current vector
	void multiply(const float multiplier); // multiply the vector
	void divide(const float divider); // divide the vector
};

void swapVector(Vector_2D& vec1, Vector_2D& vec2); //swap the two vectors.