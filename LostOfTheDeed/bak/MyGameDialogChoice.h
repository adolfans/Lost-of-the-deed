#pragma once
#include "mygameuitext.h"
class MyGameDialogChoice :
	public MyGameUIText
{
private:
	//string choice1;
	//string choice2;
public:
	MyGameDialogChoice( int _height, int _width, int _weight, string _fontName, bool _italic );
	virtual ~MyGameDialogChoice(void);
	void	RenderText();
};

