#include "StdAfx.h"
#include "MyGameDialogChoice.h"


MyGameDialogChoice::MyGameDialogChoice( int _height, int _width, int _weight, string _fontName, bool _italic )
	::MyGameUIText( _height, _width, _weight, _fontName, _italic )
{
}


MyGameDialogChoice::~MyGameDialogChoice(void)
{
}

void MyGameDialogChoice::RenderText()
{
//	static bool firstText = true;

	//this->DrawUIText( text.c_str(),
	//					count, 
	//					pDestRect,
	//					format,
	//					color );

}