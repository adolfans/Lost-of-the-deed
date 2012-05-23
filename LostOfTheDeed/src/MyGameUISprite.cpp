#include "StdAfx.h"
#include "MyGameUISprite.h"
#include "MyGameFunctions.h"
#include "MyGameTextBase.h"
#include "Resource.h"
#include <iostream>
#include <exception>
using std::exception;
using std::runtime_error;
using std::cout;

//WORD							MyGameUISprite::index[6]={ 0, 1, 2, 2, 1, 3 };
//map< string, MyGameUISprite* >	MyGameUISprite::spriteListTransparent; 
map< int, MyGameUISprite* >		MyGameUISprite::spriteListTransparentIntKey;
map< string, MyGameUISprite* >	MyGameUISprite::spriteListOpaque;
IDirect3DDevice9*				MyGameUISprite::pD3D9InstanceDevice = 0;

int								MyGameUISprite::cursorX		= 0;
int								MyGameUISprite::cursorY		= 0;


bool							MyGameUISprite::clicked = false;


MyGameUISprite::MyGameUISprite( string _fileName,bool _transparent, int _key, float _x, float _y, int _width, int _height )
	:visible(true),
	//pSpriteTexture(0),
	key(_key),
	transparency(_transparent),
	pTexture(0)
{
	if( _fileName.size() == 0 )
		return;

	try{

		if( MyGameUISprite::pD3D9InstanceDevice == 0 )
			throw runtime_error("device of MyGameUISprite is not set");
		
		//HR(D3DXCreateTextureFromFileExA(pD3D9InstanceDevice,
		//						_fileName.c_str(),
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						D3DFMT_INDEX16,
		//						D3DPOOL_MANAGED,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						NULL,
		//						NULL,
		//						&pSpriteTexture));

		pTexture = MyGame3DDevice::CreateMyTextureFromFile( _fileName.c_str() );
		
		myVertex vertices[4];
		vertices[0].pos.x = (float)_x;
		vertices[0].pos.y = (float)_y;
		vertices[0].pos.z = (float)key;
		vertices[0].texCoord.x = 0.0f;
		vertices[0].texCoord.y = 0.0f;
		vertices[1].pos.x = (float)( _x + _width );
		vertices[1].pos.y = (float)_y;
		vertices[1].pos.z = (float)key;
		vertices[1].texCoord.x = 1.0f;
		vertices[1].texCoord.y = 0.0f;
		vertices[2].pos.x = (float)_x;
		vertices[2].pos.y = (float)( _y + _height );
		vertices[2].pos.z = (float)key;
		vertices[2].texCoord.x = (float)0.0f;
		vertices[2].texCoord.y = (float)1.0f;
		vertices[3].pos.x = (float)( _x + _width);
		vertices[3].pos.y = (float)( _y + _height );
		vertices[3].pos.z = (float)key;
		vertices[3].texCoord.x = 1.0f;
		vertices[3].texCoord.y = 1.0f;


		int vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, vertices, sizeof(myVertex)*4 );

		vertexBuffer _tmpBuffer = { vertexBufferKey, true, _x, _y, _width, _height, 0, 0 };

		vertexBufferList[0] = (_tmpBuffer);
		
		if( _transparent )
			spriteListTransparentIntKey[ key ] = this;
		else
			spriteListOpaque[_fileName] = this;

		this->textureName = _fileName;

		this->transparency = _transparent;
	}catch( runtime_error e)
	{
		cout<<"MyGameUISprite.cpp"<<e.what();
	}
}

MyGameUISprite::MyGameUISprite( string _fileName, bool _transparent, int _key )
	:key( _key ),
	visible( true ),
	transparency( _transparent ),
	pTexture( 0 )
{
	if( MyGameUISprite::pD3D9InstanceDevice == 0 )
			throw runtime_error("device of MyGameUISprite is not set");
		
		//HR(D3DXCreateTextureFromFileExA(pD3D9InstanceDevice,
		//						_fileName.c_str(),
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						D3DFMT_INDEX16,
		//						D3DPOOL_MANAGED,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						NULL,
		//						NULL,
		//						&pSpriteTexture));


		pTexture = MyGame3DDevice::CreateMyTextureFromFile( _fileName.c_str() );

		if( _transparent )
			spriteListTransparentIntKey[ key ] = this;
		else
			spriteListOpaque[_fileName] = this;

		transparency = _transparent;
}


