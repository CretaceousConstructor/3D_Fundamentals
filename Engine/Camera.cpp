#include "Camera.h"



Camera::Camera(Pointf4 wl, Vec4 la, Vec4 lu)
	:
	worldLocation(wl),
	lookAt(la),
	lookUp(lu)
{

	//worldSpace -> cameraSpace
	lookAt.Normalize();
	lookUp.Normalize();
	Mat4 viewTranslation = Mat4::Translation(-wl.x, -wl.y, -wl.z);
	Vec4 gDott = Vec4::cross(lookAt, lookUp);
	Mat4 viewRotation = {
		  gDott.x  ,   gDott.y ,  gDott.z   ,0.f,
		 lookUp.x  ,  lookUp.y ,  lookUp.z  ,0.f,
		-lookAt.x  , -lookAt.y ,  -lookAt.z ,0.f,
		 0.f       ,  0.f     ,  0.f       ,1.f
	};
	cameraTransformation = viewRotation * viewTranslation;

}

void Camera::Update()
{
	Mat4 viewTranslation = Mat4::Translation(-worldLocation.x, -worldLocation.y, -worldLocation.z);
	Vec4 gDott = Vec4::cross(lookAt, lookUp);
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
	Vec4 axis = Vec4::cross(lookAt, lookUp);
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt, rotateSpeed, axis);
	lookUp = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookUp, rotateSpeed, axis);
	Update();

}
void Camera::RotateVerticallyB()
{
	Vec4 axis = Vec4::cross(lookAt, lookUp);
	lookAt = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookAt,-rotateSpeed, axis);
	lookUp = Mat::RotateAroundArbitraryVectorStartAtOrigin(lookUp,-rotateSpeed, axis);
	Update();

}


void Camera::moveu()
{


	worldLocation += ( lookUp * speed);
	Update();
}

void Camera::moved()
{
	worldLocation += (-lookUp * speed);
	Update();
}




void Camera::movel()
{
	worldLocation += (-(Vec4::cross(lookAt, lookUp)) * speed);
	Update();
}





void Camera::mover()
{
	worldLocation += ((Vec4::cross(lookAt, lookUp)) * speed);
	Update();
}




void Camera::movef()
{
	worldLocation  += (lookAt * speed);
	Update();
}


void Camera::moveb()
{
	
	worldLocation += (-lookAt * speed);
	Update();
}