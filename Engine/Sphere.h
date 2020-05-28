#pragma once


#include "Vec4.h"
#include "Mat4.h"
#include <vector>
#include "IndexList.h"
#include "PointLightEffect.h"
#include "PerPixelEffect.h"
class Sphere {

public:
	Sphere() = delete;
	Sphere(float radius, int longiDiv, int latiDvi)
	{


		const Pointf4 base = { 0.f,radius,0.f };

		const float latiAngle = PI / (float)latiDvi;
		const float longiAngle = (2.f * PI) / (float)longiDiv;


		const auto calcIdx = [latiDvi, longiDiv](int iLat, int iLong) {
			return (iLat * longiDiv + iLong);
		};

		//vertex gener
		for (int iLat = 1; iLat < latiDvi; ++iLat) {

			const Pointf4 latBase = Mat4::RotationAroundAxisX(iLat * latiAngle) * base;

			for (int iLong = 0; iLong < latiDvi; ++iLong)
			{
				Pointf4 ilRotated = Mat4::RotationAroundAxisY(iLong * longiAngle) * latBase;

				Vec4 nor = Vec4{ ilRotated.x,ilRotated.y,ilRotated.z };
				Vec4 shit = nor.Normalize();

				ilRotated.z = ilRotated.z - zTraslation;


				vertexList.emplace_back(ilRotated, shit);
			}

		}

		//indices gener
		for (int iLat = 0; iLat < latiDvi - 2; ++iLat) {


			for (int iLong = 0; iLong < longiDiv - 1; ++iLong) {

				indicesList.emplace_back(Indexes{ (size_t)calcIdx(iLat,iLong) ,(size_t)calcIdx(iLat + 1,iLong),(size_t)calcIdx(iLat,iLong + 1) });
				indicesList.emplace_back(Indexes{ (size_t)calcIdx(iLat   ,iLong + 1),(size_t)calcIdx(iLat + 1,iLong),(size_t)calcIdx(iLat + 1 ,iLong + 1) });
							}


			indicesList.emplace_back(Indexes{ (size_t)calcIdx(iLat,longiDiv - 1) ,(size_t)calcIdx(iLat + 1,longiDiv - 1),(size_t)calcIdx(iLat,0) });
			indicesList.emplace_back(Indexes{ (size_t)calcIdx(iLat,0) ,(size_t)calcIdx(iLat + 1,longiDiv - 1),(size_t)calcIdx(iLat + 1,0) });


		}



		Pointf4 translatedBase{ base.x,base.y,base.z - zTraslation };


		const auto iNorthPole = vertexList.size();
		vertexList.emplace_back(PerPixelEffect::Vs::vIn{ translatedBase ,Vec4{base.x,base.y,base.z }.GetNormalized() });
		const auto iSouthPole = vertexList.size();
		vertexList.emplace_back(PerPixelEffect::Vs::vIn{ Pointf4{translatedBase.x,-translatedBase.y,translatedBase.z} , Vec4{base.x,-base.y,base.z}.GetNormalized() });

		for (int iLong = 0; iLong < longiDiv - 1; iLong++) {
			//north
			indicesList.emplace_back(Indexes{ iNorthPole ,(size_t)calcIdx(0,iLong),(size_t)calcIdx(0,iLong + 1) });
			//south
			indicesList.emplace_back(Indexes{ (size_t)calcIdx(latiDvi - 2,iLong + 1) ,(size_t)calcIdx(latiDvi - 2,iLong),iSouthPole });
		}




		//north last piece
		indicesList.emplace_back(Indexes{ iNorthPole ,(size_t)calcIdx(0,longiDiv - 1),(size_t)calcIdx(0,0) });
		//south last piece
		indicesList.emplace_back(Indexes{ iSouthPole,(size_t)calcIdx(latiDvi - 2,0) ,(size_t)calcIdx(latiDvi - 2,longiDiv - 1) });

	}







	std::vector<typename PerPixelEffect::Vs::vIn> vertexList;
	std::vector<Indexes> indicesList;


	static constexpr float zTraslation = 4.5f;


};