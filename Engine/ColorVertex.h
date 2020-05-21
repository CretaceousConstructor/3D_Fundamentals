#pragma once
#include "Point4.h"
#include "Vec3.h"
class ColorVertex {

public:
	ColorVertex() = default;
	ColorVertex(Pointf4 a, Vec3 c);
	ColorVertex(const ColorVertex& rhs);

	ColorVertex operator+(const ColorVertex& rhs) const;
	ColorVertex& operator+= (const ColorVertex& rhs);
	ColorVertex  operator-(const ColorVertex& rhs)const;
	ColorVertex& operator-=(const ColorVertex& rhs);
	ColorVertex  operator* (const float rhs) const;
	ColorVertex& operator*= (const float rhs);
	ColorVertex& operator= (const ColorVertex& rhs);

	Pointf4 p;
	Vec3 color;
};