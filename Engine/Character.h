#pragma once
#include <string>
#include <vector>
#include "Colors.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Sprite.h"

class Character
{
public:
	Character(std::string Bmp,int actionAccount,int columnsOfAction,Vec2 p);//load all frames from one bmp file
	void update(float dt);
	void GetDraw(Graphics& GFX);
	void GetDraw(Graphics& GFX, float scaleFactor);

	void MoveU(float dt);
	void MoveD(float dt);
	void MoveL(float dt);
	void MoveR(float dt);
private:
	void iterAction();

	int actionAccount;
	int columnsOfAction;
	std::vector<texture::rect> chara;
	texture sp;
	std::vector<texture::rect>::iterator itr;
	float holdTime = 0.1f;
	float accumulationVar = 0.f;
	Color BackGroundColor = Colors::Magenta;
	Vec2 position;
	bool iterFlag = false;
	int iterCount = 0; 
	float speed = 6.f;
};

