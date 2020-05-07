#include "Cube.h"

void Cube::update(Keyboard& kbd)
{


	Mat4 temp = {

		1.f,       0.f,                         0.f,                   0.f,
		0.f,       1.f,                         0.f,                    0.f,
		0.f,       0.f,                         1.f  ,                  4.f,
		0.f,       0.f,                         0.f  ,                  1.f

	};
	RotationMat = {
		1.f,       0.f,                         0.f,                  0.f,
		0.f,     cos(rotateSpeedInRadius),-sin(rotateSpeedInRadius),  0.f,
		0.f,     sin(rotateSpeedInRadius), cos(rotateSpeedInRadius),  0.f,
		0.f,       0.f,                       0.f  ,                  1.f
	};

	TranslationMat = {
		1.f,       0.f,                         0.f,                    0.f,
		0.f,       1.f,                         0.f,                    0.f,
		0.f,       0.f,                         1.f  ,                  -4.f,
		0.f,       0.f,                         0.f  ,                  1.f
	};
	for (auto& Vertex : VertexList) {

		temp *= Vertex.p;
		RotationMat *= Vertex.p;
		TranslationMat *= Vertex.p;
	}
}
