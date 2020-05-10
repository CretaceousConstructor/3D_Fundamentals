#pragma once
#include "Cube.h"

class ColorCube {
public:
	ColorCube()
		:
		IndicesList(Cube::GetColorIndicesList(side)),
		VertexList(Cube::GetColorVertexList(side))

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
		}


	}

	void update(float dt);
	Mat4 RotationMat = Mat4::Identity();
	Mat4 TranslationMat = Mat4::Identity();

	std::vector<Indexes> IndicesList;
	std::vector<ColorVertex>  VertexList;
	static constexpr float side = 0.5f;
	static constexpr float rotateSpeedInRadius = 0.2f;



};