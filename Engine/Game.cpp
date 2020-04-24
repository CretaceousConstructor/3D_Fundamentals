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
	link("D:\\CS\\ChiliEngine\\Bmp\\images.bmp", 4, 5, {200.f,200.f}),
	house("D:\\CS\\ChiliEngine\\Bmp\\house.bmp", 1, 1, {200.f,200.f}),
	Grass("D:\\CS\\ChiliEngine\\Bmp\\grass.bmp", 1, 1, { 0.f,0.f })
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
	link.update(dt);
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		link.MoveU(dt);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		link.MoveD(dt);
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		link.MoveL(dt);
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		link.MoveR(dt);
	}
}

void Game::ComposeFrame()
{



	Grass.GetDraw(gfx);
	link.GetDraw(gfx,0.6f);
	house.GetDraw(gfx, 0.3f);
}