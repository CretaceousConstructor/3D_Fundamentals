#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Vec2.h"
class SnowFlake
{
public:
	SnowFlake() = delete;
	SnowFlake(Vec2 p,Color c,float d);
	void GetDraw(Graphics& GFX);
	

private:
	
	Color snowColor;
	Vec2 position;
	float radius;

};

SnowFlake::SnowFlake(Vec2 p,Color c = Colors::White,float d = 1.0f)
	:
	snowColor(c),
	position(p),
	radius(d)
{
}



