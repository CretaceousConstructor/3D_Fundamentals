#include "TextureCube.h"

void TextureCube::update(float dt)
{
	Mat4 temp = {

		1.f,       0.f,                         0.f,                   0.f,
		0.f,       1.f,                         0.f,                    0.f,
		0.f,       0.f,                         1.f  ,                  5.f,
		0.f,       0.f,                         0.f  ,                  1.f

	};
	RotationMat = {
		1.f,       0.f,                         0.f,                  0.f,
		0.f,     cos(dt * rotateSpeedInRadius),-sin(dt * rotateSpeedInRadius),  0.f,
		0.f,     sin(dt * rotateSpeedInRadius), cos(dt * rotateSpeedInRadius),  0.f,
		0.f,       0.f,                       0.f  ,                  1.f
	};

	TranslationMat = {
		1.f,       0.f,                         0.f,                    0.f,
		0.f,       1.f,                         0.f,                    0.f,
		0.f,       0.f,                         1.f  ,                  -5.f,
		0.f,       0.f,                         0.f  ,                  1.f
	};
	for (auto& Vertex : VertexList) {
		temp *= Vertex.p;
		RotationMat *= Vertex.p;
		TranslationMat *= Vertex.p;
	}
}
