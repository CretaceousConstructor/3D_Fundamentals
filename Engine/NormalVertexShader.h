#pragma once

class NormalVertexShader {

public:
	NormalVertexShader() = default;
	template <typename T>
	T operator()(const T& in) const {
		return in;
	}


};