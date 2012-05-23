#pragma once
//#include "MyGame3DDevice.h"
//#include <d3dx9.h>
#include "MyGameTextBase.h"
#include "MyGameVertexBuffer.h"
class MyGameTexture
{
private:
	IDirect3DTexture9* pD9Texture;
	static IDirect3DDevice9*	pD9Device;
	bool				forText;
public:
	MyGameTexture( const char* _fileName );
	MyGameTexture( int _width, int _height );	//create an empty texture for text
	~MyGameTexture(void);
	void SetTextOfTexture( const char* _text, MyGameTextBase* _textObj, MyGameTexture* targetTexture, MyGameVertexBuffer* pVertexBuffer );
	void MyGameTexture::SaveTexutureToPng( const char* _fileName);
	//void EnableMyGameTexture();
	IDirect3DTexture9* GetD9Texture();
	static void SetTextureDevice( IDirect3DDevice9* _d9Device );
};

