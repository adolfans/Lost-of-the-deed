#include "StdAfx.h"
#include "MyGameWindow.h"
#include "MyGameFunctions.h"

MyGameWindow::MyGameWindow(void)
	:hWnd( 0 ),
	wClient( 0 ),
	hClient( 0 ),
	nCmdShow( 0 ),
	wTittle( "" ),
	cursorX( 0 ),
	cursorY( 0 ),
	ifClicked( false ),
	hInstance( 0 )
{
	//::MessageBoxA(0,"MyGameWindow开始调用",0,0);
}


MyGameWindow::~MyGameWindow(void)
{
//	delete wTittle;
}

//
//POINT	MyGameWindow::GetMyMousePosistion()
//{
//	POINT	mousePoint;
//	return mousePoint;
//}

void MyGameWindow::SetWidthClient(int _width)
{
	this->wClient = _width;
}

void MyGameWindow::SetHeightClient(int _height)
{
	this->hClient = _height;
}

void MyGameWindow::SetWindowTittle(const char* _tittle)
{
	this->wTittle = _tittle;
	//::MyGameStringCopy(&(wTittle),_tittle);
//	this->SetWTittle(_tittle);
//	strcpy(wTittle, _tittle);
}

void MyGameWindow::SetCmdShow(int _nCmdShow)
{
	this->nCmdShow = _nCmdShow;
}

void MyGameWindow::SetInstance( HINSTANCE _hInstance )
{
	this->hInstance = _hInstance;
}

//POINT	GetMyMousePosistion();
int		MyGameWindow::GetWidthClient()
{
	return this->wClient;
}
int		MyGameWindow::GetHeightClient()
{
	return this->hClient;
}
	
HWND	MyGameWindow::GethWnd()
{
	return this->hWnd;
}

LRESULT CALLBACK MyGameWindow::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch( msg )
	{
		
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		::SendMyMessage( quitGame );
		return 0;
	}
	return ::DefWindowProc(hwnd,msg,wparam,lparam);
}


bool MyGameWindow::CreateGameWindow(HINSTANCE _hInstance, char* _winTittle, int _Width, int _Height, int _nCmdShow)
{
	this->wClient = _Width;
	this->hClient = _Height;

	//client pos to window pos
	RECT _windowRect = {0, 0, _Width, _Height};
	::AdjustWindowRect( &_windowRect, WS_VISIBLE|WS_OVERLAPPEDWINDOW, false);
	_Width = _windowRect.right - _windowRect.left;
	_Height= _windowRect.bottom - _windowRect.top;

	//set wTittle
//	wTittle = _winTittle;
	// fill WNDCLASSEX structure
	WNDCLASSEX winClass;
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style	= CS_VREDRAW | CS_HREDRAW/* | CS_OWNDC | CS_DBLCLKS*/;
	winClass.lpfnWndProc= WndProc;
	winClass.cbClsExtra	= 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance	= _hInstance;
	winClass.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor	= LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName	= NULL;
	winClass.lpszClassName	= L"MyClass";
	winClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	
//	DWORD er;

	// Register WinClass
	if(0==RegisterClassEx( &winClass ))
	{
		::MessageBox(0,L"Register window class -- failed",0,0);
//		er = ::GetLastError();
	}

	//Create Window
	hWnd=::CreateWindowExA(NULL, 
								"MyClass",
								_winTittle,
								WS_VISIBLE|WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								_Width, _Height,
								NULL, NULL,
								_hInstance,
								NULL);

	if(hWnd==0)
	{
		::MessageBoxA(0,"创建窗口失败！！",_winTittle,0);
		return false;
	}

	::ShowWindow(hWnd,_nCmdShow);
	::UpdateWindow(hWnd);

	return true;
}

bool MyGameWindow::CreateGameWindow()
{
	/*
	this->wClient = _Width;
	this->hClient = _Height;
	*/
	//client pos to window pos
	RECT _windowRect = {0, 0, wClient, hClient};
	::AdjustWindowRect( &_windowRect, WS_VISIBLE|WS_OVERLAPPEDWINDOW, false);
	int _Width = _windowRect.right - _windowRect.left;
	int _Height= _windowRect.bottom - _windowRect.top;

	//set wTittle
//	wTittle = _winTittle;
	// fill WNDCLASSEX structure
	WNDCLASSEX winClass;
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style	= CS_VREDRAW | CS_HREDRAW/* | CS_OWNDC | CS_DBLCLKS*/;
	winClass.lpfnWndProc= WndProc;
	winClass.cbClsExtra	= 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance	= this->hInstance;
	winClass.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor	= LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName	= NULL;
	winClass.lpszClassName	= L"MyClass";
	winClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	
//	DWORD er;

	// Register WinClass
	if(0==RegisterClassEx( &winClass ))
	{
		::MessageBox(0,L"Register window class -- failed",0,0);
//		er = ::GetLastError();
	}

	//Create Window
	hWnd=::CreateWindowExA(NULL, 
								"MyClass",
								wTittle.c_str(),
								WS_VISIBLE|WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								_Width, _Height,
								NULL, NULL,
								hInstance,
								NULL);

	if(hWnd==0)
	{
		::MessageBoxA(0,"创建窗口失败！！",wTittle.c_str(),0);
		return false;
	}

	::ShowWindow( hWnd,nCmdShow );
	::UpdateWindow( hWnd );

	return true;

}
