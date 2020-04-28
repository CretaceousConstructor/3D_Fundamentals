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
#include "Mat2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	trWorld({0.f,0.5 ,-20.f}, {-0.5f,0.f,-20.f}, {0.5f,0.f,-20.f}),
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

	if (wnd.kbd.KeyIsPressed('F')) {
		camera.moveu();
	}
	if (wnd.kbd.KeyIsPressed('G')) {
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


	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		camera.RotateHorizontally();
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		camera.RotateVertically();
	}



	//worldspace to viewspace
	trView.points[0] = camera.cameraTransformation * trWorld.points[0];
	trView.points[1] = camera.cameraTransformation * trWorld.points[1];
	trView.points[2] = camera.cameraTransformation * trWorld.points[2];



	//spectrum to cubnoid
	trCubnoid.points[0] = camera.perspectiveProjection * trView.points[0];
	trCubnoid.points[1] = camera.perspectiveProjection * trView.points[1];
	trCubnoid.points[2] = camera.perspectiveProjection * trView.points[2];

	//recover x , y cordinates
	trCubnoid.points[0] = (Mat4::Identity() * (1.f / trCubnoid.points[0].w)) * trCubnoid.points[0];
	trCubnoid.points[1] = (Mat4::Identity() * (1.f / trCubnoid.points[1].w)) * trCubnoid.points[1];
	trCubnoid.points[2] = (Mat4::Identity() * (1.f / trCubnoid.points[2].w)) * trCubnoid.points[2];

	//cubnoid to NDC
	trNDC.points[0] = camera.orthographicPro * trCubnoid.points[0];
	trNDC.points[1] = camera.orthographicPro * trCubnoid.points[1];
	trNDC.points[2] = camera.orthographicPro * trCubnoid.points[2];

	//NDC to Screen
	NSTmer.Transform(trNDC.points[0]);
	NSTmer.Transform(trNDC.points[1]); 
	NSTmer.Transform(trNDC.points[2]);

}

void Game::ComposeFrame()
{
	
	trNDC.GetDraw(gfx);

}