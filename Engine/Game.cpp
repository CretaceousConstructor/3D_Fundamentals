/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	texture1("D:\\CS\\ChiliEngine\\Bmp\\tex.bmp"),
	trWorld1({ Vertex{Pointf4{ 0.f,0.f ,-3.0f },Vec2{ 0.f,0.f }} , Vertex{ Pointf4{ -2.f,2.f ,-2.f },Vec2{ 0.f,1.f } } , Vertex{ Pointf4{ 2.f,2.f ,-6.0f },Vec2{ 1.f,0.f } } }, { 0,2,1 }, texture1),
	//                 a                                                              b                                               c
	camera({ 0.f,0.f,0.f }, { 0.f,0.f,-1.f }, { 0.f,1.f,0.f })
{


}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = clock.Mark();

	if (wnd.kbd.KeyIsPressed('B')) {
		camera.moveu();
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		camera.moved();
	}

	if (wnd.kbd.KeyIsPressed('A')) {
		camera.movel();
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		camera.mover();
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		camera.movef();
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		camera.moveb();
	}


	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		camera.RotateHorizontallyL();
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		camera.RotateHorizontallyR();
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		camera.RotateVerticallyB();
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		camera.RotateVerticallyU();

	}

















	//TO DO:objectspace to worldspace


	trPiplined = trWorld1;


	//worldspace to viewspace
	//worldspace to viewspace
	trPiplined.vertexs[0].p = camera.cameraTransformation * trPiplined.vertexs[0].p;
	trPiplined.vertexs[1].p = camera.cameraTransformation * trPiplined.vertexs[1].p;
	trPiplined.vertexs[2].p = camera.cameraTransformation * trPiplined.vertexs[2].p;



	//backface culling
	if (Vec4::dot((trPiplined.vertexs[1].p - trPiplined.vertexs[1].p), (trPiplined.vertexs[2].p - trPiplined.vertexs[1].p )) * Vec4(trPiplined.vertexs[0].p) > 0.f) {
		draw = true;
	}
	else {
		draw = false;
	}


	//spectrum to cubnoid
	trPiplined.vertexs[0].p = camera.perspectiveProjection * trPiplined.vertexs[0].p;
	trPiplined.vertexs[1].p = camera.perspectiveProjection * trPiplined.vertexs[1].p;
	trPiplined.vertexs[2].p = camera.perspectiveProjection * trPiplined.vertexs[2].p;


	//cubnoid to NDC
	trPiplined.vertexs[0].p = camera.orthographicPro * trPiplined.vertexs[0].p;
	trPiplined.vertexs[1].p = camera.orthographicPro * trPiplined.vertexs[1].p;
	trPiplined.vertexs[2].p = camera.orthographicPro * trPiplined.vertexs[2].p;


	//preserve 1/z value in w and "actually" do perspectiveProjection to x and y,
	//1/z will be used later to do perspective correct interpolation
	float tempZricapical = 1.f / trPiplined.vertexs[0].p.w;
	trPiplined.vertexs[0] *= tempZricapical;
	trPiplined.vertexs[0].p.w = tempZricapical;

	tempZricapical = 1.f / trPiplined.vertexs[1].p.w;
	trPiplined.vertexs[1] *= tempZricapical;
	trPiplined.vertexs[1].p.w = tempZricapical;

	tempZricapical = 1.f / trPiplined.vertexs[2].p.w;
	trPiplined.vertexs[2] *= (1.f/trPiplined.vertexs[2].p.w);
	trPiplined.vertexs[2].p.w = tempZricapical;



	NSTmer.Transform(trPiplined.vertexs[0].p);
	NSTmer.Transform(trPiplined.vertexs[1].p);
	NSTmer.Transform(trPiplined.vertexs[2].p);



}

void Game::ComposeFrame()
{

	//if (draw) {
		//gfx.DrawTriangle(trNDC1.points[0], trNDC1.points[1], trNDC1.points[2], Colors::Red);
		gfx.DrawTriangle(trPiplined);
	//}



}