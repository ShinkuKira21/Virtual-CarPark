/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

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

		void Scale(float scaleBy);	
		void Add(Vector& aVec);
		void Subtraction(Vector& aVec);

		float GetVector(int selector);
		float GetDotProduct(Vector& aVec);

		// sets location
		virtual void SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

		// returns vector
		virtual Vector GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }
};

