#pragma once


template <typename T>

class _Point4 {
public:
	_Point4() {};//default constructor
	_Point4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
	{}//constructor using superclass constructor;
	_Point4(T x, T y, T z) : x(x), y(y), z(z) ,w((T)1)
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


public:
	T x;
	T y;
	T z;
	T w;
};

typedef _Point4<float> Pointf4;
typedef _Point4<double> Pointd4;
typedef _Point4<int> PointInt4;