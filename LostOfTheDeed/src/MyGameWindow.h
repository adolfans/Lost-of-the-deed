#pragma once
#include <windows.h>
#include <string>
using std::string;

#include "MyGameMessage.h"
class MyGameWindow
{
private:
	int				cursorX;
	int				cursorY;
	HWND			hWnd;
	int				wClient;
	int				hClient;
	int				nCmdShow;
	string			wTittle;
	HINSTANCE		hInstance;
	bool			ifClicked;
public:
	MyGameWindow(void);
	~MyGameWindow(void);
	
	//Initialization fuctions
	bool	CreateGameWindow(HINSTANCE _hInstance,
							char* _winTittle,
							int _Width,
							int _Height,
							int _nCmdShow);

	bool	CreateGameWindow();
		
	static	LRESULT CALLBACK
		WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	
	void	SetWidthClient( int _width );
	void	SetHeightClient( int _height );
	void	SetWindowTittle( const char* _tittle );
	void	SetInstance( HINSTANCE _hInstance );
	void	SetCmdShow( int		_nCmdShow );

	void	SetCursorPos(){
		if( myGameNotifyMsg == GetGameSubState() )
		{
			this->ifClicked = false;
			this->cursorX = 0;
			this->cursorY = 0;
			return;
		}
			POINT cursorPosition;
			GetCursorPos(&cursorPosition);
			//if( ::GetAsyncKeyState( VK_LBUTTON ) & 0x8000f )
			if( GetCurrentKeyState() == LButton )
			{
				this->ifClicked = true;
				ResetCurrentKeyState();

			}else
				this->ifClicked = false;
			ScreenToClient(hWnd,&cursorPosition);
			this->cursorX = 1024*cursorPosition.x/wClient;
			this->cursorY = 768*cursorPosition.y/hClient;
	}

	bool	IfClicked(){
		return this->ifClicked;
	}

	//POINT	GetMyMousePosistion();
	int		GetWidthClient();
	int		GetHeightClient();
	HWND	GethWnd();
	int		GetCursorX(){ return this->cursorX;}
	int		GetCursorY(){ return this->cursorY;}
};

