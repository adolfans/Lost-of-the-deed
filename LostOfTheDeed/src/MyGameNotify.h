#pragma once
#include "mygamedecoration.h"
#include "MyGameUISprite.h"
#include "MyGameUIAnimation.h"
#include "MyGameUIText.h"

class MyGameNotify :
	public MyGameDecoration
{
private:
	MyGameUISprite notifyBG;
	//MyGameUISprite* pNotifyBG;
	MyGameUISprite testTextSprite;
	MyGameUIAnimation notifyAni;
	MyGameTextBase	notifyText;
	clock_t			timePassed;
	
	MyGameNotify(void);
	static MyGameNotify* pNotifyInstance;
public:
	static MyGameNotify* InitNotifyBox();
	static void MyGameNotification(const char* _notifyText);
	~MyGameNotify(void);
	void update();
};

