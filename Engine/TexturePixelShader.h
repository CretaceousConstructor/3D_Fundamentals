#pragma once
#include <memory>
#include <string>
#include "Colors.h"
#include "Sprite.h"
#include "TextureVertex.h"
class TexturePixelShader{

public:
	TexturePixelShader(std::string s) :
		tex(std::make_unique<texture>("D:\\CS\\ChiliEngine\\Bmp\\tex.bmp"))
	{
	}
public:
	template<typename T>
	Color operator()(const T& in) const {
		const int w = tex->GetWidth();
		const int h = tex->GetHeight();
		const float u = in.uvCoordinate.x; // u
		const float v = in.uvCoordinate.y; // v
		
		int x = (int)(w * fmod(u, 1.f));
		int y = (int)(h * fmod(v, 1.f));
		if (x >= w || x < 0 || y >= h || y < 0) {
			return Colors::White;
		}
		return tex->GetColor(x, y);
	
	}
private:
	std::unique_ptr<texture> tex;
};