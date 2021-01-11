#pragma once
#include "../../Library/Functions.h"

class Vector
{
	protected:
		float x, y, z;

	public:
		Vector(int, int, int);
		Vector();
		~Vector();

		void SetVector(int, int, int);
		void Scale(int scaleBy);	
		void Add(Vector& aVec);
		void Subtraction(Vector& aVec);

		int GetVector(int selector);
		float GetDotProduct(Vector& aVec);
};

