
#include "Vertex.h"

Vertex::Vertex(Pointf4 a, Vec2 uv)
	:p(a),
	uvCoordinate(uv)
{
}

Vertex::Vertex(const Vertex& rhs)
	: p(rhs.p),
	uvCoordinate(rhs.uvCoordinate)
{
}


Vertex Vertex::operator+(const Vertex& rhs)
{
	return Vertex(*this) += rhs;
}

Vertex& Vertex::operator+=(const Vertex& rhs)
{
	p += rhs.p;
	uvCoordinate += rhs.uvCoordinate;

	return *this;
}




Vertex Vertex::operator-(const Vertex& rhs)
{
	return Vertex(*this) -= rhs;
}

Vertex& Vertex::operator-=(const Vertex& rhs)
{
	p -= rhs.p;
	uvCoordinate -= rhs.uvCoordinate;
	return *this;
}


Vertex Vertex::operator*(const float rhs)
{
	return Vertex(*this) *= rhs;
}

Vertex& Vertex::operator*=(const float rhs)
{
	p *= rhs;

	uvCoordinate *= rhs;
	return *this;
}


