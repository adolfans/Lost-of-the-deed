#include "StdAfx.h"
#include "MyGameInstance.h"
#include "MyGameFunctions.h"
#include "MyGameDecoration.h"
#include <time.h>
#include "Resource.h"

#include "MyGameClock.h"

void GenerateGrid( int _width, int _height, float _stride, /*in & out*/Vertex** _pVertices, /*in & out*/WORD** _pIndices );

void CalculateNormal( D3DXVECTOR3* _vector0, D3DXVECTOR3* _vector1, D3DXVECTOR3* _vector2, D3DXVECTOR3* _outVector ); 

MyGameInstance*	MyGameInstance::pMyGameInstance = NULL;

string	configFileName = "config.lua";

MyGameInstance::MyGameInstance(void)
	:config(configFileName),
	//newLevel(0),
	pMyDevice(0),
	pMyWindow(0)//,
	//pMainUI(0)
{
	pMyWindow = new MyGameWindow;
}

MyGameInstance::~MyGameInstance(void)
{
	//pUIText->DestroyText();
	//delete pUIText;
	MyGameLevel::DestroyDialog();
	
	//MyGameUISprite::DestroyAllSprites();
	delete pMyDevice;
	delete pMyWindow;
	if(MyGameInstance::pMyGameInstance)
	{
		pMyGameInstance = NULL;
	}
}

