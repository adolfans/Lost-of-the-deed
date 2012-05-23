#pragma once
#include "mygameinstance.h"
#include "testLoadObjFile.h"
class MyNewGameInstance :
	public MyGameInstance
{
private:
	//static MyNewGameInstance*	pMyGameInstance;
	MyGameUISpriteMain* pMainUI;

	MyGameLevel*		newLevel;

	MyGameMessageBox*		pMyGameNotiy;

	MyGameNotify*			pMyGameNotify;

	testLoadObjFile*		objFile;

public:
	MyNewGameInstance(void);
	~MyNewGameInstance(void);

	void InitGameSceneObjects();

	void InitUI2();

	void NewGame();

	void RenderSceneObjects();

	static MyNewGameInstance* GetMyGameInstance( HINSTANCE _hInstance, int _nCmdShow );

};

