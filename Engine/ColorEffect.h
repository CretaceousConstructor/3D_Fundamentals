#pragma once



template <typename P,typename V,typename G>
class ColorEffect {
public:
	ColorEffect() = default;
	P ps;
	V vs;
	G gs;
};