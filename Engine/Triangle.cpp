#include "Triangle.h"

Triangle::Triangle(Pointf4 a, Pointf4 b, Pointf4 c)
{
	points.resize(3);
	points[0] = a;
	points[1] = b;
	points[2] = c;

}
Triangle::Triangle()
{
	points.resize(3);
}
//a -> b -> c -> a
void Triangle::GetDraw(Graphics& GFX, float focalLength)
{


	//float hightOffCenter0 = ((focalLength * points[0].z)) / (points[0].x + focalLength) *10.f;
	//float widthOffCenter0 = ((focalLength * points[0].y)) / (points[0].x + focalLength) * 10.f;


	//float hightOffCenter1 = ((focalLength * points[1].z)) / (points[1].x + focalLength) * 10.f;
	//float widthOffCenter1 = ((focalLength * points[1].y)) / (points[1].x + focalLength) * 10.f;

	//float hightOffCenter2 = ((focalLength * points[2].z)) / (points[2].x + focalLength) * 10.f;
	//float widthOffCenter2 = ((focalLength * points[2].y)) / (points[2].x + focalLength)*10.f;



	//GFX.DrawLine((int)(widthOffCenter0 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter0),
	//			 (int)(widthOffCenter1 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter1),
	//	         Colors::Magenta);

	//GFX.DrawLine((int)(widthOffCenter1 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter1),
	//			 (int)(widthOffCenter2 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter2),
	//			Colors::Magenta);


	//GFX.DrawLine((int)(widthOffCenter2 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter2),
	//			 (int)(widthOffCenter0 + ((float)(Graphics::ScreenWidth) / 2.f)), (int)(((float)(Graphics::ScreenHeight) / 2.f) - hightOffCenter0),
	//			Colors::Magenta);


	//GFX.DrawLine(points[2], points[0], Colors::Magenta);
	//
}
void Triangle::GetDraw(Graphics& GFX)
{


	GFX.DrawLine({ points[0].x ,points[0].y},  { points[1].x ,points[1].y }, Colors::Magenta);
	GFX.DrawLine({ points[1].x ,points[1].y }, { points[2].x ,points[2].y }, Colors::Magenta);
	GFX.DrawLine({ points[2].x ,points[2].y }, { points[0].x ,points[0].y }, Colors::Magenta);
}