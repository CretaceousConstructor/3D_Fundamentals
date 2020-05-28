#pragma once

template <typename T>
class _Vec4;
template <typename T>

class _Point4 {
public:
	_Point4() : w(T(1.0)) {
	};//default constructor
	_Point4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
	{}
	_Point4(T x, T y, T z) : x(x), y(y), z(z), w((T)1)
	{}
	_Point4(const _Point4& p4)
		:
		_Point4(p4.x, p4.y, p4.z, p4.w)
	{}//copy constructor
	_Point4& operator= (const _Point4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return	*this;
	}

	_Point4 operator+(const _Point4& rhs)const
	{
		_Point4 result;
		result.x = x + rhs.x;
		result.y = y + rhs.y;
		result.z = z + rhs.z;
		result.w = w + rhs.w;

		return	result;
	}

	_Point4 operator-(const _Point4& rhs) const
	{
		_Point4 result;
		result.x = x - rhs.x;
		result.y = y - rhs.y;
		result.z = z - rhs.z;
		result.w = w - rhs.w;

		return	result;
	}

	_Point4 operator*(T rhs) const
	{
		_Point4 result;
		result.x = x * rhs;
		result.y = y * rhs;
		result.z = z * rhs;
		result.w = w * rhs;
		return	result;
	}
	_Point4& operator*=(T rhs)
	{

		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return	*this;
	}




	_Point4 operator/(T rhs) const
	{
		_Point4 result;
		result.x = x / rhs;
		result.y = y / rhs;
		result.z = z / rhs;
		result.w = w / rhs;
		return	result;
	}







	_Point4 operator+(const _Vec4<T>& rhs) const
	{

		return	_Point4(*this) += rhs;
	}


	_Point4& operator+=(const _Vec4<T>& rhs)
	{

		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	_Point4& operator+=(const _Point4& rhs)
	{

		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	_Point4& operator-=(const _Point4& rhs)
	{

		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}


	_Point4 operator-() const
	{
		_Point4 result;
		result.x = -x;
		result.y = -y;
		result.z = -z;
		result.w = -w;

		return result;
	}








public:
	T x;
	T y;
	T z;
	T w;
};

typedef _Point4<float> Pointf4;
typedef _Point4<double> Pointd4;
typedef _Point4<int> PointInt4;