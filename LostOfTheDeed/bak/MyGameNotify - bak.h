#pragma once
#include "mygamedecoration.h"
#include "MyGameUISprite.h"
//#include "MyGameClock.h"
#include "MyGameUIText.h"
#include "MyGameUIAnimation.h"
class MyGameNotify :
	public MyGameDecoration
{
private:
	MyGameUISprite no1;
	//MyGameUISprite no2;
	//MyGameUISprite no3;
	//MyGameUISprite no4;
	//MyGameUISprite no5;
	//MyGameUISprite no6;
	//MyGameUISprite no7;
	//MyGameUISprite no8;
	MyGameUISprite* pNo1;
	MyGameUIAnimation myAnimation;
	float		numToDraw;
	//MyGameClock picNumClock;
	bool		visible;
	void		SetVisible(bool _visible)
	{ visible = _visible; }
	bool		closing;
	MyGameUIText notifyText;
	int			count;
	MyGameNotify(void);
	static MyGameNotify* gameNotifyInstance;
public:
	static MyGameNotify* InitGameNotify();
	virtual void update();
	void	SetNotifyText( const char* );
	~MyGameNotify(void);
	static void	MyGameNotifyBox( const char* );
};

