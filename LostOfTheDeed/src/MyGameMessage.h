#pragma once
//
//#define MAINMENU	0
//#define NEWGAME		1
//#define LOADGAME	2

enum GameMsg{
	noMessage,
	returnMenu = 0,
	newGame	= 1,
	loadGame = 2,
	runningGame =3,
	changeWords = 4,
	changeChoiceWords = 5,
	choosedWords = 6,
	myMsgBoxClosed = 7,
	quitGame 
};

enum GameState{
	MAINMENU = 0,
	NEWGAME	= 1,
	LOADGAME = 2,
	GAMEPROCESS = 3,
	GAMEQUIT
};

enum GameSubState{
	none,
	talking,
	dialogChoosing,
	myGameNotifyMsg
};

enum KeyState{
	None,
	LButton,
	Next,
	Esc,
	Skill,
	ChangeChoice,
	Enter
};

enum KeyPressingState{
	None_pressing,
	FastForwad,
	SkillPressing
};

#include <queue>
using std::queue;

//extern queue<GameMsg> MyMsgList;

extern GameState	currentState;

extern GameSubState currentSubState;

extern KeyState		currentKeyState;

extern bool		stateChanged;

//
//class msgQueue{
//	//int* queueTop;
//	const int MAX_QUEUE_SIZE = 20;
//	int msg[20];
//	int msgCount;
//	//int msgCount;
//	int addMsg( int _msg )
//	{
//		if( msgCount < MAX_QUEUE_SIZE - 1 )
//		{
//			++msgCount;
//			msg[ msgCount ] = _msg;
//
//		}
//	}
//};
//
//extern msgQueue  myMsgList;
void SendMyMessage(GameMsg _msg);

void DispatchMyMessage();

bool GetMyMessage(GameMsg&);

GameState 	 GetGameState();

GameSubState	GetGameSubState();

void	RemoveOneMessage();

bool	testIfStateChanged();

void	resetStateChanged();

void	UpdateCurrentKeyState();

KeyState GetCurrentKeyState();

KeyPressingState GetCurrentPressingKey();

void	ResetCurrentKeyState();

void	ChangeGameSubState( GameSubState _state );

void	SendMyChoice( int _choosen );
int		GetMyChoice();
void	RemoveMyChoice();