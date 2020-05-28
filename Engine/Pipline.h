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

template <typename Effect>
class Pipline
{
public:

	Pipline(Graphics& GFX)
		:
		NSTmer((int)Graphics::ScreenWidth, (int)Graphics::ScreenHeight),
		gfx(GFX),
		camera({ 0.f,0.f,0.f }, { 0.f,0.f,-1.f }, { 0.f,1.f,0.f })
	{

		//(cubnoid space)orthographicSpce -> (NDC space [-1,1]^3)
		ScaleMa = Mat4::Identity();
		ScaleMa.elements[0][0] = 2.f / (Spectrum::r - Spectrum::l);
		ScaleMa.elements[1][1] = 2.f / (Spectrum::t - Spectrum::b);
		ScaleMa.elements[2][2] = 2.f / (Spectrum::n - Spectrum::f);
		TransMa = Mat4::Translation((Spectrum::r + Spectrum::l) / -2.f, (Spectrum::t + Spectrum::b) / -2.f, (Spectrum::n + Spectrum::f) / -2.f);
		orthographicPro = ScaleMa * TransMa;
		//worldspace to (cubnoid space)orthographicSpce
		Mat4 perspectiveToOrtho = {
			 Spectrum::n  ,   0.f        ,              0.f  ,  0.f,
			 0.f          ,  Spectrum::n ,              0.f  ,  0.f,
			 0.f          ,   0.f        ,     Spectrum::n + Spectrum::f,-Spectrum::n * Spectrum::f,
			 0.f          ,   0.f        ,              1.f  ,  0.f
		};
		perspectiveProjection = perspectiveToOrtho;
	}


	inline void Pipline::SeparateIndexesListAndVertex(const std::vector<Indexes>& IndexesList, const std::vector<typename Effect::Vs::vIn>& vertexes)
	{
		GoThroughCameraTransformation(IndexesList, vertexes);
	}
	inline void Pipline::GoThroughCameraTransformation(const std::vector<Indexes>& IndexesList, const std::vector<typename Effect::Vs::vIn>& vertexes)
	{
		std::vector<Effect::Vs::vIn> verticesOut;
		verticesOut = vertexes;

		for (auto& v : verticesOut) {
			camera.cameraTransformation *= v.p;
			camera.cameraTransformation *= v.normal;
		}


		Pointf4 temp0{ ps.originLightPosition.x,ps.originLightPosition.y,ps.originLightPosition.z};
		Pointf4 temp1 = (camera.cameraTransformation * temp0);
		
		ps.lightPosition.x = temp1.x;
		ps.lightPosition.y = temp1.y;
		ps.lightPosition.z = temp1.z;
		AssembleTriangle(IndexesList, verticesOut);

	}

	inline void Pipline::AssembleTriangle(const std::vector<Indexes> IndexesList, const std::vector<typename Effect::Vs::vIn>& vertexes)
	{
		int i = 0;
		for (auto& indexes : IndexesList) {
			const auto& v0 = vertexes[indexes[0]];
			const auto& v1 = vertexes[indexes[1]];
			const auto& v2 = vertexes[indexes[2]];
		if ((Vec4::cross((v1.p - v0.p), (v2.p - v0.p)) * Vec4(v0.p)) < 0.f) {// do backface culling in world space or (camera space)viewspace, or you fucked up
				ProcessTriangle(vs(v0), vs(v1), vs(v2), i);
			}
			i++;
		}
	}


	inline void Pipline::ProcessTriangle(const typename Effect::Vs::vOut& v0, const typename Effect::Vs::vOut& v1, const typename Effect::Vs::vOut& v2, int i)
	{
		PostProcessTriangle(gs(v0, v1, v2, i));
	}


	inline void Pipline::PostProcessTriangle(_Triangle<typename Effect::Gs::vOut> triangle)
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



	inline void Pipline::DrawTriangle(const _Triangle<typename Effect::Gs::vOut>& tr)
	{
		//sort them so that v0 at top,v2 at the bottom 
		const Effect::Gs::vOut* pv0 = &tr.v0;
		const Effect::Gs::vOut* pv1 = &tr.v1;
		const Effect::Gs::vOut* pv2 = &tr.v2;
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

			Effect::Gs::vOut vi = *pv0 + (*pv2 - *pv0) * alpha;





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

	inline void Pipline::DrawFlatTopTriangle(const typename Effect::Gs::vOut& v0, const typename  Effect::Gs::vOut& v1, const typename  Effect::Gs::vOut& v2)
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
		Effect::Gs::vOut vPrime;
		Effect::Gs::vOut vPrimePrime;
		Effect::Gs::vOut finalPoint;
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
					gfx.PutPixel(x, y, ps(finalPoint * z));
				}
			}
		}


	}



	inline void Pipline::DrawFlatBottomTriangle(const typename Effect::Gs::vOut& v0, const typename Effect::Gs::vOut& v1, const typename Effect::Gs::vOut& v2)
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


		Effect::Gs::vOut vPrime;
		Effect::Gs::vOut vPrimePrime;
		Effect::Gs::vOut finalPoint;
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
					gfx.PutPixel(x, y, ps(finalPoint * z));
				}
			}
		}
	}

	Mat4 orthographicPro;
	Mat4 perspectiveProjection;
	Mat4 ScaleMa;
	Mat4 TransMa;
	NDCScreenTransformer NSTmer;
	Camera camera;
	Graphics& gfx;
	typename Effect::Vs vs;
	typename Effect::Gs gs;
	typename Effect::Ps ps;


};
















