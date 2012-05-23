#pragma once
#include <d3dx9.h>
#include <map>
#include <string>
#include <vector>
using std::vector;
using std::map;
using std::string;
#include "MyGame3DDevice.h"
#include "MyGameTexture.h"
class MyGameUISprite
{
	

	typedef struct rectVertexBuffer{
		//IDirect3DVertexBuffer9* pVertexBuffer;
		int						vertexBufferKey;
		bool					visible;
		int						x;
		int						y;
		int						width;
		int						height;
		float					offsetX;
		float					offsetY;
		bool					moved;
		float					scaleX;
		float					scaleY;
		bool					scaled;
	}vertexBuffer;
private:
	bool	visible;
	bool	transparency;
	int		key;
	//int		textureKey;
	MyGameTexture* pTexture;
	//IDirect3DTexture9* pSpriteTexture;
	//map< string, vertexBuffer>	vertexBufferList;
	map< int, vertexBuffer>	vertexBufferList;
	string textureName;
	//static map< string, MyGameUISprite* > spriteListTransparent;
	static map< int, MyGameUISprite* > spriteListTransparentIntKey;
	static map< string, MyGameUISprite* > spriteListOpaque;
	static IDirect3DDevice9* pD3D9InstanceDevice;
	static	int				cursorX;
	static	int				cursorY;
	static	bool			clicked;
public:
	MyGameUISprite( string _fileName,bool _transparent, int _key, float _x, float _y, int _width, int _height );
	MyGameUISprite( string _fileName, bool _transparent, int _key );
	MyGameUISprite( float _x, float _y, int _width, int _height, int _key );
	virtual ~MyGameUISprite(void);
	void	DestroySprite();
	virtual void SetVisibility(bool);
	bool GetVisibility(){ return this->visible; }
	void	SetText( const char* _text, MyGameTextBase* _textObj, MyGameUISprite* _bgSprite, int _rectKey );
	void SetRectVisibility( int _rectID, bool _visible )
	{ 
		if( !vertexBufferList.count( _rectID ) )
			return;
		vertexBufferList[_rectID].visible = _visible;}
	void CreateRectangle( int, float _u1, float _v1, float _u2, float _v2, float _x, float _y, float _width, float _height, float _z);
	void CreateRectangleWithIntKey( int, float _u1, float _v1, float _u2, float _v2, float _x, float _y, float _width, float _height );

	virtual void RenderUISprite();
	
	bool IfCursorInRect( int );

	bool IfCursorInRectClicked( int );

	void DisableAllRects(){
		for( map< int, vertexBuffer>::iterator _itr = vertexBufferList.begin();
			_itr != vertexBufferList.end();
			++ _itr )
		{
			(*_itr).second.visible = false;
		}
	}

	bool MoveRect( int _rectID, float _offsetX, float _offsetY );

	bool ScaleRect( int _rectID, float _scaleX, float _scaleY );
	
	static void SetDevice( IDirect3DDevice9* _pD3D9InstanceDevice )
	{ pD3D9InstanceDevice = _pD3D9InstanceDevice;}

	static void RenderAllSprites();
	static void SetCursorPos( int _x, int _y){ cursorX = _x; cursorY = _y ;}
	static void SetClicked(bool _clicked){ clicked = _clicked;}
	static void DestroyAllSprites();
};
