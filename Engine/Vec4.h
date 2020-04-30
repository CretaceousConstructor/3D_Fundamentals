#pragma once
#include "Point4.h"


template <typename T>
class _Vec4 {

public:
	_Vec4() = default;//default constructor
	_Vec4(T x, T y, T z) : x(x), y(y), z(z){}


	_Vec4(const _Vec4& vect)
		:
		x(vect.x), y(vect.y), z(vect.z), s(vect.s), e(vect.e)
	{}//copy constructor

	_Vec4(const _Point4<T>& vect)
		:
		x(vect.x), y(vect.y), z(vect.z)
	{}// constructor take Vector assumes to start at origin


	_Vec4& Normalize() {

		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	_Vec4 GetNormalized() const
	{
		_Vec4 norm = *this;
		norm.Normalize();
		return norm;
	}

	T	LenSq() const
	{
		return sq(*this);
	}

	T	Len() const {

		return (T)sqrt(LenSq());
	}


	_Vec4 operator- () const
	{
		_Vec4 result(-x,-y,-z);
		return result;
	}




	_Vec4& operator +=(const _Vec4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	_Vec4 operator+(const _Vec4& rhs) const
	{
		return _Vec4(*this) += rhs;
	}

	T operator*(const _Vec4& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}







	_Vec4& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	_Vec4 operator*(const T& rhs) const
	{
		return _Vec4(*this) *= rhs;
	}



	static _Vec4 dot(_Vec4 const& v1, _Vec4 const& v2) {

		return { v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z , v1.x * v2.y - v1.y * v2.x };
	}

public:
	_Point4<T> s;
	_Point4<T> e;
	T x;
	T y;
	T z;
};


typedef _Vec4<float> Vec4;
typedef _Vec4<double> Ved4;
typedef _Vec4<int> Vei4;