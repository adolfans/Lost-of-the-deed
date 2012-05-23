#include "StdAfx.h"
#include "MyGameUISpriteMain.h"
//#include <time.h>
#include "MyGameMessage.h"
#include "MyGameNotify.h"


const int START = 1;
const int LOAD	= 2;
const int CONFIG = 3;
const int END	=4;
MyGameUISpriteMain::MyGameUISpriteMain(void):
			MyGameUISprite("nani.png", true, 20),
				c("c.png", false, 0,0.0, 0, 1024, 768),
				mainUI( "main2.png", true,19 ,0, 0, 1024, 768 ),
				//testItemBG( "choiceMenuBG.png",true,100, 0.0f, 0.0f, 1024, 768 ),
				offset(0.0f),
				mClock( offset, 0.005f, true, 100 ),
				lastTime( clock() ),
				currentTime( clock() ),
				pC( &c ),
				backgroundAnimation( pC )
{
	MyGameUISprite::CreateRectangleWithIntKey( START, 0.0f, 0.0f, 1.0f, 0.25f, (1024-422), (768-326), 422.0f, 326.0f/4.0f );
	MyGameUISprite::CreateRectangleWithIntKey( LOAD, 0.0f, 0.25f, 1.0f, 0.5f, (1024-422), (768-326 + 326/4),422.0f, 326.0f/4.0f); 
	MyGameUISprite::CreateRectangleWithIntKey( CONFIG, 0.0f, 0.5f, 1.0f, 0.75f, (1024-422), (768-326 + 326/2),422.0f, 326.0f/4.0f); 
	MyGameUISprite::CreateRectangleWithIntKey( END, 0.0f, 0.75f, 1.0f, 1.0f, (1024-422), (768-326/4),422.0f, 326.0f/4.0f);
	//testItemBG.SetVisibility( true );
	//mainUI.SetVisibility( false );
	lastTime = clock();
	for( int i = 0; i < 50; i ++ )
	{
		static int fr = 0;
		fr	= backgroundAnimation.createFrame( 100 );
		backgroundAnimation.setImgToFrame( fr, 0, i, 0 );
	}
	backgroundAnimation.appear();
}


MyGameUISpriteMain::~MyGameUISpriteMain(void)
{
}

void MyGameUISpriteMain::RenderUISprite()
{
	/*static {
	backgroundAnimation.appear();
	};*/
/*	currentTime = clock();

	offset = 0;
	if( currentTime - lastTime  > (CLOCKS_PER_SEC/100 ) && offset < 100.0f )//if time passed 1 second from last time updated on
	{
		printf("time:%d\n", currentTime - lastTime);
		offset+= 0.005*(currentTime - lastTime);
		lastTime = currentTime;
	}
*/
	if( !this->GetVisibility() )
		return;
	//c.MoveRect( 0, -100 + offset, 0 );
	if( true == IfCursorInRect( START) )
		SetRectVisibility( START, true );
	if( true == IfCursorInRectClicked(START) )
	{
		SendMyMessage( newGame );
		//MyGameNotify::MyGameNotifyBox("");
	}
	if( true ==IfCursorInRect(LOAD))
		SetRectVisibility( LOAD, true );
	if( true == IfCursorInRect(CONFIG) )
		SetRectVisibility( CONFIG, true );
	if( true ==IfCursorInRect(END))
		SetRectVisibility( END, true );
	MyGameUISprite::RenderUISprite();	//render the nani.png in main menu
	SetRectVisibility( LOAD, false );
	SetRectVisibility( START, false );
	SetRectVisibility( CONFIG, false );
	SetRectVisibility( END, false );
}

void MyGameUISpriteMain::SetVisibility(bool _visible)
{
	MyGameUISprite::SetVisibility( _visible );
	this->c.SetVisibility( _visible );
	this->mainUI.SetVisibility( _visible );
	if(!_visible)
		mClock.StopUpdateAndReset();
	else
		mClock.StartUpdate();
}