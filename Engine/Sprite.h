#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "Colors.h"

#include "Vec2.h"
#include "Mat2.h"



class texture
{
public:
	class rect;
	
	texture() = default;

	texture(std::string bmpFileName);

	//void GetDraw(Graphics& GFX,rect rec,Vec2 p);
	//void GetDraw(Graphics& GFX, rect rec, Vec2 p, float scaleFactor);
	//void texture::GetDrawWithoutClipping(Graphics& GFX, rect rec, Vec2 p, float scaleFactor);

	inline int GetWidth() const {
		return width;
	}
	inline int GetHeight() const {
		return height;
	}

	Color GetColor(int x, int y)const {

		return bitMap[(height-y )* width + x];

	}

	class rect {
	public:
		inline rect(int t, int l, int r, int b)
			:top(t), left(l), right(r), bottom(b)
		{

		}
		inline rect() = default;
		int top;
		int left;
		int right;
		int bottom;
	};
	

private:

	std::unique_ptr<Color[]> bitMap;
	int width = 0;
	int height = 0;

};