MyGameUISprite::MyGameUISprite( float _x, float _y, int _width, int _height, int _key )
	:key( _key ),//猎奇了，这段代码没有的话，这个Sprite就不显示————原因已得知\
	因为后面创建vertices的时候用了key。。。而key还没有初始化
	visible( true ),
	transparency( true ),
	pTexture( 0 )
{
	//MyGameUISprite( "background.jpg", true, _key, _x, _y, _width, _height );
		try{

		if( MyGameUISprite::pD3D9InstanceDevice == 0 )
			throw runtime_error("device of MyGameUISprite is not set");
		
		//HR(D3DXCreateTextureFromFileExA(pD3D9InstanceDevice,
		//						_fileName.c_str(),
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						D3DFMT_INDEX16,
		//						D3DPOOL_MANAGED,
		//						D3DX_DEFAULT,
		//						D3DX_DEFAULT,
		//						0,
		//						NULL,
		//						NULL,
		//						&pSpriteTexture));

		pTexture = MyGame3DDevice::CreateMyTextureForText( _width, _height );
		
		myVertex vertices[4];
		vertices[0].pos.x = (float)_x;
		vertices[0].pos.y = (float)_y;
		vertices[0].pos.z = (float)key;
		vertices[0].texCoord.x = 0.0f;
		vertices[0].texCoord.y = 0.0f;
		vertices[1].pos.x = (float)( _x + _width );
		vertices[1].pos.y = (float)_y;
		vertices[1].pos.z = (float)key;
		vertices[1].texCoord.x = 1.0f;
		vertices[1].texCoord.y = 0.0f;
		vertices[2].pos.x = (float)_x;
		vertices[2].pos.y = (float)( _y + _height );
		vertices[2].pos.z = (float)key;
		vertices[2].texCoord.x = (float)0.0f;
		vertices[2].texCoord.y = (float)1.0f;
		vertices[3].pos.x = (float)( _x + _width);
		vertices[3].pos.y = (float)( _y + _height );
		vertices[3].pos.z = (float)key;
		vertices[3].texCoord.x = 1.0f;
		vertices[3].texCoord.y = 1.0f;


		int vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, vertices, sizeof(myVertex)*4 );

		vertexBuffer _tmpBuffer = { vertexBufferKey, true, _x, _y, _width, _height, 0, 0 };

		vertexBufferList[0] = (_tmpBuffer);
		
		this->key = _key;

		spriteListTransparentIntKey[ _key ] = this;

		this->textureName = "background.jpg";//这是瞎写

		this->transparency = true;
	}catch( runtime_error e)
	{
		cout<<"MyGameUISprite.cpp"<<e.what();
	}
	
	//delete pTexture;
	
	//		myVertex vertices[4];
	//	vertices[0].pos.x = (float)_x;
	//	vertices[0].pos.y = (float)_y;
	//	vertices[0].pos.z = (float)key;
	//	vertices[0].texCoord.x = 0.0f;
	//	vertices[0].texCoord.y = 0.0f;
	//	vertices[1].pos.x = (float)( _x + _width );
	//	vertices[1].pos.y = (float)_y;
	//	vertices[1].pos.z = (float)key;
	//	vertices[1].texCoord.x = 1.0f;
	//	vertices[1].texCoord.y = 0.0f;
	//	vertices[2].pos.x = (float)_x;
	//	vertices[2].pos.y = (float)( _y + _height );
	//	vertices[2].pos.z = (float)key;
	//	vertices[2].texCoord.x = (float)0.0f;
	//	vertices[2].texCoord.y = (float)1.0f;
	//	vertices[3].pos.x = (float)( _x + _width);
	//	vertices[3].pos.y = (float)( _y + _height );
	//	vertices[3].pos.z = (float)key;
	//	vertices[3].texCoord.x = 1.0f;
	//	vertices[3].texCoord.y = 1.0f;


	//	int vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, vertices, sizeof(myVertex)*4 );

	//	vertexBuffer _tmpBuffer = { vertexBufferKey, true, _x, _y, _width, _height, 0, 0 };

	//	vertexBufferList[0] = (_tmpBuffer);

	//pTexture = MyGame3DDevice::CreateMyTextureForText( _width, _height );
	//this->key = _key;
	//spriteListTransparentIntKey[ _key ] = this;
	//transparency = true;
}

