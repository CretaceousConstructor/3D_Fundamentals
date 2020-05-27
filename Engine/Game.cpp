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
	pipColorEffect(gfx)
{
	pipColorEffect.gs.BindColors({ Colors::Red,Colors::Green,Colors::Blue,Colors::Magenta,Colors::Yellow,Colors::Cyan });

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

	Ncube.update(dt);

	pipColorEffect.SeparateIndexesListAndVertex(Ncube.IndicesList, Ncube.VertexList);

}



void Game::ComposeFrame()
{
}

void Game::pipUpdate(float dt)
{
	if (wnd.kbd.KeyIsPressed('B')) {
		pipColorEffect.camera.moveu();
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		pipColorEffect.camera.moved();
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		pipColorEffect.camera.movel();
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		pipColorEffect.camera.mover();
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		pipColorEffect.camera.movef();
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		pipColorEffect.camera.moveb();
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		pipColorEffect.camera.RotateHorizontallyL();
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		pipColorEffect.camera.RotateHorizontallyR();
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		pipColorEffect.camera.RotateVerticallyB();
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		pipColorEffect.camera.RotateVerticallyU();
	}

}