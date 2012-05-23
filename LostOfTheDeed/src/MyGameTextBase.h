#pragma once
//#include "MyGame3DDevice.h"
#include <d3dx9.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
/*这个类的operator=需要被重载并设为私有*/
class MyGameTextBase
{
private:
	D3DXFONT_DESC df;
	ID3DXFont* font;
	bool		destroyed;
	bool		visible;
	static LPDIRECT3DDEVICE9 pDevice;


	LPRECT	pDestRect;
	int		count;
	DWORD	format;
	D3DCOLOR	color;
	//string	text;
	wchar_t textToDraw[100];

	static	int screenWidth;
	static	int screenHeight;

public:
	MyGameTextBase( float _height, float _width, int _weight, string _fontName, bool _italic );
	virtual ~MyGameTextBase(void);
	void DestroyText();
	//void DrawUIText( const char* _text, int _count, int _x, int _y, int _rectWidth, int _rectHeight, DWORD _format, D3DCOLOR _corlor );
	void DrawUIText( wchar_t* _text, int _count, LPRECT _rect, DWORD _format, D3DCOLOR _color );
	void DrawUIText( const char* _text, int _count, LPRECT _rect, DWORD _format, D3DCOLOR _color );
	//static void SetDevice( MyGame3DDevice* _pDevice ){
	//	pDevice = _pDevice->GetDevice();
	//}
	static void SetDevice( LPDIRECT3DDEVICE9 _pDevice )
	{
		pDevice = _pDevice;
	}



	
	void	SetDestRectForScreen(int _x, int _y, int _width, int _height);
	void	SetDestRectForTexture( int _x, int _y, int _width, int _height);
	void	SetRect(int _x, int _y, int _width, int _height);
	int		SetText(const char*);
	void	SetCount(int _count);
	void	SetDialogRect( int _x, int _y, int _width, int _height );
	void	SetColor( D3DCOLOR _color );
	void	SetFormat( DWORD _format );
	virtual void	RenderText();
};

