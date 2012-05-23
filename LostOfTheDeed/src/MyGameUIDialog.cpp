#include "StdAfx.h"
#include "MyGameUIDialog.h"
#include "MyGameMessage.h"

const int DIALOG = 1;
const int SKILL	 = 2;
const int SKILL_S = 3;
const int NEXT	= 4;
const int NEXT_F = 5;

MyGameUIDialog::MyGameUIDialog(void)
	://dialogUI( "dialogUI2.png", true, 22, 0.0f, 0.0f, 1024.0f, 768.0f ),
	dialogUI( "img/dialog.png", true, 22),
	dialogText( 35, 14, 30, "Î¢ÈíÑÅºÚ", false ),
	choiceText( 30, 12, 30, "Î¢ÈíÑÅºÚ", false ),
	personBG( "img/personBG.png",true, 21, 0.0f, 0.0f, 1024.0f, 768.0f ),
	nameText( 30, 13, 400, "Î¢ÈíÑÅºÚ", false ),
	textAcountDrawn( 0.0f ),
	textAcount( 0 ),
	dialogTextClock( textAcountDrawn, 0.02, true, 20.0),
	currentChoice( 1 ),
	choiceWordsCountWillNotBeDrawn( 0.0f ),
	countDownChoiceWordNum( choiceWordsCountWillNotBeDrawn, 0.08, true, 0),
	choiceCount(0)
{
	dialogText.SetDestRectForScreen( 85, 600, 1000, 400 );
	dialogText.SetColor( 0xffffffff );
	nameText.SetDestRectForScreen( 100, 520, 160, 50 );
	nameText.SetColor( 0xff000000 );
	choiceText.SetDestRectForScreen( 85, 600, 1000, 400 );
	choiceText.SetColor( 0xff17d609 );
	personBG.SetVisibility(false);
	dialogUI.CreateRectangleWithIntKey( DIALOG, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 384.0f, 1024.0f, 384.0f );
	dialogUI.CreateRectangleWithIntKey( SKILL, 0.0f, 0.0f, 194.0f/1024.0f, 194.0f/768.0f, 786.0f, 475.0f, 194.0f, 194.0f );
	dialogUI.CreateRectangleWithIntKey( SKILL_S, 194.0f/1024.0f, 0.0f, 388.0f/1024.0f, 194.0f/768.0f, 786.0f, 475.0f, 194.0f, 194.0f );
	dialogUI.CreateRectangleWithIntKey( NEXT, 0.0f, 194.0f/768.0f,  89.0f/1024.0f, (194.0f+24.0f)/768.0f , 745.0f, 688.0f, 89.0f, 24.0f ); 
	dialogUI.CreateRectangleWithIntKey( NEXT_F, 0.0f, 194.0f/768.0f,  135.0f/1024.0f, (194.0f+24.0f)/768.0f , 745.0f, 688.0f, 135.0f, 24.0f ); 
	dialogUI.SetRectVisibility( DIALOG, true );
	dialogUI.SetRectVisibility( SKILL, true );
	dialogUI.SetRectVisibility( SKILL_S, false );
	dialogUI.SetRectVisibility( NEXT, true );
	dialogUI.SetRectVisibility( NEXT_F, true );
	dialogTextClock.StopUpdateAndReset();

	choiceText.SetCount(0);

	countDownChoiceWordNum.StopUpdateAndReset();
}


MyGameUIDialog::~MyGameUIDialog(void)
{
	dialogText.DestroyText();
}

void MyGameUIDialog::SetVisibility(bool _visible)
{
	this->dialogText.SetCount(0);
	dialogUI.SetVisibility(_visible);
	personBG.SetVisibility( _visible );
	nameText.SetCount(0);
	if( _visible )
		dialogTextClock.StartUpdate();
	else
		dialogTextClock.StopUpdateAndReset();
}

int MyGameUIDialog::SetDialogText( const char* _text)
{
	return this->dialogText.SetText( _text );
}

void MyGameUIDialog::SetCount( int _count )
{
//	dialogText.SetCount( _count );
	dialogTextClock.SetLimit( _count );
	textAcount = _count;
}

int MyGameUIDialog::SetNameText(const char* _text )
{
	int num = nameText.SetText( _text );
	nameText.SetCount( num );
	return num;
}

