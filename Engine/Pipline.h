#pragma once

#include "Graphics.h"
#include "Vertex.h"
#include <vector>
#include <memory>
#include "IndexList.h"
#include "Mat4.h"
#include "Spectrum.h"
#include "Triangle.h"
#include "ChiliMath.h"
#include "Camera.h"
#include "Zbuffer.h"

#include "TextureEffect.h"
#include "ColorEffect.h"

#include "TextureVertex.h"
#include "ColorVertex.h"
#include "SolidVertex.h"

#include "TexturePixelShader.h"
#include "ColorPixelShader.h"

#include "WaveyVertexShader.h"
#include "NormalVertexShader.h"

#include "SolidGeometryShader.h"


#include "ShaderChoser.h"
class Pipline
{
public:
	Pipline() = delete;
	Pipline(Graphics& GFX);
	template <typename Vertex>
	void SeparateIndexesListAndVertex(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes, ShaderChoser choser);
	template <typename Vertex>
	void GoThroughVertexTransformation(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes, ShaderChoser choser);
	template <typename Vertex>
	void AssembleTriangle(const std::vector<Indexes> IndexesList, const std::vector<Vertex>& vertexes ,ShaderChoser choser);
	template <typename Vertex>
	void ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2,int i, ShaderChoser choser);
	template <typename Vertex>
	void PostProcessTriangle(_Triangle<Vertex> triangle, ShaderChoser choser);
	template <typename Vertex>
	void DrawTriangle(const _Triangle<Vertex>& tr, ShaderChoser choser);
	template <typename Vertex>
	void DrawFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, ShaderChoser choser);//draw in clockwise order 
	template <typename Vertex>
	void DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, ShaderChoser choser);//draw in counterclockwise order 

	template <typename Vertex>
	Color GetColor(Vertex v) {
		return Colors::White;
	}
	template <>
	Color GetColor(ColorVertex v) {
		return ColorEffect.ps(v);
	}
	template <>
	Color GetColor(TextureVertex v) {
		return TextureEffect.ps(v);
	}

	template <typename Vertex>
	auto GetVertex(const Vertex& v) {
		return v;
	}

	template <>
	auto GetVertex(const ColorVertex& v) {
		return ColorEffect.vs(v);
	}

	template <>
	auto GetVertex(const TextureVertex& v) {
		return TextureEffect.vs(v);
	}



	template <typename Vertex>
	auto GetTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2,int num) {

		return _Triangle<Vertex>{v0, v1, v2};
	}


	template <>
	auto GetTriangle(const SolidVertex& v0, const SolidVertex& v1, const SolidVertex& v2, int num) 
	{
		return ColorEffect.gs(v0, v1, v2,num);
	}


	Mat4 orthographicPro;
	Mat4 perspectiveProjection;
	Mat4 ScaleMa;
	Mat4 TransMa;
	NDCScreenTransformer NSTmer;
	Camera camera;
	Graphics& gfx;


	TextureEffect<TexturePixelShader,WaveyVertexShader, SolidGeometryShader> TextureEffect;
	ColorEffect<ColorPixelShader,NormalVertexShader, SolidGeometryShader> ColorEffect;

	//TexturePixelShader	texPs;
	ColorPixelShader	colorPs;  
	WaveyVertexShader	waveyVs;  
	NormalVertexShader	normalVs; 
	SolidGeometryShader	solidGs;  





};

template<typename Vertex>
inline void Pipline::SeparateIndexesListAndVertex(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes, ShaderChoser choser)
{
	GoThroughVertexTransformation(IndexesList, vertexes);
}

template<typename Vertex>
inline void Pipline::GoThroughVertexTransformation(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes,ShaderChoser choser)
{

	std::vector<Vertex> verticesOut;
	verticesOut = vertexes;

	for (auto& v : verticesOut) {
		camera.cameraTransformation *= v.p;
	}





	AssembleTriangle(IndexesList, verticesOut);
}

template<typename Vertex>
inline void Pipline::AssembleTriangle(const std::vector<Indexes> IndexesList, const std::vector<Vertex>& vertexes)
{
	int i = 0;
	for (auto& indexes : IndexesList) {
		const auto& v0 = vertexes[indexes[0]];
		const auto& v1 = vertexes[indexes[1]];
		const auto& v2 = vertexes[indexes[2]];
		if ((Vec4::dot((v1.p - v0.p), (v2.p - v0.p)) * Vec4(v0.p)) < 0.f) {// do backface culling in world space or viewspace or you fucked up
			ProcessTriangle(GetVertex(v0), GetVertex(v1), GetVertex(v2),i);
		}
		i++;
	}
}








template<typename Vertex>
inline void Pipline::ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2,int i)
{



	PostProcessTriangle( GetTriangle(v0, v1, v2, i) );


}