//void MyGameUISprite::CreateRectangle( string _name, float _u1, float _v1, float _u2, float _v2, float _x, float _y, float _width, float _height, float _z)
void MyGameUISprite::CreateRectangle( int _rectID, float _u1, float _v1, float _u2, float _v2, float _x, float _y, float _width, float _height, float _z)
{
	myVertex vertices[4];
		vertices[0].pos.x = (float)_x;
		vertices[0].pos.y = (float)_y;
		vertices[0].pos.z = (float)_z;
		vertices[0].texCoord.x = _u1;
		vertices[0].texCoord.y = _v1;
		vertices[1].pos.x = (float)( _x + _width );
		vertices[1].pos.y = (float)_y;
		vertices[1].pos.z = (float)_z;
		vertices[1].texCoord.x = _u2;
		vertices[1].texCoord.y = _v1;
		vertices[2].pos.x = (float)_x;
		vertices[2].pos.y = (float)( _y + _height );
		vertices[2].pos.z = (float)_z;
		vertices[2].texCoord.x = _u1;
		vertices[2].texCoord.y = _v2;
		vertices[3].pos.x = (float)( _x + _width);
		vertices[3].pos.y = (float)( _y + _height );
		vertices[3].pos.z = (float)_z;
		vertices[3].texCoord.x = _u2;
		vertices[3].texCoord.y = _v2;

		int vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, vertices, sizeof(myVertex)*4 );

		vertexBuffer _tmpBuffer = { vertexBufferKey, true, _x, _y, _width, _height, 0.0f, 0.0f, false, 0.0f, 0.0f, false };

		vertexBufferList[_rectID] = (_tmpBuffer);
		
}


void MyGameUISprite::CreateRectangleWithIntKey( int _rectID, float _u1, float _v1, float _u2, float _v2, float _x, float _y, float _width, float _height )
{
	myVertex vertices[4];
		vertices[0].pos.x = (float)_x;
		vertices[0].pos.y = (float)_y;
		vertices[0].pos.z = (float)key;
		vertices[0].texCoord.x = _u1;
		vertices[0].texCoord.y = _v1;
		vertices[1].pos.x = (float)( _x + _width );
		vertices[1].pos.y = (float)_y;
		vertices[1].pos.z = (float)key;
		vertices[1].texCoord.x = _u2;
		vertices[1].texCoord.y = _v1;
		vertices[2].pos.x = (float)_x;
		vertices[2].pos.y = (float)( _y + _height );
		vertices[2].pos.z = (float)key;
		vertices[2].texCoord.x = _u1;
		vertices[2].texCoord.y = _v2;
		vertices[3].pos.x = (float)( _x + _width);
		vertices[3].pos.y = (float)( _y + _height );
		vertices[3].pos.z = (float)key;
		vertices[3].texCoord.x = _u2;
		vertices[3].texCoord.y = _v2;

		int vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, vertices, sizeof(myVertex)*4 );

		vertexBuffer _tmpBuffer = { vertexBufferKey, true, _x, _y, _width, _height, 0.0f, 0.0f, false, 0.0f, 0.0f, false };
		
		vertexBufferList[_rectID] = (_tmpBuffer);
		
}


