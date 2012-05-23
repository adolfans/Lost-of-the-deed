#include "StdAfx.h"
#include "MyGameLevel.h"
#include "MyGameFunctions.h"
#include "MyGameMessage.h"
#include "MyGameMessageBox.h"

//definitions of the static members in MyGameLevel
//MyGameInstance*	MyGameLevel::gameInstance = NULL;
MyGameLevel*	MyGameLevel::currentLevel = NULL;
string			MyGameLevel::dataFileName("data.lua");
string			MyGameLevel::AddChFuncName("AddCh");
string			MyGameLevel::AddBgFuncName("AddBg");
string			MyGameLevel::ChoiceFuncName("choice");
string			MyGameLevel::DialogFuncName("dialog");
const char*		MyGameLevel::MyMessageFuncName = "MyMessage";
bool			(*MyGameLevel::DialogLoop)() = NULL;
//int				MyGameLevel::MyGameMessageFunc( lua_State* L);

MyGameUIDialog* MyGameLevel::mainDialog = 0;

/*
MyGameLevel::MyGameLevel(void)
{
}
*/

MyGameLevel::~MyGameLevel(void)
{
	/*
	if(scriptName)
	delete[] scriptName;
*/	if(characterList)
	delete[] characterList;
	if(backgroundList)
	delete[] backgroundList;
}

//void MyGameLevel::SetgameInstance(MyGameInstance* _gameInstance)
//{
//	gameInstance = _gameInstance;
//}

MyGameLevel::MyGameLevel(void)
	:luaLevelScript(),characterList(0),backgroundList(0),
	scriptName("")
{
	//MessageBoxA(0,"囧，MyGameLevel构造函数开始",0,0);
	// open lua libs
	luaLevelScript.OpenLuaLibs();
#ifdef _DEBUG
	// open debug
	luaLevelScript.RunALine("debug.sethook(print,\"l\")");
#endif
		
	/*Load C function*/
	luaLevelScript.PushCFunctionToLuaByName( AddCh, AddChFuncName );
	luaLevelScript.PushCFunctionToLuaByName( AddBg, AddBgFuncName );
	
	/*push c function of updating frame*/
	luaLevelScript.PushCFunctionToLuaByName( MyGameLevel::Choice, ChoiceFuncName );
	luaLevelScript.PushCFunctionToLuaByName( MyGameLevel::Dialog, DialogFuncName );

	luaLevelScript.PushCFunctionToLuaByName( MyGameMessageFunc,"MyMessage");

	/*test to load lua datas*/
	luaLevelScript.LoadAScriptFile(dataFileName);
//	MyGameStringCopy( &scriptName, _luaScriptName );
	//MessageBoxA(0,"囧，MyGameLevel构造函数结束",0,0);
}

bool MyGameLevel::LoadLevel(string _luaScriptName)
{
	
	this->scriptName = _luaScriptName;
	
	currentLevel = this;
	/*load this level*/
	luaLevelScript.LoadAScriptFile( scriptName );
	/***********load datas*************/

	luaLevelScript.PushLuaFunctionToCByName("situation");
	/*set update function*/

	return true;
}

// run the situation function in lua
bool MyGameLevel::RunLevel()
{
	mainDialog->SetVisibility(true);
	bool returnValue = luaLevelScript.RunLuaFunction( 0, 0 );
	mainDialog->SetVisibility(false);
	return returnValue;
}

const char* returnLuaFunction = "do return end";
///////////////////////////////////////////////
// C functions that will be (only) called in lua
///////////////////////////////////////////////
int MyGameLevel::AddCh( lua_State* L )
{
	if(GetGameState()!= GAMEPROCESS )
	{
		//int errorCode;
		//errorCode = luaL_loadbuffer( L, returnLuaFunction, strlen(returnLuaFunction), "line") ||
  //              lua_pcall(L, 0, 0, 0);
		return 0;
	}
	int index = lua_gettop( L );

	//currentLevel->characterList = new string[index];

	MyGameMessage("Character list:");
	for(int i = index; i > 0; --i)
	{		
		/*Add Characters*/
		const char* ch = lua_tostring( L, i );
		//currentLevel->characterList[i-1] = ch;
//		printf("%s",ch);
		MyGameMessage( ch );
	}
//	printf("\nThe No. parameter is %d", i);
	return 0;
}