template<typename Vertex>
inline void Pipline::PostProcessTriangle(_Triangle<Vertex> triangle)
{

	perspectiveProjection *= triangle.v0.p;
	perspectiveProjection *= triangle.v1.p;
	perspectiveProjection *= triangle.v2.p;


	//to NDC
	orthographicPro *= triangle.v0.p;
	orthographicPro *= triangle.v1.p;
	orthographicPro *= triangle.v2.p;



	NSTmer.Transform(triangle.v0);
	NSTmer.Transform(triangle.v1);
	NSTmer.Transform(triangle.v2);

	DrawTriangle(triangle);
}

template<typename Vertex>
inline void Pipline::DrawTriangle(const _Triangle<Vertex>& tr)
{
	//sort them so that v0 at top,v2 at the bottom 
	const Vertex* pv0 = &tr.v0;
	const Vertex* pv1 = &tr.v1;
	const Vertex* pv2 = &tr.v2;
	//sort
	if (pv0->p.y > pv1->p.y)  std::swap(pv0, pv1);
	if (pv0->p.y > pv2->p.y)  std::swap(pv0, pv2);
	if (pv1->p.y > pv2->p.y)  std::swap(pv1, pv2);


	if (pv0->p.y == pv1->p.y)  //flat top tri 
	{
		if (pv0->p.x > pv1->p.x) {
			std::swap(pv0, pv1);
		}

		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
	}

	else if (pv1->p.y == pv2->p.y)  //flat bottom tri 
	{
		if (pv1->p.x > pv2->p.x) {
			std::swap(pv1, pv2);
		}

		DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
	}

	else { //general tir

		const float alpha = (pv1->p.y - pv0->p.y) / (pv2->p.y - pv0->p.y);

		Vertex vi = *pv0 + (*pv2 - *pv0) * alpha;





		if (vi.p.x > pv1->p.x) //major right
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(*pv0, *pv1, vi);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle(*pv1, vi, *pv2);
		}
		else//major left
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(*pv0, vi, *pv1);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle(vi, *pv1, *pv2);
		}
	}


}

template<typename Vertex>
inline void Pipline::DrawFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	// v0--------v1
	//   \      /
	// v' \    / v''
	//      v2
	// z negtive

	if (v2.p.y < 0.f || v1.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	//run over rise ,avoid vertical fuck up
	float m0 = (v2.p.x - v0.p.x) / (v2.p.y - v0.p.y);
	float m1 = (v2.p.x - v1.p.x) / (v2.p.y - v1.p.y);


	//scanline start and end
	const int yStart = std::max((int)ceil(v0.p.y - 0.5f), 0);
	const int yEnd = std::min((int)ceil(v2.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive this last one
	Vertex vPrime;
	Vertex vPrimePrime;
	Vertex finalPoint;
	for (int y = yStart; y < yEnd; y++)
	{
		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v1.p.y) + v1.p.x;
		const int xStart = std::max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = std::min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));//exclusive

		for (int x = xStart; x < xEnd; x++) {
			float alpha = (float(y) + 0.5f - v0.p.y) / (v2.p.y - v0.p.y);
			vPrime = v0 + (v2 - v0) * alpha;
			vPrimePrime = v1 + (v2 - v1) * alpha;
			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			finalPoint = vPrime + (vPrimePrime - vPrime) * beta;
			float recipicalOfz = finalPoint.p.w;
			float z = (1.f / recipicalOfz);

			if (recipicalOfz < gfx.pzBuffer.At(x, y)) {
				gfx.pzBuffer.Store(x, y, recipicalOfz);
				gfx.PutPixel(x, y, GetColor(finalPoint * z));
			}
		}
	}


}

template<typename Vertex>
inline void Pipline::DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

	//          v0
	//         /  \ 
	//        /    \
	//       v1----v2


	if (v2.p.y < 0.f || v2.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	float m0 = (v0.p.x - v1.p.x) / (v0.p.y - v1.p.y);
	float m1 = (v0.p.x - v2.p.x) / (v0.p.y - v2.p.y);





	int yStart = std::max((int)ceil(v0.p.y - 0.5f), 0);
	int yEnd = std::min((int)ceil(v1.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive


	Vertex vPrime;
	Vertex vPrimePrime;
	Vertex finalPoint;
	for (int y = yStart; y < yEnd; y++) {
		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const int xStart = std::max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = std::min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));
		for (int x = xStart; x < xEnd; x++) {
			//          v0
			//         /  \ 
			//    v'  /    \ v''
			//       v1----v2

			float alpha = (float(y) + 0.5f - v0.p.y) / (v1.p.y - v0.p.y);

			vPrime = v0 + (v1 - v0) * alpha;
			vPrimePrime = v0 + (v2 - v0) * alpha;

			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			finalPoint = vPrime + (vPrimePrime - vPrime) * beta;


			float recipicalOfz = finalPoint.p.w;
			float z = 1.f / recipicalOfz;

			if (recipicalOfz < gfx.pzBuffer.At(x, y)) {
				gfx.pzBuffer.Store(x, y, recipicalOfz);
				gfx.PutPixel(x, y, GetColor(finalPoint * z));
			}
		}
	}
}



