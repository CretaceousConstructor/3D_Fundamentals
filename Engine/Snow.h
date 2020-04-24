#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Vec2.h"
#include "ChiliMath.h"
#include "Timer.h"

class Snow
{
public:
	Snow() = delete;
	Snow(Vec2 position, Color c, float rad, Vec2 valoci = { 0.0f,0.0f });
	void GetDraw(Graphics& GFX);
	void Move(float timeElapsed  = 0.0167f);
	//static::Graphics& GFX;


private:
	bool offTheScreen = false;
	Color snowColor;
	Vec2 valocity;
	Vec2 position;
	float radius;

};


