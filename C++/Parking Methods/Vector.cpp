#include "Vector.h"

Vector::Vector()
{
	x=y=z=0;
}

Vector::Vector(float aX, float aY, float aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

Vector::~Vector() { }

void Vector::SetVector(float aX, float aY, float aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

void Vector::Scale(float s)
{
	x = s * x;
	y = s * y;
	z = s * z;
} 

void Vector::Add(Vector& aVec)
{
	x += aVec.GetVector(0);
	y += aVec.GetVector(1);
	z += aVec.GetVector(2);
}

void Vector::Subtraction(Vector& aVec)
{
	x -= aVec.GetVector(0);
	y -= aVec.GetVector(1);
	z -= aVec.GetVector(2);
}

float Vector::GetVector(int value)
{
	if (value == 0) return x;
	else if (value == 1) return y;
	else return z;
}

float Vector::GetDotProduct(Vector& aVec)
{
	return (x * aVec.GetVector(0)) + (y * aVec.GetVector(1)) + (z * aVec.GetVector(2));
}