#pragma once
#include <array>
#include "Colors.h"
#include "Vec3.h"
#include "Graphics.h"
class Triangle
{
public:
	Triangle(Vec3 a, Vec3 b, Vec3 c);
	void GetDraw(Graphics& GFX,float focalLength);
private:
	std::array<Vec3,3> points;


};

