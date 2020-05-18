#pragma once
#include "Point4.h"
#include "Vec3.h"
class SolidVertex {

public:
	SolidVertex() = default;
	SolidVertex(Pointf4 a);
	SolidVertex(const SolidVertex& rhs);
	SolidVertex operator+(const SolidVertex& rhs) const;
	SolidVertex& operator+= (const SolidVertex& rhs);
	SolidVertex  operator-(const SolidVertex& rhs)const;
	SolidVertex& operator-=(const SolidVertex& rhs);
	SolidVertex  operator* (const float rhs) const;
	SolidVertex& operator*= (const float rhs);
	SolidVertex& operator= (const SolidVertex& rhs);

	Pointf4 p;
	
};