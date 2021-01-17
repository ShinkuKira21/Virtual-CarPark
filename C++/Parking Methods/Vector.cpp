/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "Vector.h"

// sets all values to naught
Vector::Vector()
{
	x=y=z=0;
}

// custom set vector constructor
Vector::Vector(float aX, float aY, float aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

Vector::~Vector() { }

// a way to set the vector again after initialisation.
void Vector::SetVector(float aX, float aY, float aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

// a method to scale vector
void Vector::Scale(float s)
{
	x = s * x;
	y = s * y;
	z = s * z;
} 

// a method to add to vector
void Vector::Add(Vector& aVec)
{
	x += aVec.GetVector(0);
	y += aVec.GetVector(1);
	z += aVec.GetVector(2);
}

// a method to subtract from a vector
void Vector::Subtraction(Vector& aVec)
{
	x -= aVec.GetVector(0);
	y -= aVec.GetVector(1);
	z -= aVec.GetVector(2);
}

// a method to return a vector attribute
float Vector::GetVector(int value)
{
	if (value == 0) return x;
	else if (value == 1) return y;
	else return z;
}

//a method to return a dot product
float Vector::GetDotProduct(Vector& aVec)
{
	return (x * aVec.GetVector(0)) + (y * aVec.GetVector(1)) + (z * aVec.GetVector(2));
}