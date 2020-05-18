#pragma once
#include <vector>
#include "Colors.h"
#include "ColorVertex.h"
#include "Triangle.h"
class SolidGeometryShader {
public:
	SolidGeometryShader() = default;

	template <typename T>
	_Triangle<ColorVertex> operator()(const T & v0, const T& v1, const T& v2,const int triangle_index) const {

		return
		{
			ColorVertex{v0.p,toVec3(triangle_colors[triangle_index / 2])},
			ColorVertex{v1.p,toVec3(triangle_colors[triangle_index / 2])},
			ColorVertex{v2.p,toVec3(triangle_colors[triangle_index / 2])}
		};
	}


	void BindColors(std::vector<Color> colorList) {
		triangle_colors = colorList;
	}


private:
	std::vector<Color> triangle_colors;


};