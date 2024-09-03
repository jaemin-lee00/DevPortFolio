/*
  vector2D.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "cmath"
#include "vector2D.hpp"
#include "math.hpp"
#include "vector2D.hpp"

void Vector_2D::initialization(const float x1, const float y1)
{
	x = x1;
	y = y1;
}

void Vector_2D::setAngle(float angle)
{
	float distance = sqrt(x * x + y * y);
	x = distance * cos(toRadians(angle));
	y = distance * sin(toRadians(angle));
}

void Vector_2D::setLength(float length)
{
	float angle = this->getAngle();
	x = length * cos(angle);
	y = length * sin(angle);
}

float Vector_2D::getX() { return x; }

float Vector_2D::getY() { return y; }

float Vector_2D::getAngle()
{
	return atan2(y, x);
}

float Vector_2D::getLength()
{
	return sqrt(x * x + y * y);
}

void Vector_2D::add(Vector_2D& vec2)
{
	x += vec2.x;
	y += vec2.y;
}

void Vector_2D::addTo(const float x1, const float y1)
{
	x += x1;
	y += y1;
}

void Vector_2D::subtract(Vector_2D& vec2)
{
	x -= vec2.x;
	y -= vec2.y;
}

void Vector_2D::subtractTo(const float x1, const float y1)
{
	x -= x1;
	y -= y1;
}

void Vector_2D::multiply(const float multiplier)
{
	x *= multiplier;
	y *= multiplier;
}

void Vector_2D::divide(const float divider)
{
	x /= divider;
	y /= divider;
}

void swapVector(Vector_2D& vec1, Vector_2D& vec2) {
	Vector_2D vec3 = vec1;
	vec1 = vec2;
	vec2 = vec3;
}