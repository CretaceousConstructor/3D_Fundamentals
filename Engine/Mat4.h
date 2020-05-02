#pragma once
#include "ChiliMath.h"
#include "Vec4.h"
#include <cstring>

template <typename T>
class _Mat4
{
public:
	_Mat4() = default;
	_Mat4& operator=(const _Mat4& rhs)
	{
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}
	_Mat4& operator*=(T rhs)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				elements[i][j] *= rhs;
			}
		}
		return *this;
	}
	_Mat4 operator*(T rhs) const
	{
		_Mat4 result = *this;
		return result *= rhs;
	}

	_Mat4 operator*(const _Mat4& rhs) const
	{
		_Mat4 result;
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				T sum = (T)0.0;
				for (size_t i = 0; i < 4 ;i++)
				{
					sum += rhs.elements[i][k] * elements[j][i];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}



	static _Mat4 Identity()
	{
		_Mat4 i = { (T)1.0,(T)0.0,(T)0.0,(T)0.0,
					(T)0.0,(T)1.0,(T)0.0,(T)0.0,
					(T)0.0,(T)0.0,(T)1.0,(T)0.0,
					(T)0.0,(T)0.0,(T)0.0,(T)1.0
		};
		return i;
	}

	static _Mat4 Scaling(T factor)
	{
		_Mat4 s = { factor,(T)0.0,(T)0.0,(T)0.0,
					(T)0.0,factor,(T)0.0,(T)0.0,
					(T)0.0,(T)0.0,factor,(T)0.0,
					(T)0.0,(T)0.0,(T)0.0,(T)1.0
		};
		return s;
	}

	static _Mat4 RotationAroundAxisX(T theta)
	{
		const T cosTheta = (T)cos(theta);
		const T sinTheta = (T)sin(theta);

		_Mat4 r = { (T)1.0 ,(T)0.0  ,  (T)0.0   , (T)0.0,
					(T)0.0 ,cosTheta,  -sinTheta, (T)0.0,
					(T)0.0 ,sinTheta,  cosTheta , (T)0.0,
					(T)0.0 ,(T)0.0  ,  (T)0.0   , (T)1.0
		};
		return r;
	}

	static _Mat4 RotationAroundAxisY(T theta)
	{
		const T cosTheta = (T)cos(theta);
		const T sinTheta = (T)sin(theta);
		_Mat4 r = { cosTheta ,  (T)0.0  ,  sinTheta  , (T)0.0,
					(T)0.0   ,  (T)1.0,    (T)0.0     , (T)0.0,
					-sinTheta,  (T)0.0  ,  cosTheta   , (T)0.0,
					(T)0.0   ,  (T)0.0  ,  (T)0.0     , (T)1.0
		};
		return r;
	}

	static _Mat4 RotationAroundAxisZ(T theta )
	{
		const T cosTheta = (T)cos(theta);
		const T sinTheta = (T)sin(theta);
		_Mat4 r = {
					cosTheta ,  -sinTheta, (T)0.0  ,   (T)0.0,
					sinTheta ,  cosTheta , (T)0.0  ,   (T)0.0,
					(T)0.0   ,  (T)0.0   , (T)1.0  ,   (T)0.0,
					(T)0.0   ,  (T)0.0   , (T)0.0  ,   (T)1.0
		};
		return r;
	}



	static _Mat4 Translation(T dx, T dy, T dz)
	{

		_Mat4 r = {
					(T)1.0   ,  (T)0.0 ,   (T)0.0  ,   dx,
					(T)0.0   ,  (T)1.0  ,  (T)0.0  ,   dy,
					(T)0.0   ,  (T)0.0   , (T)1.0  ,   dz,
					(T)0.0   ,  (T)0.0   , (T)0.0  ,   (T)1.0
		};
		return r;
	}


public:
	// [ row ][ col ]
	T elements[4][4];
};




namespace Mat {
	template<typename T>
	static _Vec4<T> RotateAroundArbitraryVectorStartAtOrigin(_Vec4<T> v, T theta, _Vec4<T> k) {
		const T cosTheta = (T)cos(theta);
		const T sinTheta = (T)sin(theta);

		k.Normalize();
		_Vec4<T> vRot = v * cosTheta + (_Vec4<T>::dot(k, v)) * sinTheta + k * (k * v) * ((T)1.0 - cosTheta);

		return vRot;

	}


	template<typename T>
	static _Point4<T> RotateAroundArbitraryVectorStartAtOrigin(_Point4<T> p, T theta, _Vec4<T> k) {
		const T cosTheta = (T)cos(theta);
		const T sinTheta = (T)sin(theta);
		k.Normalize();

		_Vec4<T> v = p;


		_Vec4<T> vRot = v * cosTheta + (_Vec4<T>::dot(k, v)) * sinTheta + k * (k * v) * ((T)1.0 - cosTheta);



		return { vRot.x,vRot.y,vRot.z,(T)1.0 };

	}

}
	











		//template<typename T>
		//_Vec4<T> operator*(const _Mat4<T>& lhs, const _Vec4<T>& rhs)
		//{
		//	return
		//	{
		//		rhs.x * lhs.elements[0][0] + rhs.y * lhs.elements[0][1] + rhs.z * lhs.elements[0][2],
		//		rhs.x * lhs.elements[1][0] + rhs.y * lhs.elements[1][1] + rhs.z * lhs.elements[1][2],
		//		rhs.x * lhs.elements[2][0] + rhs.y * lhs.elements[2][1] + rhs.z * lhs.elements[2][2],
		//		(T)0.0
		//	};
		//}


		template<typename T>
		_Point4<T>& operator*=(_Mat4<T>& lhs, const _Point4<T>& rhs)
		{
			return lhs = rhs * lhs;
		}



		template<typename T>
		_Point4<T> operator*(const _Mat4<T>& lhs, const _Point4<T>& rhs)
		{
			return
			{
				rhs.x * lhs.elements[0][0] + rhs.y * lhs.elements[0][1] + rhs.z * lhs.elements[0][2] + rhs.w * lhs.elements[0][3],
				rhs.x * lhs.elements[1][0] + rhs.y * lhs.elements[1][1] + rhs.z * lhs.elements[1][2] + rhs.w * lhs.elements[1][3],
				rhs.x * lhs.elements[2][0] + rhs.y * lhs.elements[2][1] + rhs.z * lhs.elements[2][2] + rhs.w * lhs.elements[2][3],
				rhs.x * lhs.elements[3][0] + rhs.y * lhs.elements[3][1] + rhs.z * lhs.elements[3][2] + rhs.w * lhs.elements[3][3],
				
			};
		}


		template<typename T>
		_Point4<T> wPreserveMultiplication(const _Mat4<T>& lhs, const _Point4<T>& rhs)
		{
			return
			{
				rhs.x * lhs.elements[0][0] + rhs.y * lhs.elements[0][1] + rhs.z * lhs.elements[0][2] + (T)1.0 * lhs.elements[0][3],
				rhs.x * lhs.elements[1][0] + rhs.y * lhs.elements[1][1] + rhs.z * lhs.elements[1][2] + (T)1.0 * lhs.elements[1][3],
				rhs.x * lhs.elements[2][0] + rhs.y * lhs.elements[2][1] + rhs.z * lhs.elements[2][2] + (T)1.0 * lhs.elements[2][3],
				rhs.w,

			};
		}







typedef _Mat4<float> Mat4;
typedef _Mat4<double> Mad4;