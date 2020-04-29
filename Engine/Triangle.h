#pragma once
#include <array>
#include <vector>

#include "Colors.h"
#include "Vec4.h"
#include "Point4.h"
#include "Graphics.h"
#include "Vec2.h"
#include "ChiliMath.h"
#include "minwindef.h"
class Triangle
{
public:
	Triangle(Pointf4 a, Pointf4 b, Pointf4 c);
	Triangle();
	void Triangle::GetDraw(Graphics& GFX);
	void Triangle::GetDraw(Graphics& GFX, int a);
	void GetDraw(Graphics& GFX,float focalLength);
	std::vector<Pointf4> points;


};

