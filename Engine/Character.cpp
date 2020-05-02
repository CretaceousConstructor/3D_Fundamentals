#include "Character.h"
Character::Character(std::string Bmp, int _actionAccount, int _columnsOfAction, Vec2 p)
	:
	sp(Bmp),
	actionAccount(_actionAccount),
	columnsOfAction(_columnsOfAction),
	position(p)

{
	/*
		class rect {
			int top;
			int left;
			int right;
			int bottom;
		};
	*/
	chara = std::vector<texture::rect>(_actionAccount * _columnsOfAction);
	int width = sp.GetWidth();
	int height = sp.GetHeight();

	for (int i = 0; i < _actionAccount * _columnsOfAction; i++) {
		int t = (i / _columnsOfAction) * (height / _actionAccount);
		int l = (i % _columnsOfAction) * (width / _columnsOfAction);
		int r = l + width / _columnsOfAction; //not include 
		int b = t + height / _actionAccount; // not include
		chara[i] = texture::rect{ t,l,r,b };
	}

	itr = chara.begin();

}

void Character::update(float dt)
{
	if (iterFlag) {
		accumulationVar += dt;
		if (accumulationVar > holdTime) {
			accumulationVar = 0.f;
			++itr;
			iterAction();
		}
	}
	else {
		itr = (chara.begin() + iterCount * columnsOfAction);
	}
	iterFlag = false;
}



void Character::GetDraw(Graphics& GFX)
{

	//sp.GetDraw(GFX, *itr, position);
}

void Character::GetDraw(Graphics& GFX, float scaleFactor)
{

	//sp.GetDrawWithoutClipping(GFX, *itr, position, scaleFactor);

}



void Character::MoveU(float dt)
{
	iterCount = 2;  //2
	iterFlag = true;
	position += Vec2{ 0.f,-1.f } *speed;
}

void Character::MoveD(float dt)
{
	iterCount = 3;  //3
	iterFlag = true;
	position += Vec2{ 0.f,1.f } *speed;

}

void Character::MoveL(float dt)
{
	iterCount = 0;
	iterFlag = true;
	position += Vec2{ -1.f,0.f } *speed;

}

void Character::MoveR(float dt)
{
	iterCount = 1;  //1
	iterFlag = true;
	position += Vec2{ 1.f,0.f } *speed;

}

void Character::iterAction()
{
	/*
		int actionAccount;
		int columnsOfAction;
	*/
	//range :=  [index * columnsOfAction,index * columnsOfAction + columnsOfAction);

	if ( !((chara.begin() + iterCount * columnsOfAction) <= itr && itr < (chara.begin() + iterCount * columnsOfAction + columnsOfAction)) ) 
	{
		itr = (chara.begin() + iterCount * columnsOfAction);
	}


}
