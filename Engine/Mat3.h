#pragma once
#include "Vec3.h"


template <typename T>
class _Mat3
{

public:
	_Mat3& operator=(const _Mat3& rhs)
	{
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}
	_Mat3& operator*= (T rhs) {
		for (auto& row : elements)
		{
			for (T& e : row)
			{
				e *= rhs;
			}
		}
		return *this;
	}

	_Mat3 operator*(T rhs) const
	{
		_Mat3 result = *this;
		return result *= rhs;

	}

	_Mat3 operator*(const _Mat3& rhs) const
	{
		_Mat3 result;
		//j: row	index of resulting matrix
		//k: column index of resulting matrix
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				T sum = (T)0.0;
				for (size_t i = 0; i < 3; i++)
				{
					//i changes: first  matrix's column i changes
					//			 second matrix's row    i changes
					sum += elements[j][i] * rhs.elements[i][k];
					//j: first  matrix's row	changes
					//k: second matrix's column changes
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}

	static _Mat3 Identity() {
		return {
			(T)1.0,(T)0.0,(T)0.0,
			(T)0.0,(T)1.0,(T)0.0,
			(T)0.0,(T)0.0,(T)1.0
		}
	}
	static _Mat3 Scaling(T factor)
	{
		return{
			factor,(T)0.0,(T)0.0,
			(T)0.0,factor,(T)0.0,
			(T)0.0,(T)0.0,factor
		};
	}





public:
	T elements[3][3];

};