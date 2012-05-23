#include "StdAfx.h"
#include "MyNewGameInstance.h"

//MyNewGameInstance*	MyNewGameInstance::pMyGameInstance = 0;


MyNewGameInstance::MyNewGameInstance(void)
{
}


MyNewGameInstance::~MyNewGameInstance(void)
{
	delete objFile;
	delete newLevel;
	//pMainUI->DestroySprite();
	delete pMainUI;
	delete pMyGameNotiy;
	delete pMyGameNotify; 
}

void MyNewGameInstance::InitUI2()
{
#ifdef DX9

	//get view matrix


	pMainUI = new MyGameUISpriteMain();

	//MyGameTextBase::SetDevice( this->pMyDevice );
	
	pMyGameNotiy = MyGameMessageBox::InitGameMessageBox();

	pMyGameNotify = MyGameNotify::InitNotifyBox();

	newLevel = new MyGameLevel();

#endif
}

void MyNewGameInstance::NewGame()
{
	this->newLevel->LoadLevel("testLevel.lua");
	
					this->pMainUI->SetVisibility(false);
					::MyGameNotify::MyGameNotification("记录于2012-01-13-16:32\n游戏已3小时25分钟\n地点：东南海域");
					newLevel->RunLevel();
					this->pMainUI->SetVisibility(true);
}


MyNewGameInstance* MyNewGameInstance::GetMyGameInstance( HINSTANCE _hInstance, int _nCmdShow )
{
	if(pMyGameInstance==NULL)
	{
		MyNewGameInstance* pNewInstance = new MyNewGameInstance;
		pMyGameInstance = pNewInstance;

		pMyGameInstance->SetInstanceAndCmdLine( _hInstance, _nCmdShow );

		return pNewInstance;

	}else
	{
		return 0;
	}
}


void MyNewGameInstance::InitGameSceneObjects()
{
	objFile = new testLoadObjFile("harbor");
}

void MyNewGameInstance::RenderSceneObjects()
{
	MyGame3DDevice::StartRenderUI();
	objFile->render();
	MyGame3DDevice::EndRenderUI();
}