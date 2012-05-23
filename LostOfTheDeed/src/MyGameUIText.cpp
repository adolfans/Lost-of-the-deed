#include "StdAfx.h"
#include "MyGameUIText.h"
#include "MyGame3DDevice.h"
//#include <string>
//using std::wstring;
vector<MyGameUIText*>	MyGameUIText::uiTextList;



MyGameUIText::MyGameUIText( int _height, int _width, int _weight, string _fontName, bool _italic )
	:MyGameTextBase( _height, _width, _weight, _fontName, _italic )/*, text( "" )*/
{
	
	//MessageBoxA(0,"囧，MyGameUIText构造函数开始",0,0);
	uiTextList.push_back( this );

	//pDestRect = 0;
}


MyGameUIText::~MyGameUIText(void)
{
	//free( pDestRect );
}

//int MyGameUIText::SetText( string _text )
//{
//	text = _text;
//	const char* text_c = _text.c_str();
//	wchar_t _textWide[50];
//		setlocale(LC_ALL, "");
//		mbstowcs( _textWide, text_c, strlen( text_c )+1 ); 
//	return wcslen( _textWide );
//}

void MyGameUIText::RenderAllText()
{
	for( vector<MyGameUIText*>::iterator _itr = uiTextList.begin();
		_itr != uiTextList.end();
		++ _itr )
	{	
		MyGameUIText* currentText = *_itr;
		//currentText->DrawUIText( currentText->text.c_str(),
		//						currentText->count, 
		//						currentText->pDestRect,
		//						currentText->format,
		//						currentText->color );
		currentText->RenderText();
	}
}

