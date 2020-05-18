#pragma once
#include "TextureVertex.h"
class WaveyVertexShader {

public:
	WaveyVertexShader() = default;

	template <typename T>
	T operator()(const T& in) const {
		T result = in;
		result.p.y += amplitude * std::sin(time * freqScroll + result.p.x * freqWave);
		return result;
	}
	void SetTime(float t) {
	
		time += t;
	}

	float time = 0.f;
	float freqWave =5.f;
	float freqScroll = 3.f;
	float amplitude = 0.05f;
	

};