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
	pip(gfx)
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
	pipUpdate(dt);
	Ccube.update(dt);
	Tcube.update(dt);
	Ncube.update(dt);

	//pip.SeparateIndexesListAndVertex(Ccube.IndicesList, Ccube.VertexList);
	//pip.SeparateIndexesListAndVertex(Tcube.IndicesList, Tcube.VertexList);

	//pip.SeparateIndexesListAndVertex(WaveyPlane::GetTextureIndicesList(), WaveyPlane::GetTextureVertexList(0.5f));

	pip.SeparateIndexesListAndVertex(Ncube.IndicesList, Ncube.VertexList);

}



void Game::ComposeFrame()
{
}

void Game::pipUpdate(float dt)
{
	if (wnd.kbd.KeyIsPressed('B')) {
		pip.camera.moveu();
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		pip.camera.moved();
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		pip.camera.movel();
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		pip.camera.mover();
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		pip.camera.movef();
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		pip.camera.moveb();
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		pip.camera.RotateHorizontallyL();
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		pip.camera.RotateHorizontallyR();
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		pip.camera.RotateVerticallyB();
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		pip.camera.RotateVerticallyU();
	}

	pip.TextureEffect.vs.SetTime(dt);



}