void MyGameUIDialog::update()
{
	if( !dialogUI.GetVisibility() )
		return;
	//MyGameUISprite::RenderUISprite();

	static int textAcountReallyDrawn;

	//static int keyPressed = false;
	if( dialogUI.IfCursorInRect( SKILL ) || SkillPressing == GetCurrentPressingKey() )
	{
		dialogUI.SetRectVisibility( SKILL, false );
		dialogUI.SetRectVisibility( SKILL_S, true );
	}else
	{
		dialogUI.SetRectVisibility( SKILL, true );
		dialogUI.SetRectVisibility( SKILL_S, false );
	}

	if( FastForwad == GetCurrentPressingKey() )
	{
		dialogUI.SetRectVisibility( NEXT_F, true );
	}else
	{
		dialogUI.SetRectVisibility( NEXT_F, false );
	}


	textAcountReallyDrawn = textAcountDrawn;

	if( textAcountDrawn >= textAcount )
	{
		//dialogTextClock.StopUpdateAndReset();
		textAcountReallyDrawn = textAcount;
		//if(::GetAsyncKeyState(VK_SPACE) & 0x8000f)
		//if(::GetAsyncKeyState(VK_SPACE) & 0x8000)
		if( GetCurrentKeyState() == Next || FastForwad == GetCurrentPressingKey() )
		{
				::SendMyMessage( changeWords );
				ResetCurrentKeyState();
		}
	}else
	{
		//if(::GetAsyncKeyState(VK_SPACE) & 0x8000)
		if( GetCurrentKeyState() == Next || FastForwad == GetCurrentPressingKey() )
		{
				textAcountReallyDrawn = textAcount;
				textAcountDrawn = textAcount + 1;
				ResetCurrentKeyState();
		}
	}
	// set count that will be really drawn
	dialogText.SetCount( textAcountReallyDrawn );

	
	//static int	choiceWordsAcount = 0;

	if( dialogChoosing == GetGameSubState() )
	{
		static bool choiceRemoving = false;

		static bool choiceLoading  = true;

		static int choiceLoadingUpdate = 0;
			countDownChoiceWordNum.StartUpdate();
		//if( choiceLoadingUpdate == 0 )
		//{
		//	//countDownChoiceWordNum.StartUpdate();
		//	choiceText.SetText( choiceList[choiceCount - 1].c_str() );
		//	choiceLoadingUpdate = 1;
		//}

		//if pressed enter
		if( GetCurrentKeyState() == Enter )
		{
			if( choiceRemoving || choiceLoading )
			{
				ResetCurrentKeyState();
				return;
			}
			SendMyMessage( choosedWords );
			::SendMyChoice( currentChoice );
			currentChoice = 1;
			choiceList.clear();
			choiceText.SetCount(0);
			choiceLoading = true;
			ResetCurrentKeyState();
			return;
		}
		//if pressed backspace
		if( GetCurrentKeyState() == ChangeChoice )
		{
			//static int currentChoice = 1;
			if( choiceRemoving == true )//if it is changing, start load the next choice
			{
				choiceRemoving = false;
				currentChoice++;;
				if( currentChoice > choiceCount )		//overflow
					currentChoice = 1;
				int count = choiceText.SetText( choiceList[choiceCount-currentChoice].c_str() );
				choiceText.SetCount( count );
				choiceWordsCount = count;
				//countDownChoiceWordNum.StopUpdateAndReset();
				countDownChoiceWordNum.SetLimit( count );
				countDownChoiceWordNum.StartUpdate();
				choiceLoading = true;
				ResetCurrentKeyState();
				countDownChoiceWordNum.StartUpdate();
			}else if( choiceLoading == true )		//if it is loading, do nothing
			{
				ResetCurrentKeyState();
			}else
			{
				choiceRemoving = true;
				countDownChoiceWordNum.SetLimit( choiceWordsCount );
				countDownChoiceWordNum.StartUpdate();
				ResetCurrentKeyState();
			}
		}
		if( choiceRemoving )
		{
			if( choiceWordsCountWillNotBeDrawn >= choiceWordsCount)	// if so, stop update
			{
				currentChoice++;
				if( currentChoice > choiceCount )
					currentChoice = 1;
				//countDownChoiceWordNum.StopUpdateAndReset();
				choiceRemoving = false;
				int count = choiceText.SetText( choiceList[choiceCount-currentChoice].c_str() );
				choiceText.SetCount( count );
				choiceWordsCount = count;
				choiceLoading = true;
				countDownChoiceWordNum.SetLimit( count );
				countDownChoiceWordNum.StartUpdate();
			}else
			{
				choiceText.SetCount( choiceWordsCount - choiceWordsCountWillNotBeDrawn );
			}

		}
		
		if( choiceLoading )
		{
			int i = choiceWordsCountWillNotBeDrawn;
				if( i >= choiceWordsCount )
				{
					countDownChoiceWordNum.StopUpdateAndReset();
					choiceText.SetCount( choiceWordsCount );
					choiceLoading = false;
					//countDownChoiceWordNum.SetLimit( choiceWordsCount );
				}else
				{
					choiceText.SetCount( i );
				}
		}
	}
}

void MyGameUIDialog::EnableChoiceMenu()
{
	dialogText.SetCount(0);
}

int MyGameUIDialog::SetChoiceText( const char* _text )
{
	int count = choiceText.SetText( _text );
	choiceText.SetCount( count );
	choiceWordsCount = count;
	return count;
}

int MyGameUIDialog::AddChoiceText( const char* _text )
{
	choiceList.push_back( _text );
	SetChoiceText( _text );
	countDownChoiceWordNum.SetLimit( choiceWordsCount );
	return 0;
}

void MyGameUIDialog::CleanChoiceText()
{
	choiceList.clear();
}