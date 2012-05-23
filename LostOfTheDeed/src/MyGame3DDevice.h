#pragma once
#include "MyGameFunctions.h"
#include "MyGame3DEffect.h"
#ifdef DX9
#include <d3d9.h>
#include <D3dx9math.h>
#pragma comment (lib, "D3D9.lib")
#pragma comment (lib, "d3dx9.lib")
#endif
#ifdef DX11
#include <D3D11.h>
#include <D3DX11.h>
#include <DXGI.h>
#endif
#include <D3Dcompiler.h>
#include "MyGameWindow.h"
#include "MyGameTexture.h"
#include "MyGameVertexBuffer.h"
#include <map>
using std::map;

enum VertexType{
	uiVertex
};


typedef struct myVertex{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texCoord;
//	float u, v;
}myVertex;

class MyGame3DDevice
{
private:
	static	MyGameWindow*			pGameWindow;
	static	MyGame3DDevice*			pMyGameDevice;

	//D3D9
#ifdef DX9
	D3DPRESENT_PARAMETERS			d3dpp;
	IDirect3DVertexDeclaration9*	pMyGameUIVertexDecl;
	IDirect3DDevice9*				pD3D9InstanceDevice;
	IDirect3D9*						d3d9;


	///
	///D3D9 UI
	///
	ID3DXEffect*					mFX;
	
	D3DXHANDLE		mhTex;

	D3DXHANDLE		mhUIWorldMatHandle;
	D3DXHANDLE		mhUIViewMatHandle;
	D3DXHANDLE		mhUIProjMatHandle;
	D3DXHANDLE		mhUIMoveMatHandle;
	D3DXHANDLE		mhAlphaEnabled;

	const char*		worldMatName;
	const char*		viewMatName;
	const char*		projMatName;
	const char*		moveMatName;
	const char*		techniqueName;
	const char*		textureHandleName;

	D3DXMATRIX		uiMoveMatrix;
	const D3DXMATRIX uiMoveMatrix0;

	WORD uiRectIndices[6];
	IDirect3DIndexBuffer9* pUIIndexBuffer;

	IDirect3DSurface9*		pScreenTarget;

	IDirect3DSurface9*		pTextureTarget;


	///
	///D3D9 Scenes
	///
	ID3DXEffect*					mSceneFX;
	
	D3DXHANDLE		mhSceneTex;

	D3DXHANDLE		mhSceneWorldMatHandle;
	D3DXHANDLE		mhSceneViewMatHandle;
	D3DXHANDLE		mhSceneProjMatHandle;
	D3DXHANDLE		mhSceneMoveMatHandle;
	D3DXHANDLE		mhSceneAlphaEnabled;		//must be enabled

	const char*		sceneWorldMatName;
	const char*		sceneViewMatName;
	const char*		sceneProjMatName;
	const char*		sceneMoveMatName;
	const char*		sceneTechniqueName;
	const char*		sceneTextureHandleName;

	D3DXMATRIX		sceneMoveMatrix;
	//const D3DXMATRIX sceneMoveMatrix0;

	//WORD uiRectIndices[6];
	//IDirect3DIndexBuffer9* pSceneIndexBuffer;

	//IDirect3DSurface9*		pScreenTarget;

	//IDirect3DSurface9*		pTextureTarget;



	//private functions
	bool							InitD3DDevice9();
	
#endif
	
	//D3D11
#ifdef DX11
	typedef struct D3D11Variables
	{
		ID3D11Device*			pD3D11InstanceDevice;
		ID3D11DeviceContext*	pD3D11DeviceContext;
		D3D_FEATURE_LEVEL		d3d11FeatureLevel;
		ID3D11RenderTargetView* pRenderTargetView;
	
	}D3D11Variables;
	D3D11Variables d3d11Objects;
	bool	InitD3DDevice11();

#endif

	//
	//private functions:
	//
private:
	MyGame3DDevice(void);
	bool	InitDevice();
	void	InitUIEffectShader();
	void	InitSceneEffectShader();
	//
	//public functions
	//
public:
	~MyGame3DDevice(void);
	static void	SetGameWindow( MyGameWindow* _pGameWindow );
	static MyGame3DDevice* GetMyDevice();
	bool					InitVertexDecl( D3DVERTEXELEMENT9* _decl );
	
	//
	//render controller
	//
	void StartRender();
	void EndRender();

	static void StartRenderToTexture( MyGameTexture* _targetTexture );

	static void EndRenderToTexture();
	//
	//Texture controller
	//
	//static MyGameTexture* CreateMyTextureFromFile( const char* _fileName );		//return texture ID
	//static MyGameTexture* CreateMyTextureForText();
	static MyGameTexture* CreateMyTextureFromFile( const char* _fileName );
	static MyGameTexture* CreateMyTextureForText(int _width, int _height);
	//ui texture controller
	static void EnableMyUITexture( MyGameTexture* _pTexture);

	static void EnableTexture( MyGameTexture* _pTexture );

	static void TestEnableTexture( IDirect3DTexture9* );

	//
	//UI	controller
	//
	void InitUIIndexBuffer();
	void DestroyUIIndexBuffer();
	static void StartRenderUI();
	static void EndRenderUI();
	static void MoveUIMatrix( float, float);
	static void ScaleUIMatrix( float, float );
	static void ResetUIMatrix();
	static void DisableUIAlphaBlending();
	static void EnableUIAlphaBlending();

	//
	//vertex buffer controller
	//
	//typedef struct myVertexBuffer{
	//	IDirect3DVertexBuffer9* vertexBuffer;
	//	unsigned	int			bufferSize;
	//}myVertexBuffer;
	map< unsigned int, MyGameVertexBuffer* > myVertexBufferList;
	static int CreateVertexBuffer( VertexType _type, void* vertices, unsigned int verticeSize );
	static void SetVertexBuffer(int);
	static MyGameVertexBuffer* GetVertexBufferFromKey( int _key )
	{	return pMyGameDevice->myVertexBufferList[ _key ]; }
	static void DrawIndexedTrianglePrimitive(int, int );
	static void DrawTrianglePrimitive( D3DPRIMITIVETYPE _type, UINT StartVertex, UINT PrimitiveCount );  
	static void DestroyVertexBuffer( int _bufferKey );


	//others
	static int GetWidth()
	{	return pMyGameDevice->d3dpp.BackBufferWidth;}
	static int GetHeight()
	{	return pMyGameDevice->d3dpp.BackBufferHeight;}
#ifdef DX9	
	IDirect3DDevice9* GetDevice();
#endif
//	void	SetDeviceVersion(D3DXVERSION _deviceVersion);


	//Effect
	static MyGame3DEffect*	CreateEffectFromResourceID( int _rsID );

};

