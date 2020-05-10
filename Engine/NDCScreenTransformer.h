#pragma once

#include "Point4.h"


class NDCScreenTransformer
{
public:
	NDCScreenTransformer(int w, int h) 
		:
		xFactor( float(w) / 2.f),
		yFactor( float(h) / 2.f)
	{}
	template <typename Vertex>
	inline Vertex& Transform(Vertex& v) {
		float tempZricapical = 1.f / v.p.w;
		v *= tempZricapical;
		v.p.w = tempZricapical;
		v.p.x = ( v.p.x + 1.f) * xFactor;
		v.p.y = (-v.p.y + 1.f) * yFactor;
		return v;
	}
	template <typename Vertex>
	inline Vertex GetTransform(const Vertex& v) {
		return Transform(Vertex(v));
	}




private:
	float xFactor;
	float yFactor;
};


//template<class Vertex>
//Vertex& Transform(Vertex& v) const
//{
//	// perform homo -> ndc on xyz / perspective-correct interpolative divide on all other attributes
//	const float wInv = 1.0f / v.pos.w;
//	v *= wInv;
//	// additional divide for mapped z because it must be interpolated
//	// adjust position x,y from perspective normalized space
//	// to screen dimension space after perspective divide
//	v.pos.x = (v.pos.x + 1.0f) * xFactor;
//	v.pos.y = (-v.pos.y + 1.0f) * yFactor;
//	// store 1/w in w (we will need the interpolated 1/w
//	// so that we can recover the attributes after interp.)
//	v.pos.w = wInv;
//
//	return v;
//}
//template<class Vertex>
//Vertex GetTransformed(const Vertex& v) const
//{
//	return Transform(Vertex(v));
//}
//private:
//	float xFactor;
//	float yFactor;
//};