#pragma once
#include "MyGameUISprite.h"
#include "MyGameClock.h"
#include "MyGameUIText.h"
#include "MyGameDecoration.h"
#include <vector>
using std::vector;
class MyGameUIDialog:
	MyGameDecoration
	/*:
	public MyGameUISprite*/
{
private:
	MyGameUISprite dialogUI;
	MyGameUIText	dialogText;
	MyGameUIText	nameText;
	MyGameUIText	choiceText;
	MyGameUISprite	personBG;
	float			textAcountDrawn; //the count that will be drawn really
	int				textAcount;
	int				choiceWordsCount;
	float			choiceWordsCountWillNotBeDrawn;
	MyGameClock countDownChoiceWordNum;
	//int				choiceCountDrawn;//the count that will be drawn really
	MyGameClock		dialogTextClock;
	vector<string>	choiceList;
	int				choiceCount;
	int				currentChoice;
public:
	MyGameUIDialog(void);
	~MyGameUIDialog(void);
	void update();
	void SetVisibility(bool);
	int SetDialogText( const char* );
	int SetNameText( const char* );
	void SetCount( int );

	void SendMyChoice( int );

	int	GetMyChoice();
	
	void EnableChoiceMenu();
	int SetChoiceText( const char* );
	int AddChoiceText( const char* );
	void SetChoiceCount( int _count )
	{
		choiceCount = _count;
	}
	void CleanChoiceText();
};

