#pragma once
#include "MyGameLua.h"
//#include "MyGameInstance.h"
#include "MyGameUIDialog.h"
#include <string>
using std::string;
class MyGameLevel
{
private:
	
	MyGameLua luaLevelScript;

	string scriptName;

	string* characterList;
	string* backgroundList;

	static MyGameUIDialog* mainDialog;

	static MyGameLevel* currentLevel;
	//static MyGameInstance*	gameInstance;

	static string dataFileName;

	static string AddChFuncName;
	static string AddBgFuncName;
	static string ChoiceFuncName;
	static string DialogFuncName;

	static const char* MyMessageFuncName;

	// C functions that will be (only) called in lua
	static int AddCh( lua_State* L );
	static int AddBg( lua_State* L );
	static int Choice( lua_State* L );
	static int Dialog( lua_State* L );
	static int MyGameMessageFunc( lua_State* L);

	static bool (*DialogLoop)();
public:
	MyGameLevel(void);
	//Load the lua script and init this level
//	MyGameLevel(char* _luaScriptName);
	bool LoadLevel(string _luaScriptName);
	bool RunLevel();
	~MyGameLevel(void);
	//static void SetgameInstance(MyGameInstance*);
	static void SetLoopFunction( bool (*loop)() );
	static void InitDialog()
	{
		//MessageBoxA(0,"‡å£¬InitDialog()¿ªÊ¼",0,0);
		mainDialog = new MyGameUIDialog();
		//MessageBoxA(0,"‡å£¬new MyGameUIDialog()½áÊø",0,0);
		mainDialog->SetCount(0);
		mainDialog->SetVisibility(false);
	}
	static void DestroyDialog()
	{
		delete mainDialog;
	}
};