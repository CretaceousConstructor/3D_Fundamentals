#include "SolidVertex.h"

SolidVertex::SolidVertex(Pointf4 a)
	:p(a)
{
}
SolidVertex::SolidVertex(const SolidVertex& rhs)
	: p(rhs.p)
{
}


SolidVertex SolidVertex::operator+(const SolidVertex& rhs) const
{
	return SolidVertex(*this) += rhs;
}

SolidVertex& SolidVertex::operator+=(const SolidVertex& rhs)
{
	p += rhs.p;

	return *this;
}




SolidVertex SolidVertex ::operator-(const SolidVertex& rhs) const
{
	return SolidVertex(*this) -= rhs;
}

SolidVertex& SolidVertex::operator-=(const SolidVertex& rhs)
{
	p -= rhs.p;
	return *this;
}


SolidVertex SolidVertex::operator*(const float rhs) const
{
	return SolidVertex(*this) *= rhs;
}

SolidVertex& SolidVertex::operator*=(const float rhs)
{
	p *= rhs;

	return *this;
}

SolidVertex& SolidVertex::operator=(const SolidVertex& rhs)
{
	p = rhs.p;
	return *this;
}
