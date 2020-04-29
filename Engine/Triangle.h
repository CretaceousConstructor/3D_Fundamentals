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
	void DrawTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2,Color c);
private:
	//ALL STATRT from top vertex
	void DrawFlatTopTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, Color c);//draw in clockwise order 
	void DrawFlatBottomTriangle(const Vec2& v0, const Vec2& v1, const Vec2& v2, Color c);//draw in counterclockwise order 


};

