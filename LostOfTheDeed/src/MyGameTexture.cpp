#include "StdAfx.h"
#include "MyGameTexture.h"

IDirect3DDevice9* MyGameTexture::pD9Device = 0;

MyGameTexture::MyGameTexture( const char* _fileName )
	:pD9Texture(0),forText(false)
{
	// create texture from file name for d3d9
	HR(D3DXCreateTextureFromFileExA( pD9Device,
								_fileName,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								0/*D3DUSAGE_RENDERTARGET*/,
								D3DFMT_A8R8G8B8,
								/*D3DPOOL_MANAGED*/D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								0,
								NULL,
								NULL,
								&pD9Texture));
}

MyGameTexture::MyGameTexture( int _width, int _height )
	:pD9Texture(0),forText(true)
{
	//if( pD9Texture )
	//	pD9Texture->Release();		//if it was created, release it first

	HR( pD9Device->CreateTexture( _width,
									_height,
									1,
									D3DUSAGE_RENDERTARGET,
									D3DFMT_A8R8G8B8,
									D3DPOOL_DEFAULT,
									&pD9Texture,
									NULL ) );
}

void MyGameTexture::SetTextOfTexture( const char* _text, MyGameTextBase* _textObj, MyGameTexture* targetTexture, MyGameVertexBuffer* pVertexBuffer )
{
	//save current RenderTarget
	IDirect3DSurface9*		pRenderScreenTarget = 0;

	HR( pD9Device->GetRenderTarget( 0, &pRenderScreenTarget ) );

	//set current render texture

	IDirect3DSurface9*		pRenderTextureSurface = 0;

	HR( pD9Texture->GetSurfaceLevel( 0, &pRenderTextureSurface ) );

	HR( pD9Device->SetRenderTarget( 0, pRenderTextureSurface ) );

	//render text to texture
	{
		HR( pD9Device->BeginScene() );
		HR( pD9Device->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00ffffff, 1.0f, 0 ) );
		HR( pD9Device->SetTexture( 0, targetTexture->GetD9Texture() ) );
		HR( pD9Device->SetStreamSource( 0, pVertexBuffer->GetVertexBuffer(), 0, pVertexBuffer->GetBufferSize() ) );
		HR( pD9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2)  );
		HR( pD9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE) );
		HR( pD9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA) );
		HR(	pD9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA) );
// pD9Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE , TRUE);
// pD9Device->SetRenderState(D3DRS_SRCBLENDALPHA , D3DBLEND_SRCALPHA);  
// pD9Device->SetRenderState(D3DRS_DESTBLENDALPHA , D3DBLEND_DESTALPHA);
// pD9Device->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MAX);
		_textObj->DrawUIText( _text, 30, NULL, 0, 0xFF000000 );
		
		//HR( D3DXSaveSurfaceToFileW( L"‡å.tga", D3DXIFF_TGA  , pRenderTextureSurface, 0, 0 ) );
		HR( pD9Device->EndScene() );
	}
	
	//restore renderTarget
	HR( pD9Device->SetRenderTarget(0, pRenderScreenTarget) );


	//RELEASE THEM !!!! OR THEY'LL CAUSE MEMORY LEAK!!!
	pRenderScreenTarget->Release();

	pRenderTextureSurface->Release();
	HR( D3DXSaveTextureToFile( L"‡å.png",D3DXIFF_PNG,pD9Texture, NULL ) );
}

void MyGameTexture::SaveTexutureToPng( const char* _fileName)
{
	D3DXSaveTextureToFileA( _fileName, D3DXIFF_PNG, this->pD9Texture, NULL );
}

MyGameTexture::~MyGameTexture(void)
{
	if(pD9Texture)
	{
		pD9Texture->Release();
		//if(forText)
		//	pD9Texture->Release();
		pD9Texture = 0;
	}
}

void MyGameTexture::SetTextureDevice( IDirect3DDevice9* _d9Device )
{
	static bool _deviceSetted = false;
	if( _deviceSetted == false )
		pD9Device = _d9Device;
	else{
		MyGameMessage("texture device has already been setted!");
		return;
	}
}

IDirect3DTexture9* MyGameTexture::GetD9Texture()
{
	return pD9Texture;
}