#pragma once
#include "Graphics.h"

#include "Point4.h"

class NDCScreenTransformer
{
public:
	NDCScreenTransformer() 
		:
		xFactor( float(Graphics::ScreenWidth) / 2.f),
		yFactor( float(Graphics::ScreenHeight) / 2.f)
	{}
	Pointf4& Transform(Pointf4& v) {
		v.x = (v.x + 1.f) * xFactor;
		v.y = (-v.y + 1.f) * yFactor;
		return v;
	}

	Pointf4 GetTransform(const Pointf4& v) {
		
		return Transform(Pointf4(v));
	}



private:
	float xFactor;
	float yFactor;
};

