#pragma once

#include "ChiliMath.h"

class Spectrum {
public:
	static constexpr float l = -3.f;
	static constexpr float r =  3.f;
	static constexpr float b = -3.f;
	static constexpr float t =  3.f;
	static constexpr float f = -10.f;
	static constexpr float n = -2.f;


	static constexpr float aspect = r / t;

	float tangentOfFovYDividByTwo = t / abs(n);

};