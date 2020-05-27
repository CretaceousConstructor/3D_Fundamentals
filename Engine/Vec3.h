#pragma once
#include "ChiliMath.h"
#include "Vec2.h"
#include "Colors.h"
template <typename T>

class _Vec3 : public _Vec2<T> {
public:
	_Vec3() {};//default constructor
	_Vec3(T x, T y, T z) : _Vec2(x, y), z(z)
	{}//constructor using superclass constructor;
	_Vec3(const _Vec3& vect)
		:
		_Vec3(vect.x, vect.y, vect.z)
	{}//copy constructor

	template <typename T2>
	explicit operator _Vec3<T2>() const {
		return { (T2)x,(T2)y,(T2)z };
	}

	T		LenSq() const
	{
		return sq(*this);
	}

	T	Len() const {

		return sqrt(LenSq());
	}

	_Vec3& Normalize() {
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	_Vec3 GetNormalized() const
	{
		_Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}

	_Vec3	operator-() const
	{
		return _Vec3(-x, -y, -z);
	}
	_Vec3& operator=(const _Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}//copy assignment operator overloading



	_Vec3& operator +=(const _Vec3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	_Vec3& operator-=(const _Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	T		operator*(const _Vec3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}


	_Vec3	operator+(const _Vec3& rhs) const
	{
		return _Vec3(*this) += rhs;
	}
	_Vec3	operator-(const _Vec3& rhs) const
	{
		return _Vec3(*this) -= rhs;
	}


	_Vec3& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	_Vec3	operator*(const T& rhs) const
	{
		return _Vec3(*this) *= rhs;
	}



	_Vec3& operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	_Vec3	operator/(const T& rhs) const
	{
		return _Vec3(*this) /= rhs;
	}
	bool	operator==(const _Vec3& rhs) const
	{
		return x == rhs.x && y == rhs.y && rhs.z = z;
	}
	bool	operator!=(const _Vec3& rhs) const
	{
		return !(*this == rhs);
	}

	explicit operator Color()const
	{
		return Color{ (unsigned char)x,(unsigned char)y,(unsigned char)z };
	}

	static _Vec3 GetHadamard(_Vec3 lhs,_Vec3 rhs) {
		return { lhs.x * rhs.x ,lhs.y * rhs.y,lhs.z * rhs.z };
	}
	_Vec3 Saturate() {
		if (x < (T)0) {
			x = (T)0;
		}
		if (x > (T)1.0f) {
			x = (T)1.0f;
		}

		if (y < (T)0) {
			y = (T)0;
		}
		if (y > (T)1.0f) {
			y = (T)1.0f;
		}

		if (z < (T)0) {
			z = (T)0;
		}
		if (z > (T)1.0f) {
			z = (T)1.0f;
		}


		return *this;
	}

public:
	T z;
};

typedef _Vec3<float> Vec3;
typedef _Vec3<double> Ved3;
typedef _Vec3<int> Vei3;


static Vec3 toVec3(Color c)
{
	return Vec3{ (float)c.GetR(), (float)c.GetG(), (float)c.GetB() };
}
