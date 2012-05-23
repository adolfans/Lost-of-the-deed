#pragma once
#include "mygamedecoration.h"
#include "MyGameUISprite.h"
#include "MyGameUIText.h"
#include "MyGameUIAnimation.h"
class MyGameMessageBox :
	public MyGameDecoration
{
private:
	MyGameUISprite no1;
	MyGameUISprite* pNo1;
	MyGameUIAnimation myAnimation;
	float		numToDraw;
	bool		visible;
	void		SetVisible(bool _visible)
	{ visible = _visible; }
	bool		closing;
	MyGameUIText notifyText;
	int			count;
	MyGameMessageBox(void);
	static MyGameMessageBox* gameNotifyInstance;
public:
	static MyGameMessageBox* InitGameMessageBox();
	virtual void update();
	void	SetNotifyText( const char* );
	~MyGameMessageBox(void);
	static void	MyGameNotifyBox( const char* );
};

