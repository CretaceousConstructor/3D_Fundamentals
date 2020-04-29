#include "Camera.h"



Camera::Camera(Pointf4 wl, Vec4 la, Vec4 lu)
	:
	worldLocation(wl),
	lookAt(la),
	lookUp(lu)
{

	//(cubnoid space)orthographicSpce -> (NDC space [-1,1]^3)
	Mat4 ScaleMa = Mat4::Identity();
	ScaleMa.elements[0][0] = 2.f / (Spectrum::r - Spectrum::l);
	ScaleMa.elements[1][1] = 2.f / (Spectrum::t - Spectrum::b);
	ScaleMa.elements[2][2] = 2.f / (Spectrum::n - Spectrum::f);
	orthographicPro = ScaleMa * Mat4::Translation((Spectrum::r + Spectrum::l) / -2.f, (Spectrum::t + Spectrum::b) / -2.f, (Spectrum::n + Spectrum::f) / -2.f);


	//worldSpace -> cameraSpace
	lookAt.Normalize();
	lookUp.Normalize();
	Mat4 viewTranslation = Mat4::Translation(-wl.x, -wl.y, -wl.z);
	Vec4 gDott = Vec4::dot(lookAt, lookUp);
	Mat4 viewRotation = {
		  gDott.x  ,   gDott.y ,  gDott.z   ,0.f,
		 lookUp.x  ,  lookUp.y ,  lookUp.z  ,0.f,
		-lookAt.x  , -lookAt.y ,  -lookAt.z ,0.f,
		 0.f       ,  0.f     ,  0.f       ,1.f
	};
	cameraTransformation = viewRotation * viewTranslation;






	Mat4 perspectiveToOrtho = {

		 Spectrum::n  ,   0.f        ,              0.f  ,  0.f,
		 0.f          ,  Spectrum::n ,              0.f  ,  0.f,
		 0.f          ,   0.f        ,     Spectrum::n+Spectrum::f,-Spectrum::n * Spectrum::f,
		 0.f          ,   0.f        ,              1.f  ,  0.f
	};
	perspectiveProjection = perspectiveToOrtho;






}

void Camera::Update()
{
	Mat4 viewTranslation = Mat4::Translation(-worldLocation.x, -worldLocation.y, -worldLocation.z);
	Vec4 gDott = Vec4::dot(lookAt, lookUp);
	Mat4 viewRotation = {
		  gDott.x  ,   gDott.y ,  gDott.z   ,0.f,
		 lookUp.x  ,  lookUp.y ,  lookUp.z  ,0.f,
		-lookAt.x  , -lookAt.y ,  -lookAt.z ,0.f,
		 0.f       ,  0.f     ,  0.f        ,1.f
	};

	cameraTransformation = viewRotation * viewTranslation;
}

void Camera::RotateHorizontallyL()
{
	//lookAt rotate around lookUp
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt, rotateSpeed,lookUp);
	Update();
}
void Camera::RotateHorizontallyR()
{
	//lookAt rotate around lookUp
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt, -rotateSpeed, lookUp);
	Update();
}

void Camera::RotateVerticallyU()
{
	Vec4 axis = Vec4::dot(lookAt, lookUp);
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt, rotateSpeed, axis);
	lookUp = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookUp, rotateSpeed, axis);
	Update();

}
void Camera::RotateVerticallyB()
{
	Vec4 axis = Vec4::dot(lookAt, lookUp);
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt,-rotateSpeed, axis);
	lookUp = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookUp,-rotateSpeed, axis);
	Update();

}


void Camera::moveu()
{
	worldLocation.y += speed;
	Update();
}

void Camera::moved()
{
	worldLocation.y-= speed;
	Update();
}
void Camera::movel()
{
	worldLocation.x -= speed;
	Update();
}
void Camera::mover()
{
	worldLocation.x += speed;
	Update();
}

void Camera::movef()
{
	worldLocation.z -= speed;
	Update();

}
void Camera::moveb()
{
	worldLocation.z += speed;
	Update();
}