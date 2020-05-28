#pragma once
#include "Cube.h"
#include "ColorEffect.h"
#include "PerPixelEffect.h"
class SolidCube {
public:
	SolidCube()
		:
		IndicesList(Cube::GetLishtIndicesList(side)),
		VertexList(Cube::GetLightVertexList(side))

	{
		//model space to world space
		TranslationMat = {
			1.f,         0.f,         0.f,               0.f,
			0.f,         1.f,         0.f,               0.f,
			0.f,         0.f,         1.f  ,             -4.f,
			0.f,         0.f,         0.f  ,             1.f
		};
		for (auto& Vertex : VertexList) {
			TranslationMat *= Vertex.p;
			TranslationMat *= Vertex.normal;
		}


	}

	void update(float dt);
	Mat4 RotationMat = Mat4::Identity();
	Mat4 TranslationMat = Mat4::Identity();

	std::vector<Indexes> IndicesList;
	std::vector<typename PerPixelEffect::Vs::vIn>  VertexList;
	static constexpr float side = 0.5f;
	static constexpr float rotateSpeedInRadius = 2.f;



};