#include "ColorVertex.h"

ColorVertex::ColorVertex(Pointf4 a, Vec3 c)
	:p(a),
	color(c)
{
}
ColorVertex::ColorVertex(const ColorVertex& rhs)
	: p(rhs.p),
	color(rhs.color)
{
}






ColorVertex ColorVertex::operator+(const ColorVertex& rhs) const
{
	return ColorVertex(*this) += rhs;
}

ColorVertex& ColorVertex::operator+=(const ColorVertex& rhs)
{
	p += rhs.p;
	color += rhs.color;

	return *this;
}




ColorVertex ColorVertex ::operator-(const ColorVertex& rhs) const
{
	return ColorVertex(*this) -= rhs;
}

ColorVertex& ColorVertex::operator-=(const ColorVertex& rhs)
{
	p -= rhs.p;
	color -= rhs.color;
	return *this;
}


ColorVertex ColorVertex::operator*(const float rhs) const
{
	return ColorVertex(*this) *= rhs;
}

ColorVertex& ColorVertex::operator*=(const float rhs)
{
	p *= rhs;

	color *= rhs;
	return *this;
}

ColorVertex& ColorVertex::operator=(const ColorVertex& rhs)
{
	p = rhs.p;
	color = rhs.color;
	return *this;
}
