#pragma once
#include "MyGameTextBase.h"
class MyGameUIText :
	public MyGameTextBase
{
private:
	static	vector<MyGameUIText*> uiTextList;
public:
	MyGameUIText( int _height, int _width, int _weight, string _fontName, bool _italic );
	virtual ~MyGameUIText(void);
	//int		SetText(string);
	static void	RenderAllText();
};

