#pragma once
#include "Point4.h"
#include "Vec2.h"
#include "Colors.h"
#include <memory>
#include "Sprite.h"
#include <string>



//<TextureVertex, TexturePixelShader> 

template <typename T, typename S>
class TextureEffect  {
public:
	TextureEffect() = delete;
	TextureEffect(std::string s) :
		ps(s)
	{
	}



	S ps;
};
















//
//
//TextureEffect::Vertex::Vertex(Pointf4 a, Vec2 uv)
//	:p(a),
//	uvCoordinate(uv)
//{
//}
//
//TextureEffect::Vertex::Vertex(const TextureEffect::Vertex& rhs)
//	: p(rhs.p),
//	uvCoordinate(rhs.uvCoordinate)
//{
//}
//
//
//
//
//TextureEffect::Vertex TextureEffect::Vertex::operator+(const TextureEffect::Vertex& rhs) const
//{
//	return TextureEffect::Vertex(*this) += rhs;
//}
//
//
//
//
//TextureEffect::Vertex& TextureEffect::Vertex::operator+=(const TextureEffect::Vertex& rhs)
//{
//	p += rhs.p;
//	uvCoordinate += rhs.uvCoordinate;
//
//	return *this;
//}
//
//
//
//
//TextureEffect::Vertex TextureEffect::Vertex::operator-(const TextureEffect::Vertex& rhs) const
//{
//	return TextureEffect::Vertex(*this) -= rhs;
//}
//
//TextureEffect::Vertex& TextureEffect::Vertex::operator-=(const TextureEffect::Vertex& rhs)
//{
//	p -= rhs.p;
//	uvCoordinate -= rhs.uvCoordinate;
//	return *this;
//}
//
//
//TextureEffect::Vertex TextureEffect::Vertex::operator*(const float rhs) const
//{
//	return TextureEffect::Vertex(*this) *= rhs;
//}
//
//TextureEffect::Vertex& TextureEffect::Vertex::operator*=(const float rhs)
//{
//	p *= rhs;
//
//	uvCoordinate *= rhs;
//	return *this;
//}
//
//TextureEffect::Vertex& TextureEffect::Vertex::operator=(const TextureEffect::Vertex& rhs)
//{
//	p = rhs.p;
//	uvCoordinate = rhs.uvCoordinate;
//	return *this;
//}
//
//template<typename T, typename S>
//inline T TextureEffect<T, S>::operator+(const T& rhs) const
//{
//
//	return T(*this) += rhs;
//
//	
//}
