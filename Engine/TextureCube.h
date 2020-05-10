#pragma once
#include "Cube.h"
class TextureCube {
public:
	TextureCube()
		:
		IndicesList(Cube::GetTextureIndicesList(side)),
		VertexList(Cube::GetTextureVertexList(side))

	{
		//model space to world space
		TranslationMat = {
			1.f,         0.f,         0.f,               0.f,
			0.f,         1.f,         0.f,               0.f,
			0.f,         0.f,         1.f  ,             -5.f,
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
	std::vector<TextureVertex>  VertexList;
	static constexpr float side = 0.4f;
	static constexpr float rotateSpeedInRadius = -1.f;



};