MyGameUISprite::~MyGameUISprite(void)
{
	//if(visible||/* || pSpriteTexture*/ )				//TODO:
		//DestroySprite();

	for (map<int,vertexBuffer>::iterator _itr = vertexBufferList.begin();
	//for (map<string,vertexBuffer>::iterator _itr = vertexBufferList.begin();
		_itr != vertexBufferList.end();
		++_itr )
	{
		MyGame3DDevice::DestroyVertexBuffer( (*_itr).second.vertexBufferKey );
	}
	delete pTexture;

	this->pTexture = 0;

	this->visible = false;

	if( this->transparency )
	{	//spriteListTransparent.erase( textureName );
		spriteListTransparentIntKey.erase( key );
	}
	else
		spriteListOpaque.erase( textureName );
}

void MyGameUISprite::SetText( const char* _text, MyGameTextBase* _textObj, MyGameUISprite* _bgSprite, int _rectKey )
{
	//pTexture->SetTextOfTexture( _text, _textObj, _targetSprite->pTexture, MyGame3DDevice::GetVertexBufferFromKey(_targetSprite->vertexBufferList[_rectKey].vertexBufferKey) );
	MyGame3DDevice::StartRenderToTexture( this->pTexture );
		MyGame3DDevice::StartRenderUI();
			MyGame3DDevice::EnableUIAlphaBlending();
			_textObj->RenderText();
			MyGame3DDevice::EnableMyUITexture( _bgSprite->pTexture );
			MyGame3DDevice::SetVertexBuffer( _bgSprite->vertexBufferList[_rectKey].vertexBufferKey );
			//_textObj->DrawUIText( _text, 30, NULL, 0, 0xFF000000 );
			MyGame3DDevice::DrawIndexedTrianglePrimitive( 4, 2 );
		MyGame3DDevice::EndRenderUI();
	MyGame3DDevice::EndRenderToTexture();
	this->pTexture->SaveTexutureToPng( "囧.png" );
}

void MyGameUISprite::DestroySprite()
{
	for (map<int,vertexBuffer>::iterator _itr = vertexBufferList.begin();
	//for (map<string,vertexBuffer>::iterator _itr = vertexBufferList.begin();
		_itr != vertexBufferList.end();
		++_itr )
	{
		MyGame3DDevice::DestroyVertexBuffer( (*_itr).second.vertexBufferKey );
	}
	delete pTexture;

	this->pTexture = 0;

	this->visible = false;
}

void MyGameUISprite::RenderAllSprites()
{

	MyGame3DDevice::StartRenderUI();

		for( map< string, MyGameUISprite* >::iterator _itr = spriteListOpaque.begin();
			_itr != spriteListOpaque.end();
			++_itr )

			( *_itr ).second->RenderUISprite();

		MyGame3DDevice::EnableUIAlphaBlending();

		//for( map< string, MyGameUISprite* >::iterator _itr = spriteListTransparent.begin();
		//	_itr != spriteListTransparent.end();
		//	++_itr )
		//
		//	( *_itr ).second->RenderUISprite();

		for( map< int, MyGameUISprite* >::iterator _itr = spriteListTransparentIntKey.begin();
			_itr != spriteListTransparentIntKey.end();
			++_itr )

			( *_itr ).second->RenderUISprite();
		
	MyGame3DDevice::EndRenderUI();
}

void MyGameUISprite::SetVisibility( bool _visible)
{
	this->visible = _visible;
}

