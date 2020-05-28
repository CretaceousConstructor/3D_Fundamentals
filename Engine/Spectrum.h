#pragma once

#include "ChiliMath.h"

class Spectrum {
public:
	static constexpr float l = -4.f;
	static constexpr float r =  4.f;
	static constexpr float b = -3.f;
	static constexpr float t =  3.f;


	//(r - l) / (t - b) is as the same ratio as ScreenWidth / ScreenHeiht
	//so your squre shit will be squre shit
	static constexpr float f = -8.f;
	static constexpr float n = -3.f;


	static constexpr float aspect = r / t;

	float tangentOfFovYDividByTwo = t / abs(n);

};