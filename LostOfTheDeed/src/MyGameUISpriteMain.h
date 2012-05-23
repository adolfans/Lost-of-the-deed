/************************
this class needs modification
it shouldn't be inherited from MyGameUISprite
*************************/

#pragma once
#include "MyGameUISprite.h"
#include "MyGameUIAnimation.h"
#include <time.h>
class MyGameUISpriteMain :
	public MyGameUISprite
{
private:
	MyGameUISprite c;
	//MyGameUISprite* pC;
	MyGameUISprite mainUI;
	MyGameUIAnimation backgroundAnimation;
public:
	MyGameUISpriteMain(void);
	~MyGameUISpriteMain(void);
	virtual void RenderUISprite();
	void		SetVisibility(bool);
};

