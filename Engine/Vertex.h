#pragma once
#include "Point4.h"
#include "Vec2.h"

class Vertex
{
public:
	Vertex() = default;
	Vertex(Pointf4 a, Vec2 uv);
	Vertex(const Vertex& rhs);
	Vertex operator+(const Vertex& rhs);
	Vertex& operator+= (const Vertex& rhs);
	Vertex Vertex::operator-(const Vertex& rhs);
	Vertex& Vertex::operator-=(const Vertex& rhs);
	Vertex operator* (const float rhs);
	Vertex& operator*= (const float rhs);


	Pointf4 p;
	Vec2 uvCoordinate;



};

