#pragma once
#include "Point4.h"
#include "Vec2.h"
class TextureVertex {

	public:
		TextureVertex() = default;
		TextureVertex(Pointf4 a, Vec2 uv);
		TextureVertex(const TextureVertex& rhs);
		TextureVertex operator+(const TextureVertex& rhs) const;
		TextureVertex& operator+= (const TextureVertex& rhs);
		TextureVertex  operator-(const TextureVertex& rhs)const;
		TextureVertex& operator-=(const TextureVertex& rhs);
		TextureVertex  operator* (const float rhs) const;
		TextureVertex& operator*= (const float rhs);
		TextureVertex& operator= (const TextureVertex& rhs);

		Pointf4 p;
		Vec2 uvCoordinate;
};