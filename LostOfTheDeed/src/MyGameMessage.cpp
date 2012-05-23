#pragma once
#include "StdAfx.h"
#include "MyGameMessage.h"
#include "MyGameClock.h"

//queue<GameMsg> MyMsgList;
//queue<int>		choosenList;

GameMsg			MyMsgList = noMessage;
GameState		currentState = MAINMENU;
bool			stateChanged = false;
KeyState		currentKeyState = None;
KeyPressingState currentPressingKey = None_pressing;

GameSubState	currentSubState = talking;

int				myChoice = 0;
//
//msgStack	myMsgList;

void SendMyMessage( GameMsg _msg ){
	//MyMsgList.push_back( _msg );
	MyMsgList = _msg ;
}

void DispatchMyMessage()
{
	//if( MyMsgList.size() == 0 )
	if( MyMsgList == noMessage )
		return;
	GameMsg msgToDispatch = MyMsgList;
	
	switch( msgToDispatch )
	{
	case returnMenu:
		currentState = MAINMENU;
		stateChanged = true;
		//MyMsgList.pop();
		MyMsgList = noMessage;
		break;
	case newGame:
		currentState = NEWGAME;
		stateChanged = true;
		//MyMsgList.pop();
		MyMsgList = noMessage;
		break;
	case loadGame:
		currentState = LOADGAME;
		stateChanged = true;
		//MyMsgList.pop();
		MyMsgList = noMessage;
		break;
	case runningGame:
		currentState = GAMEPROCESS;
		stateChanged = true;
		//MyMsgList.pop();
		MyMsgList = noMessage;
		break;
	case quitGame:
		currentState = GAMEQUIT;
		stateChanged = true;
		//MyMsgList.pop();
		MyMsgList = noMessage;
	default:
		break;
	}
}

GameState GetGameState()
{
	return currentState;
}

bool	testIfStateChanged()
{
	bool ifChanged = stateChanged;
	return ifChanged;
}

void	resetStateChanged()
{
	stateChanged = false;
}

bool GetMyMessage( GameMsg& myMsg)
{
	if( MyMsgList == noMessage )
		return false;
	GameMsg msgToDispatch = MyMsgList;
	//MyMsgList.pop();
	myMsg = msgToDispatch;
	return true;
}

void RemoveOneMessage()
{
	//MyMsgList.pop();
	MyMsgList = noMessage;
}

void UpdateCurrentKeyState()
{
	static float timePassed = 0;
	static KeyState pressedKey = None;

	//if( currentSubState == myGameNotifyMsg )		//if so, disable all keys except LButton and Space

		if(::GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			pressedKey = Next;
			return;
		}else if(::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			pressedKey = LButton;
			return;
		}else if( currentSubState == myGameNotifyMsg )		//if so, disable all keys except LButton and Space
		{
			//if not pressing anything
			if( pressedKey != None )	//if pressed some key last time
			{
				currentKeyState = pressedKey;
				pressedKey = None;
			}
				currentPressingKey = None_pressing;
			return;
		}
		else if(::GetAsyncKeyState(VK_BACK) & 0x8000)
		{
			pressedKey = ChangeChoice;
			return;
		}else if(::GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			pressedKey = Enter;
			return;
		}else if(::GetAsyncKeyState(VK_CONTROL) & 0x8000)
		{
			currentPressingKey = FastForwad;
			return;
		}else if(::GetAsyncKeyState('S') & 0x8000)
		{
			currentPressingKey = SkillPressing;
			pressedKey = Skill;
			return;
		}else
		{
			//if not pressing anything
			if( pressedKey != None )	//if pressed some key last time
			{
				currentKeyState = pressedKey;
				pressedKey = None;
			}/*else
			{*/
				currentPressingKey = None_pressing;
			/*}*/
		}

}

KeyState GetCurrentKeyState()
{
	return currentKeyState;
}

KeyPressingState GetCurrentPressingKey()
{
	return currentPressingKey;
}

void	ResetCurrentKeyState()
{
	currentKeyState = None;
}

GameSubState GetGameSubState()
{
	return currentSubState;
}

void	ChangeGameSubState( GameSubState _state )
{
	currentSubState = _state;
}

void SendMyChoice( int _choosen )
{
	myChoice = _choosen;
	//choosenList.push( _choosen );
}

int GetMyChoice()
{
	return myChoice;
	//if( choosenList.size() == 0 )
	//	return 0;
	//int myChoice = choosenList.back();
	////choosenList.pop();
	//return myChoice;
}

void RemoveMyChoice()
{
	//choosenList.pop();
	myChoice = 0;
}