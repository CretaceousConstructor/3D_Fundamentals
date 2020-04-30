#pragma once
#include "Mat4.h"

#include "Vec4.h"
#include "Cubnoid.h"
#include "Spectrum.h"
class Camera
{
public:
	Camera(Pointf4 wl, Vec4 lookAt,Vec4 lookUp);
	Camera() = delete;
	void Update();
	void RotateHorizontallyL();
	void RotateHorizontallyR();
	void RotateVerticallyU();
	void RotateVerticallyB();
	void moveu();
	void moved();
	void movel();
	void mover();
	void movef();
	void moveb();
	Mat4 orthographicPro;
	Mat4 cameraTransformation;
	Mat4 perspectiveProjection;


	Pointf4 worldLocation;
	Vec4 lookAt;
	Vec4 lookUp;
	float speed = 0.1f;
	float rotateSpeed = 0.05f;
};

