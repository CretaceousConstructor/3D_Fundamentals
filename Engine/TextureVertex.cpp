#include "TextureVertex.h"


TextureVertex::TextureVertex(Pointf4 a, Vec2 uv)
	:p(a),
	uvCoordinate(uv)
{
}

TextureVertex::TextureVertex(const TextureVertex& rhs)
	: p(rhs.p),
	uvCoordinate(rhs.uvCoordinate)
{
}






TextureVertex TextureVertex::operator+(const TextureVertex& rhs) const
{
	return TextureVertex(*this) += rhs;
}

TextureVertex& TextureVertex::operator+=(const TextureVertex& rhs)
{
	p += rhs.p;
	uvCoordinate += rhs.uvCoordinate;

	return *this;
}




TextureVertex TextureVertex ::operator-(const TextureVertex& rhs) const
{
	return TextureVertex(*this) -= rhs;
}

TextureVertex& TextureVertex::operator-=(const TextureVertex& rhs)
{
	p -= rhs.p;
	uvCoordinate -= rhs.uvCoordinate;
	return *this;
}


TextureVertex TextureVertex::operator*(const float rhs) const
{
	return TextureVertex(*this) *= rhs;
}

TextureVertex& TextureVertex::operator*=(const float rhs)
{
	p *= rhs;

	uvCoordinate *= rhs;
	return *this;
}

TextureVertex& TextureVertex::operator=(const TextureVertex& rhs)
{
	p = rhs.p;
	uvCoordinate = rhs.uvCoordinate;
	return *this;
}

TextureVertex TextureVertex::operator/(const float rhs) const
{


	return TextureVertex(*this) /= rhs;
}

TextureVertex& TextureVertex::operator/=(const float rhs)
{
	p *= rhs;
	uvCoordinate *= rhs;
	return *this;

}