void MyGameUISprite::RenderUISprite()
{
	if( false==visible )
		return;
	//MyGame3DDevice::TestEnableTexture( pSpriteTexture );
	MyGame3DDevice::EnableMyUITexture( this->pTexture );
	//for (map<string,vertexBuffer>::iterator _itr = vertexBufferList.begin();
	for (map<int,vertexBuffer>::iterator _itr = vertexBufferList.begin();
		_itr != vertexBufferList.end();
		++_itr )
	{
		vertexBuffer currentVertexBuffer = (*_itr).second;
		if( true == currentVertexBuffer.visible )
		{
			// if offset is not 0
			//if( (currentVertexBuffer.offsetX >= -0.0001f)&&(currentVertexBuffer.offsetX <= 0.0001f) || 
			//	(currentVertexBuffer.offsetY >= -0.0001f)&&(currentVertexBuffer.offsetY <= 0.0001f) )
			if( currentVertexBuffer.moved )
			{
				MyGame3DDevice::MoveUIMatrix( currentVertexBuffer.offsetX, currentVertexBuffer.offsetY );
			}

			if( currentVertexBuffer.scaled )
			{
				MyGame3DDevice::ScaleUIMatrix( currentVertexBuffer.scaleX, currentVertexBuffer.scaleY );
			}
				
			//HR(pD3D9InstanceDevice->SetStreamSource( 0,
			//								(currentVertexBuffer.pVertexBuffer),
			//								0,
			//								sizeof( myVertex )));

			MyGame3DDevice::SetVertexBuffer( currentVertexBuffer.vertexBufferKey );
	
			MyGame3DDevice::DrawIndexedTrianglePrimitive( 4, 2 );
			//if( currentVertexBuffer.offsetX != 0 || currentVertexBuffer.offsetY != 0 )
			if( currentVertexBuffer.moved || currentVertexBuffer.scaled )
				MyGame3DDevice::ResetUIMatrix();
		}
	}
}

bool IfPosInRect( int _x, int _y, RECT _rect )
{
	if( _x > _rect.left && _x < _rect.right && _y > _rect.top && _y < _rect.bottom )
		return true;
	else
		return false;

}
//bool MyGameUISprite::IfCursorInRect( const char* _rectName )
bool MyGameUISprite::IfCursorInRect( int _rectID )
{
	//vertexBuffer rectBuffer = this->vertexBufferList[_rectName];
	if( !vertexBufferList.count(_rectID) )
		return false;
	vertexBuffer rectBuffer = this->vertexBufferList[_rectID];
	RECT rect;
	rect.left = rectBuffer.x;
	rect.right = rectBuffer.x + rectBuffer.width;
	rect.top = rectBuffer.y;
	rect.bottom = rectBuffer.y + rectBuffer.height;
	return IfPosInRect( cursorX, cursorY, rect );
}

bool MyGameUISprite::IfCursorInRectClicked( int _rectID )
{
	if(!IfCursorInRect( _rectID ))
		return false;
	if(clicked)
		return true;
	else
		return false;

}

bool MyGameUISprite::MoveRect( int _rectID, float _offsetX, float _offsetY )
{
	map<int, vertexBuffer>::iterator _itr = this->vertexBufferList.find( _rectID );
	if( _itr == vertexBufferList.end() )
		return false;
	(*_itr).second.offsetX = _offsetX;
	(*_itr).second.offsetY = _offsetY;
	(*_itr).second.moved	= true;
	return true;
}

bool MyGameUISprite::ScaleRect( int _rectID, float _scaleX, float _scaleY )
{
	map<int, vertexBuffer>::iterator _itr = this->vertexBufferList.find( _rectID );
	if( _itr == vertexBufferList.end() )
		return false;
	(*_itr).second.scaleX = _scaleX;
	(*_itr).second.scaleY = _scaleY;
	(*_itr).second.scaled	= true;
	return true;
}

void MyGameUISprite::DestroyAllSprites()
{
	
		//for( map< string, MyGameUISprite* >::iterator _itr = spriteListTransparent.begin();
		//	_itr != spriteListTransparent.end();
		//	++_itr )
		//{

		//	( *_itr ).second->DestroySprite();
		//}

		for( map< string, MyGameUISprite* >::iterator _itr = spriteListOpaque.begin();
			_itr != spriteListOpaque.end();
			++_itr )
		{

			( *_itr ).second->DestroySprite();
		}

		for( map< int, MyGameUISprite* >::iterator _itr = spriteListTransparentIntKey.begin();
			_itr != spriteListTransparentIntKey.end();
			++_itr )
		{

			( *_itr ).second->DestroySprite();
		}

		//pIndexBuffer->Release();
		
}