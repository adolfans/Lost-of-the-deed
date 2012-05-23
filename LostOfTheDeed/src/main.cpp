// testMyWorld1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"
#include "MyNewGameInstance.h"
#include "MyGameSettings.h"
#include "MyGameLevel.h"
#include "MyGameFunctions.h"
#include "MyGameUISpriteMain.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );  
	MyGameInstance* newGame = MyNewGameInstance::GetMyGameInstance(hInstance, nCmdShow);
	newGame->InitGame();
	newGame->InitUI2();
	newGame->InitGameSceneObjects();
	newGame->MainLoop();
	delete newGame;
	_CrtDumpMemoryLeaks();
}

