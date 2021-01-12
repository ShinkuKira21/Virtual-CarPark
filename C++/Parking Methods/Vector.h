#pragma once
#include "../../Library/Functions.h"

class Vector
{
	protected:
		float x, y, z;

	public:
		Vector(float x, float y, float z);
		Vector();
		~Vector();

		void SetVector(float x, float y, float z);
		Vector(float, float, float);
		Vector();
		~Vector();
		
		void Scale(float scaleBy);	
		void Add(Vector& aVec);
		void Subtraction(Vector& aVec);

		float GetVector(int selector);
		float GetDotProduct(Vector& aVec);

		virtual void SetLocation(Vector& vec)
		{
			SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2));
		}

};

