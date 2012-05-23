#pragma once
#include "MyGameUISprite.h"
#include "MyGameClock.h"
#include "MyGameUIAnimation.h"
#include <time.h>
class MyGameUISpriteMain :
	public MyGameUISprite
{
private:
	MyGameUISprite c;
	MyGameUISprite* pC;
	MyGameUISprite mainUI;
	MyGameUIAnimation backgroundAnimation;
	//MyGameUISprite testItemBG;
	clock_t currentTime;
	clock_t lastTime;
	float offset;
	MyGameClock	mClock;
public:
	MyGameUISpriteMain(void);
	~MyGameUISpriteMain(void);
	virtual void RenderUISprite();
	void		SetVisibility(bool);
};