bool MyGameInstance::DialogLoop()
{
	static MyGameInstance* gameInstance = MyGameInstance::GetMyGameInstance();
	MSG msg;

	while(true)
	{
		DispatchMyMessage();

		//if( GAMEQUIT == GetGameState() )
		//	return false;

		if(::PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			if( msg.message == WM_QUIT || msg.message == WM_DESTROY )
			{
				return false;
			}

			//
			//
			//static GameMsg myGameMsg;

			//if( ::GetMyMessage( myGameMsg ) )		//if Get a message
			//{
			//	if( myGameMsg == changeWords )
			//	{
			//		RemoveOneMessage();
			//		return true;
			//	}
			//}

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if( GAMEQUIT == GetGameState() )
			return false;
		else
		{
			static GameMsg myGameMsg;

			if( ::GetMyMessage( myGameMsg ) )		//if Get a message
			{
				if( talking == GetGameSubState() )	//if it is in talking state
				{
					if( myGameMsg == changeWords )
					{
						RemoveOneMessage();
						return true;
					}
				}else if( dialogChoosing == GetGameSubState() )		//if it is in dialog choosing state
				{
					if( myGameMsg == choosedWords )
					{
						if( ::GetMyChoice() )
						RemoveOneMessage();
						return true;
					}
				}else if(  myGameNotifyMsg == GetGameSubState() )
				{
					if( myGameMsg == myMsgBoxClosed )
					{
						::ChangeGameSubState( none );
						RemoveOneMessage();
						return true;
					}
				}
			}
		}
		
		
		UpdateCurrentKeyState();

		//this->UpdateGame();
		gameInstance->UpdateScene_tmp2();
	}
	return true;
}

bool MyGameInstance::MainLoop()
{
	static MyGameInstance* gameInstance = MyGameInstance::GetMyGameInstance();
	MSG msg;

	while(true)
	{
		DispatchMyMessage();
		
		if( GAMEQUIT == GetGameState() )
			return false;
		if(::PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			if( msg.message == WM_QUIT || msg.message == WM_DESTROY )
				return false;

			if( true == testIfStateChanged() )
			{
				if( NEWGAME == GetGameState() )
				{
					resetStateChanged();
					SendMyMessage( runningGame );
					DispatchMyMessage();
					resetStateChanged();
					this->NewGame();
				}
			}

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		

		UpdateCurrentKeyState();

		//this->UpdateGame();
		gameInstance->UpdateScene_tmp2();
	}
	return true;
}

MyGameInstance* MyGameInstance::GetMyGameInstance(HINSTANCE _hInstance, int _nCmdShow)
{
	//::MessageBoxA(0,"囧，GetMyGameInstance开始调用",0,0);
	if(pMyGameInstance==NULL)
	{
		pMyGameInstance = new MyGameInstance;

		pMyGameInstance->pMyWindow->SetInstance( _hInstance );

		pMyGameInstance->pMyWindow->SetCmdShow( _nCmdShow );

	}

	return pMyGameInstance;


}


MyGameInstance* MyGameInstance::GetMyGameInstance()
{
	if(pMyGameInstance==NULL)//if Uninitialized
	{
		return 0;
	}

	return pMyGameInstance;
}

//for the window with all configuration set
void MyGameInstance::InitGame()
{

	config.SetLoadedSettingsToInst(pMyWindow);

	pMyWindow->CreateGameWindow();

	MyGame3DDevice::SetGameWindow( pMyWindow );

	pMyDevice = MyGame3DDevice::GetMyDevice();

		IDirect3DDevice9* pD3D9InstanceDevice = this->pMyDevice->GetDevice();

	MyGameUISprite::SetDevice( pD3D9InstanceDevice );

	MyGameLevel::InitDialog();

	MyGameLevel::SetLoopFunction( MyGameInstance::DialogLoop );


}


HRESULT MyGameInstance::UpdateScene_tmp2()
{
	
	this->pMyWindow->SetCursorPos();
	MyGameUISprite::SetCursorPos( pMyWindow->GetCursorX(), pMyWindow->GetCursorY() );
	MyGameUISprite::SetClicked( pMyWindow->IfClicked() );

	pMyDevice->StartRender();
	
	
	this->RenderSceneObjects();

	MyGameDecoration::updateAllDecration();
	MyGameClock::UpdateAllClock();
	MyGame3DDevice::EnableUIAlphaBlending();
	MyGameUISprite::RenderAllSprites();
	MyGameUIText::RenderAllText();

	pMyDevice->EndRender();

	return S_OK;
}

//void MyGameInstance::InitGameSceneObjects()
//{
////	pD3D9InstanceDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
////	pD3D9InstanceDevice->CreateVertexBuffer(
//	
//	//IDirect3DDevice9* pD3D9InstanceDevice = this->pMyDevice->GetDevice();
//	
//	//pMyGameNotiy->MyGameNotifyBox("");
//
//	//return S_OK;
//}


void MyGameInstance::InitUI2()
{
}

void MyGameInstance::NewGame()
{
}


struct header{
	unsigned int	bfSize;		//4 bytes
	unsigned int	bfReserved12;	//4 bytes
	unsigned int	bfOffBits;	//4 bytes
	unsigned int	biSize;		//4 bytes
	unsigned int	Width;		//4 bytes
	int	Height;		//4 bytes
	char biPlanes[4];
	unsigned int	biCompression;	//4 bytes
	unsigned int	biSizeImage;	//4 bytes
	unsigned int	biXPelsPerMeter;
	unsigned int	biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
};

void GenerateGrid( int _width, int _height, float stride, /*in & out*/Vertex** _pVertices, /*in & out*/WORD** _pIndices )
{
	
	// map buffer
//	Vertex	mapVertices[11*11];
//	WORD	mapIndices[10*10*2*3];

	FILE *pFile = fopen( "c.bmp", "rb" );
	char bm[3];
	bm[2] = '\0';
	fread( bm, 1, 2, pFile );
	MyGameMessage( bm );

	struct header bmpHeader;
	fread( &bmpHeader, sizeof( struct header ), 1, pFile );

	unsigned char a[256*4];
	fread( a, 4, 256, pFile );
	unsigned char jiong[20*20];
	fread( jiong, 1, 20*20, pFile );

	*_pVertices = new Vertex[ ( _width + 1 ) * ( _height + 1 ) ];                                   

	*_pIndices	= new WORD[ _width * _height * 2 * 3];


	memset( *_pVertices, 0, sizeof(Vertex) *( _width + 1 ) * ( _height + 1 ) );

	srand ( time(NULL) );

	for( int i = 0; i < ( _width + 1 ) * ( _height + 1 ); ++i )
	{
		(*_pVertices)[i].pos.x = 0.0f + i%(_width+1)*stride;
		(*_pVertices)[i].pos.y = 480.0f - i/(_width+1)*stride;
		(*_pVertices)[i].pos.z = /*1.0f*/ /* rand()%20*/ -((float)jiong[i])/10.0f;
		(*_pVertices)[i].texCoord.x = (i%(_width+1))/(float)_width;
		(*_pVertices)[i].texCoord.y = (i/(_width+1))/(float)_height;
	}

	WORD* _tmpIndices = *_pIndices;
	for( int i = 0; i < _height; ++i )
	{
		for( int j = 0; j < _width; ++j )
		{
			D3DXVECTOR3 normalVector;
			*(_tmpIndices++) = ( i + 1 ) * (_width+1) + j;
			*(_tmpIndices++) =  i *(_width+1) +j;
			*(_tmpIndices++) =	i * (_width+1) + j + 1 ;

			CalculateNormal( &((*_pVertices)[( i + 1 ) * (_width+1) + j].pos),
							&((*_pVertices)[i *(_width+1) +j].pos),
							&((*_pVertices)[i * (_width+1) + j + 1 ].pos),
							&normalVector );

			(*_pVertices)[( i + 1 ) * (_width+1) + j].normal	+= normalVector;
			(*_pVertices)[i *(_width+1) +j].normal				+= normalVector;
			(*_pVertices)[i * (_width+1) + j + 1 ].normal		+= normalVector;
								


			*(_tmpIndices++) = ( i + 1 ) * (_width+1) + j;
			*(_tmpIndices++) = i * (_width+1) + j + 1;
			*(_tmpIndices++) = ( i + 1 ) * (_width+1) + j +1;

			CalculateNormal( &((*_pVertices)[( i + 1 ) * (_width+1) + j].pos),
							&((*_pVertices)[i * (_width+1) + j + 1].pos),
							&((*_pVertices)[( i + 1 ) * (_width+1) + j + 1 ].pos),
							&normalVector );

			(*_pVertices)[( i + 1 ) * (_width+1) + j].normal			+= normalVector;
			(*_pVertices)[i * (_width+1) + j + 1].normal				+= normalVector;
			(*_pVertices)[( i + 1 ) * (_width+1) + j + 1 ].normal		+= normalVector;
		}
	}

	
	for( int i = 0; i < ( _width + 1 ) * ( _height + 1 ); ++i )
	{
		D3DXVec3Normalize( &(*_pVertices)[i].normal, &(*_pVertices)[i].normal );
	}
}

void CalculateNormal( D3DXVECTOR3* _vector0, D3DXVECTOR3* _vector1, D3DXVECTOR3* _vector2, D3DXVECTOR3* _outVector )
{
	D3DXVECTOR3 A = *_vector1 - *_vector0;
	D3DXVECTOR3 B = *_vector2 - *_vector0;

	D3DXVec3Cross( _outVector, &A, &B );
}