int MyGameLevel::AddBg( lua_State* L )
{
	if(GetGameState()!= GAMEPROCESS )
	{
		//int errorCode;
		//errorCode = luaL_loadbuffer( L, returnLuaFunction, strlen(returnLuaFunction), "line") ||
  //              lua_pcall(L, 0, 0, 0);
		return 0;
	}
	int index = lua_gettop( L );
	
	//currentLevel->backgroundList = new string[index];

	MyGameMessage("Background list:");
	
	for( int i = index; i > 0; --i )
	{
		/*Add Background*/
		const char* bg = lua_tostring( L, i );
		//currentLevel->backgroundList[i-1] = bg;
		MyGameMessage(bg);
	}

	return 0;
}

int MyGameLevel::Choice( lua_State* L )
{
	if(GetGameState()!= GAMEPROCESS )
	{
		//int errorCode;
		//errorCode = luaL_loadbuffer( L, returnLuaFunction, strlen(returnLuaFunction), "line")/* ||
  //              lua_pcall(L, 0, 0, 0)*/;
		lua_pushinteger( L, 0 );
		return 0;
	}
	ChangeGameSubState( dialogChoosing );
	mainDialog->SetCount(0);
	int index = lua_gettop( L );
	mainDialog->SetChoiceCount( index );
	//string* strList = new string[index];

	MyGameMessage("Choices list:");

	mainDialog->CleanChoiceText();

	for(int i = index; i > 0; --i)
	{		
		/*Add Characters*/
		const char* ch = lua_tostring( L, i );
		//strList[i-1] = ch;
		mainDialog->AddChoiceText(ch);
//		printf("%s",ch);
		//MyGameMessage( ch );
	}
	MyGameMessage("参数个数为"<<index);
	static int result = 0;
	//static int currentChoiceDisplay;
	//currentChoiceDisplay = 1;
	//while( !result )
	//{
	//	if( currentChoiceDisplay > index )
	//		currentChoiceDisplay = 1;
	//	mainDialog->SetChoiceText( strList[currentChoiceDisplay-1].c_str() );
		if(!MyGameLevel::DialogLoop())
		{
			//save game and set game state to GAMECLOSE
			SendMyMessage( quitGame );
			return 0;
		}else
		{
			//static GameMsg myGameMsg;
			////if choosed
			//if( ::GetMyMessage( myGameMsg ) )
			//{
			//	if( myGameMsg == choosedWords )
			//	{
			//		result = currentChoiceDisplay;
			//		RemoveOneMessage();
			//		//break;
			//	}
			//}
			result = GetMyChoice();
			RemoveMyChoice();
		}
		//currentChoiceDisplay++;
	//}
	lua_pushinteger( L, result );
	//mainDialog->SetCount(0);
	result = 0;
	mainDialog->SetChoiceText("");
	//delete[] strList;
	//return 1;
	return 1;
}
// before it be called, gameInstance must be set
int MyGameLevel::Dialog( lua_State* L )
{
	if(GetGameState()!= GAMEPROCESS )
	{
		return 0;
	}
	MyGameMessage("dialog function was called");
	ChangeGameSubState( talking );
	//parameter from left to right 
	//dialog content, character number, expression number
	int index = lua_gettop( L );
	/*Add Characters*/
	const char* name_c = lua_tostring( L, index-1 );
	mainDialog->SetNameText( name_c );
	const char* ch = lua_tostring( L, index-2 );
	int num = mainDialog->SetDialogText( ch );
	mainDialog->SetCount(num);
	if(!MyGameLevel::DialogLoop())
	{
		//save game and set game state to GAMECLOSE
		SendMyMessage( quitGame );
	}
	mainDialog->SetCount(0);
	return true;
}

void MyGameLevel::SetLoopFunction( bool (*loop)() )
{
	MyGameLevel::DialogLoop = loop;
}


int	MyGameLevel::MyGameMessageFunc( lua_State* L)
{
	if(GetGameState()!= GAMEPROCESS )
	{
		//int errorCode;
		//errorCode = luaL_loadbuffer( L, returnLuaFunction, strlen(returnLuaFunction), "line") ||
  //              lua_pcall(L, 0, 0, 0);
		return 0;
	}
	//ChangeGameSubState( myGameNotifyMsg );
	int index = lua_gettop( L );
	/*Add Characters*/
	const char* msg = lua_tostring( L, index );
	MyGameMessageBox::MyGameNotifyBox( msg );
	if(!MyGameLevel::DialogLoop())
	{
		//save game and set game state to GAMECLOSE
		SendMyMessage( quitGame );
	}
	//::MessageBoxA( 0, msg, 0, 0 );
	return 1;
}