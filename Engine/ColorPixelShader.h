#pragma once

#include <memory>
#include <string>
#include "Colors.h"
#include "Sprite.h"

class ColorPixelShader {
public:
	ColorPixelShader() = default;
	
public:
	template<typename T>
	Color operator()(const T& in) const {

		return Color(in.color);
	}

};