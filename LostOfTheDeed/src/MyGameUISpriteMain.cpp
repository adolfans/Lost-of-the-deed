
#include "StdAfx.h"
#include "MyGameUISpriteMain.h"
//#include <time.h>
#include "MyGameMessage.h"
#include "MyGameMessageBox.h"


const int START = 1;
const int LOAD	= 2;
const int CONFIG = 3;
const int END	=4;
MyGameUISpriteMain::MyGameUISpriteMain(void):
			MyGameUISprite("img/nani.png", true, 20),
				c("img/c.png", false, 0,0.0, 0, 1024, 768),
				mainUI( "img/main2.png", true,19 ,0, 0, 1024, 768 ),
				//pC( &c ),
				backgroundAnimation( &c )
{
	MyGameUISprite::CreateRectangleWithIntKey( START, 0.0f, 0.0f, 1.0f, 0.25f, (1024-422), (768-326), 422.0f, 326.0f/4.0f );
	MyGameUISprite::CreateRectangleWithIntKey( LOAD, 0.0f, 0.25f, 1.0f, 0.5f, (1024-422), (768-326 + 326/4),422.0f, 326.0f/4.0f); 
	MyGameUISprite::CreateRectangleWithIntKey( CONFIG, 0.0f, 0.5f, 1.0f, 0.75f, (1024-422), (768-326 + 326/2),422.0f, 326.0f/4.0f); 
	MyGameUISprite::CreateRectangleWithIntKey( END, 0.0f, 0.75f, 1.0f, 1.0f, (1024-422), (768-326/4),422.0f, 326.0f/4.0f);

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
	if( !this->GetVisibility() )
		return;
	if( true == IfCursorInRect( START) )
		SetRectVisibility( START, true );
	if( true == IfCursorInRectClicked(START) )
	{
		SendMyMessage( newGame );
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
}