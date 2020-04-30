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
	trWorld0({ 0.f,0.5f ,-3.f }, { -0.5f,0.f,-3.f }, { 0.5f,0.f,-3.f }),
	trWorld1({ 0.f,0.f ,-3.0f }, { -2.f,2.f,-4.f }, { 2.f,2.f,-4.f }),
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


	////worldspace to viewspace
	//trView0.points[0] = camera.cameraTransformation * trWorld0.points[0];
	//trView0.points[1] = camera.cameraTransformation * trWorld0.points[1];
	//trView0.points[2] = camera.cameraTransformation * trWorld0.points[2];

	//worldspace to viewspace
	trView1.points[0] = camera.cameraTransformation * trWorld1.points[0];
	trView1.points[1] = camera.cameraTransformation * trWorld1.points[1];
	trView1.points[2] = camera.cameraTransformation * trWorld1.points[2];



	//backface culling
	if (Vec4::dot((trView1.points[1] - trView1.points[0]), (trView1.points[2] - trView1.points[1])) * trView1.points[0] > 0.f) {
		draw = true;
	}
	else {
		draw = false;
	}



	////spectrum to cubnoid
	//trCubnoid0.points[0] = camera.perspectiveProjection * trView0.points[0];
	//trCubnoid0.points[1] = camera.perspectiveProjection * trView0.points[1];
	//trCubnoid0.points[2] = camera.perspectiveProjection * trView0.points[2];


	trCubnoid1.points[0] = camera.perspectiveProjection * trView1.points[0];
	trCubnoid1.points[1] = camera.perspectiveProjection * trView1.points[1];
	trCubnoid1.points[2] = camera.perspectiveProjection * trView1.points[2];


	//
	////preserve z value in w and "actually" do perspectiveProjection to x and y,
	//	Mat4 recoverMat0 = Mat4::Identity() * (1.f / trCubnoid0.points[0].w);
	//	recoverMat0.elements[3][3] = 1.f;
	//	Mat4 recoverMat1 = Mat4::Identity() * (1.f / trCubnoid0.points[1].w);
	//	recoverMat1.elements[3][3] = 1.f;
	//	Mat4 recoverMat2 = Mat4::Identity() * (1.f / trCubnoid0.points[2].w);
	//	recoverMat2.elements[3][3] = 1.f;

	// trCubnoid0.points[0] = (recoverMat0) * trCubnoid0.points[0];
	// trCubnoid0.points[1] = (recoverMat1) * trCubnoid0.points[1];
	// trCubnoid0.points[2] = (recoverMat2) * trCubnoid0.points[2];





	 //preserve z value in w and "actually" do perspectiveProjection to x and y,
	/*Mat4  recoverMat0 = Mat4::Identity() * (1.f / trCubnoid1.points[0].w);
	recoverMat0.elements[3][3] = 1.f;
	Mat4   recoverMat1 = Mat4::Identity() * (1.f / trCubnoid1.points[1].w);
	recoverMat1.elements[3][3] = 1.f;
	Mat4   recoverMat2 = Mat4::Identity() * (1.f / trCubnoid1.points[2].w);
	recoverMat2.elements[3][3] = 1.f;

	trCubnoid1.points[0] = (recoverMat0)*trCubnoid1.points[0];
	trCubnoid1.points[1] = (recoverMat1)*trCubnoid1.points[1];
	trCubnoid1.points[2] = (recoverMat2)*trCubnoid1.points[2];*/

	//cubnoid to NDC
	trNDC1.points[0] = camera.orthographicPro * trCubnoid1.points[0];
	trNDC1.points[1] = camera.orthographicPro * trCubnoid1.points[1];
	trNDC1.points[2] = camera.orthographicPro * trCubnoid1.points[2];



		//
		//preserve z value in w and "actually" do perspectiveProjection to x and y,
		Mat4 recoverMat0 = Mat4::Identity() * (1.f / trCubnoid1.points[0].w);
		recoverMat0.elements[3][3] = 1.f;
		Mat4 recoverMat1 = Mat4::Identity() * (1.f / trCubnoid1.points[1].w);
		recoverMat1.elements[3][3] = 1.f;
		Mat4 recoverMat2 = Mat4::Identity() * (1.f / trCubnoid1.points[2].w);
		recoverMat2.elements[3][3] = 1.f;

		trNDC1.points[0] = (recoverMat0)*trNDC1.points[0];
		trNDC1.points[1] = (recoverMat1)*trNDC1.points[1];
		trNDC1.points[2] = (recoverMat2)*trNDC1.points[2];

	
		//trNDC1.points[0] = wPreserveMultiplication(camera.TransMa, trCubnoid1.points[0]);
		//trNDC1.points[1] = wPreserveMultiplication(camera.TransMa, trCubnoid1.points[1]);
		//trNDC1.points[2] = wPreserveMultiplication(camera.TransMa, trCubnoid1.points[2]);
	
	
		//trNDC1.points[0] = camera.ScaleMa * trNDC1.points[0];
		//trNDC1.points[1] = camera.ScaleMa * trNDC1.points[1];
		//trNDC1.points[2] = camera.ScaleMa * trNDC1.points[2];
	
	
	
		//NSTmer.Transform(trNDC0.points[0]);
		//NSTmer.Transform(trNDC0.points[1]);
		//NSTmer.Transform(trNDC0.points[2]);
	
		NSTmer.Transform(trNDC1.points[0]);
		NSTmer.Transform(trNDC1.points[1]);
		NSTmer.Transform(trNDC1.points[2]);

}

void Game::ComposeFrame()
{

	//trNDC.GetDraw(gfx);


	gfx.DrawTriangle(trNDC1.points[0], trNDC1.points[1], trNDC1.points[2], Colors::Red);


	//gfx.DrawTriangle(trNDC0.points[0], trNDC0.points[1], trNDC0.points[2],Colors::Green);

}