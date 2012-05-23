#include "StdAfx.h"
#include "MyGameUISpriteProcess.h"


MyGameUISpriteProcess::MyGameUISpriteProcess(void)
	:MyGameUISprite("dialogUI.png", true,0, 0, 1024, 768, 21)
{
//	MyGameUISprite dialogUI("dialogUI.png", 0, 0, 1024, 768, 12)
//	MyGameUISprite::CreateRectangle( "dialogRect", 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1024.0f, 768.0f, 25.0f);
}


MyGameUISpriteProcess::~MyGameUISpriteProcess(void)
{
}
