#include "StdAfx.h"
#include "MyGame3DDevice.h"
#include "Resource.h"

#include "MyGameTexture.h"
#include "MyGame3DEffect.h"

MyGame3DDevice*	MyGame3DDevice::pMyGameDevice = 0;
MyGameWindow*	MyGame3DDevice::pGameWindow		= 0;

MyGame3DDevice::MyGame3DDevice(void)
	:
#ifdef DX9
	pMyGameUIVertexDecl(0),
	pD3D9InstanceDevice(0),
	uiMoveMatrix0( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ),
	uiMoveMatrix( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ),
	worldMatName( "gUIWorld" ),
	viewMatName( "gUIView" ),
	projMatName( "gUIProj" ),
	moveMatName( "gUIMove" ),
	techniqueName( "TransformTech" ),
	textureHandleName( "gTex" ),
	pUIIndexBuffer( 0 ),
	d3dpp(),
	mFX(0),
	mhTex(0),
	mhUIWorldMatHandle(0),
	mhUIViewMatHandle(0),
	mhUIProjMatHandle(0),
	mhUIMoveMatHandle(0),
	mhAlphaEnabled(0),
	pScreenTarget(0),
	pTextureTarget(0)
#endif
{
	uiRectIndices[0] = 0;
	uiRectIndices[1] = 1;
	uiRectIndices[2] = 2;
	uiRectIndices[3] = 2;
	uiRectIndices[4] = 1;
	uiRectIndices[5] = 3;/*{ 0, 1, 2, 2, 1, 3 };*/
}

	//typedef void (*new_handler) ();
	//new_handler set_new_handler( new_handler p ) throw();


/*
void MyGame3DDevice::SetDeviceVersion(D3DXVERSION _deviceVersion)
{
	this->deviceVersion = _deviceVersion;
}*/


bool MyGame3DDevice::InitVertexDecl( D3DVERTEXELEMENT9* _decl )
{
	if( pMyGameUIVertexDecl )
	{
		MyGameMessage( "VertexDeclaration was already initialized" );
		return true;
	}
	if( FAILED( pD3D9InstanceDevice->CreateVertexDeclaration
							( _decl, &pMyGameUIVertexDecl ) ) )
	{
		MyGameMessage("CreateVetexDeclaration error!!");
		return false;
	}
	if(FAILED(pD3D9InstanceDevice->SetVertexDeclaration( pMyGameUIVertexDecl )))
	{	MyGameMessage("set vertex declaration error");
		
	}
	return true;
}
bool MyGame3DDevice::InitDevice()
{
		////////////////////////////////
		//if choosed D3DX9
		////////////////////////////////
#ifdef DX9
		MyGameMessage("using d3d9");
		return InitD3DDevice9();
#endif

		////////////////////////////////
		//if choosed D3DX11
		////////////////////////////////
#ifdef DX11
		MyGameMessage("using d3d11");
		return InitD3DDevice11();
#endif
}

#ifdef DX9
IDirect3DDevice9* MyGame3DDevice::GetDevice()
{
	return pD3D9InstanceDevice;
}
#endif
MyGame3DDevice* MyGame3DDevice::GetMyDevice()
{
	if(pMyGameDevice)
		return pMyGameDevice;
	pMyGameDevice = new MyGame3DDevice;
	pMyGameDevice->InitDevice();
	
	//
	//init UI vertex declaration
	//
	D3DVERTEXELEMENT9 decl[]=
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_POSITION, 0},
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_NORMAL, 0},
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	pMyGameDevice->InitVertexDecl( decl );
	//init effect shader
	pMyGameDevice->InitUIEffectShader();
	pMyGameDevice->InitUIIndexBuffer();
	MyGameTexture::SetTextureDevice(pMyGameDevice->GetDevice());
	MyGame3DEffect::SetEffectDevice( pMyGameDevice->GetDevice() );
	MyGameTextBase::SetDevice( pMyGameDevice->GetDevice() );
	return MyGame3DDevice::pMyGameDevice;
}
void MyGame3DDevice::SetGameWindow(MyGameWindow* _pGameWindow)
{
	pGameWindow = _pGameWindow;
}

MyGame3DDevice::~MyGame3DDevice(void)
{
	
#ifdef DX9
	//Release all the texture in list

	//for( map< int, IDirect3DTexture9* >::iterator _iter = myTextureList.begin();
	//for( map< int, MyGameTexture* >::iterator _iter = myTextureList.begin();
	//	_iter != myTextureList.end();
	//	++ _iter )
	//{	/*( *_iter ).second->Release();*/
	//	delete ( *_iter ).second;
	//}
		//IRelease(pUIIndexBuffer);
		//IRelease(pUIIndexBuffer);
		pUIIndexBuffer->Release();
		IRelease( mFX );
		IRelease( pMyGameUIVertexDecl );
		//pD3D9InstanceDevice->Release();
		//pD3D9InstanceDevice->Release();
		//pD3D9InstanceDevice->Release();
		IRelease(pD3D9InstanceDevice);
		//this->d3d9->Release();
		//d3d9->Release();
		//d3d9->Release();
		//this->d3d9->Release();
		//this->d3d9->Release();
		IRelease(this->d3d9);
#endif
#ifdef DX11
		IRelease(this->d3d11Objects.pD3D11DeviceContext);
		IRelease(this->d3d11Objects.pD3D11InstanceDevice);
		IRelease(this->d3d11Objects.pRenderTargetView);
#endif
}


#ifdef DX9
bool MyGame3DDevice::InitD3DDevice9()
{
	if( pD3D9InstanceDevice )
		return true;
	//Get the pointer to the IDirect3D9 interface
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&caps);

	//check if we can use hardware vertex processing
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	/*
	if( this->wClient != _Width || height != _Height )
		::MessageBox( 0, L"the size of back buffer dosen't adjust the size of window", L"Error", 0 );
*/

	d3dpp.BackBufferWidth			= pGameWindow->GetWidthClient();
	d3dpp.BackBufferHeight			= pGameWindow->GetHeightClient();
	d3dpp.BackBufferFormat			= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount			= 1;
	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		= 0;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow				= pGameWindow->GethWnd();
	d3dpp.Windowed					= true;				//Windowed
	d3dpp.EnableAutoDepthStencil	= true;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;		//depth format
	d3dpp.Flags						= 0;
	d3dpp.FullScreen_RefreshRateInHz= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr;

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		pGameWindow->GethWnd(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&(pD3D9InstanceDevice)
		);
/*
==========================Initialize the global variable -- pd3dDevice
*/

	//d3d9 = 0;

	if(FAILED(hr))
		return false;
	else
//		this->deviceInited = true;
		return true;

}
#endif
#ifdef DX11
bool MyGame3DDevice::InitD3DDevice11()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE driverTypes[] = 
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	::memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = this->wClient;
	sd.BufferDesc.Height = this->hClient;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = this->hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	//driver type 
	D3D_DRIVER_TYPE	g_driverType = D3D_DRIVER_TYPE_NULL;

	//swap chain
	IDXGISwapChain*         g_pSwapChain = NULL;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL,
										g_driverType,
										NULL,
										createDeviceFlags,
										featureLevels,
										numFeatureLevels,
										D3D11_SDK_VERSION,
										&sd,
										&g_pSwapChain,
										&(d3d11Objects.pD3D11InstanceDevice),
										&(d3d11Objects.d3d11FeatureLevel),
										&(d3d11Objects.pD3D11DeviceContext));

		if( SUCCEEDED( hr ) )
			break;

	}
	if( FAILED( hr ) )
		return false;

	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return false;

	hr = d3d11Objects.pD3D11InstanceDevice->CreateRenderTargetView(
											pBackBuffer,
											NULL,
											&(d3d11Objects.pRenderTargetView) );

	pBackBuffer->Release();

	if( FAILED( hr ) )
        return false;

	d3d11Objects.pD3D11DeviceContext->OMSetRenderTargets( 1,
													&(d3d11Objects.pRenderTargetView),
													NULL );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)wClient;
    vp.Height = (FLOAT)hClient;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
	d3d11Objects.pD3D11DeviceContext->RSSetViewports( 1, &vp );

	g_pSwapChain->Release();

	return true;
/*	
    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );

    // Create the input layout
	hr = d3d11Objects.pD3D11InstanceDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &g_pVertexLayout );
*/

}
#endif

void MyGame3DDevice::InitUIEffectShader()
{	
	// load shader
	HRSRC hResource = ::FindResource( NULL, MAKEINTRESOURCE(IDR_PIXEL_SHADER), RT_RCDATA );
	HGLOBAL hResourceData = ::LoadResource( NULL, hResource );
	LPVOID pData = ::LockResource( hResourceData );

	ID3DXBuffer* errorBuffer = 0;
	HR( D3DXCreateEffect( pD3D9InstanceDevice,
							pData,
							::SizeofResource( NULL, hResource ),
							0,
							0,
							0,
							0,
							&mFX,
							&errorBuffer ) );
	if( errorBuffer )
	{
		MyGameMessage( (char*)errorBuffer->GetBufferPointer() );
		errorBuffer->Release();
		return;
	}

	//initialize matrix in shader

	D3DXMATRIX worldMatrix;

	D3DXMatrixTranslation( &worldMatrix, -512.0f, -384.0f, 0 );

	D3DXVECTOR3 position( 0.0f, 0.0f, 20.0f );
	D3DXVECTOR3 targetPoint( 0.0f, 0.0f ,0.0f );
	D3DXVECTOR3 upVector( 0.0f, -1.0f, 0.0f );

	D3DXMATRIX	viewMatrix;

	D3DXMatrixLookAtLH( &viewMatrix, &position, &targetPoint, &upVector );

	D3DXMATRIX  projMatrix;

	D3DXMatrixOrthoLH( &projMatrix, 1024.0f, 768.0f, -1009.0f, 5000.0f );

	D3DXMatrixTranslation( &uiMoveMatrix, 0.0f, 0.0f, 0 );

	mhUIWorldMatHandle	= mFX->GetParameterByName( 0, worldMatName );
	mhUIViewMatHandle	= mFX->GetParameterByName( 0, viewMatName );
	mhUIProjMatHandle	= mFX->GetParameterByName( 0, projMatName );
	mhUIMoveMatHandle	= mFX->GetParameterByName( 0, moveMatName );
	mhAlphaEnabled		= mFX->GetParameterByName( 0, "alphaEnable" );
	D3DXHANDLE mhTech	= mFX->GetTechniqueByName( techniqueName );

	mhTex = mFX->GetParameterByName( 0, "gTex" );

	mFX->SetMatrix( mhUIWorldMatHandle, &worldMatrix );
	mFX->SetMatrix( mhUIViewMatHandle, &viewMatrix );
	mFX->SetMatrix( mhUIProjMatHandle, &projMatrix );
	mFX->SetMatrix( mhUIMoveMatHandle, &uiMoveMatrix );

	mFX->SetTechnique( mhTech );

	HR(mFX->SetBool( mhAlphaEnabled, FALSE ));

	return;
}


void MyGame3DDevice::InitSceneEffectShader()
{
	// load shader
	HRSRC hResource = ::FindResource( NULL, MAKEINTRESOURCE(IDR_PIXEL_SHADER2), RT_RCDATA );
	HGLOBAL hResourceData = ::LoadResource( NULL, hResource );
	LPVOID pData = ::LockResource( hResourceData );

	ID3DXBuffer* errorBuffer = 0;
	HR( D3DXCreateEffect( pD3D9InstanceDevice,
							pData,
							::SizeofResource( NULL, hResource ),
							0,
							0,
							0,
							0,
							&mFX,
							&errorBuffer ) );
	if( errorBuffer )
	{
		MyGameMessage( (char*)errorBuffer->GetBufferPointer() );
		errorBuffer->Release();
		return;
	}

	//initialize matrix in shader

	D3DXMATRIX worldMatrix;

	D3DXMatrixTranslation( &worldMatrix, -512.0f, -384.0f, 0 );

	D3DXVECTOR3 position( 0.0f, 0.0f, 20.0f );
	D3DXVECTOR3 targetPoint( 0.0f, 0.0f ,0.0f );
	D3DXVECTOR3 upVector( 0.0f, -1.0f, 0.0f );

	D3DXMATRIX	viewMatrix;

	D3DXMatrixLookAtLH( &viewMatrix, &position, &targetPoint, &upVector );

	D3DXMATRIX  projMatrix;

	D3DXMatrixOrthoLH( &projMatrix, 1024.0f, 768.0f, -1009.0f, 5000.0f );

	D3DXMatrixTranslation( &uiMoveMatrix, 0.0f, 0.0f, 0 );
	
	mhUIWorldMatHandle	= mFX->GetParameterByName( 0, worldMatName );
	mhUIViewMatHandle	= mFX->GetParameterByName( 0, viewMatName );
	mhUIProjMatHandle	= mFX->GetParameterByName( 0, projMatName );
	mhUIMoveMatHandle	= mFX->GetParameterByName( 0, moveMatName );
	mhAlphaEnabled		= mFX->GetParameterByName( 0, "alphaEnable" );
	D3DXHANDLE mhTech	= mFX->GetTechniqueByName( techniqueName );

	mhTex = mFX->GetParameterByName( 0, "gTex" );

	mFX->SetMatrix( mhUIWorldMatHandle, &worldMatrix );
	mFX->SetMatrix( mhUIViewMatHandle, &viewMatrix );
	mFX->SetMatrix( mhUIProjMatHandle, &projMatrix );
	mFX->SetMatrix( mhUIMoveMatHandle, &uiMoveMatrix );

	mFX->SetTechnique( mhTech );

	HR(mFX->SetBool( mhAlphaEnabled, FALSE ));

	return;
}


void MyGame3DDevice::StartRender()
{
	HR( pD3D9InstanceDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0) );
	HR( pD3D9InstanceDevice->BeginScene() );
}

void MyGame3DDevice::EndRender()
{
	HR(pD3D9InstanceDevice->EndScene());
	HR(pD3D9InstanceDevice->Present( 0, 0, 0, 0 ) );
}

MyGameTexture* MyGame3DDevice::CreateMyTextureFromFile( const char* _fileName )
{
	static unsigned int textureKey = 0;
/*
	IDirect3DTexture9* pSpriteTexture;

	HR(D3DXCreateTextureFromFileExA( pMyGameDevice->pD3D9InstanceDevice,
								_fileName,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								0,
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								0,
								NULL,
								NULL,
								&pSpriteTexture));
*/
	MyGameTexture* pSpriteTexture = new MyGameTexture(_fileName);
	/*pMyGameDevice->myTextureList[textureKey] = pSpriteTexture;*/

	//return textureKey++;
	return pSpriteTexture;
}

MyGameTexture* MyGame3DDevice::CreateMyTextureForText( int _width, int _height )
{
	MyGameTexture* pSpriteTexture = new MyGameTexture( _width, _height);
	/*pMyGameDevice->myTextureList[textureKey] = pSpriteTexture;*/

	//return textureKey++;
	return pSpriteTexture;
}

void MyGame3DDevice::EnableMyUITexture( MyGameTexture* _pTexture )
 {
	HR( pMyGameDevice->mFX->SetTexture( pMyGameDevice->mhTex, _pTexture->GetD9Texture() ) );
	HR( pMyGameDevice->mFX->CommitChanges());
}

void MyGame3DDevice::EnableTexture( MyGameTexture* _pTexture )
{
	HR( pMyGameDevice->mFX->SetTexture( 0, _pTexture->GetD9Texture() ) );
}

void MyGame3DDevice::StartRenderUI()
{
	
	UINT num = 0;

	// render opaque textures
	
	HR(pMyGameDevice->pD3D9InstanceDevice->SetRenderState(D3DRS_SRCBLEND,
                                    D3DBLEND_SRCALPHA));
	HR( pMyGameDevice->pD3D9InstanceDevice->SetRenderState(D3DRS_DESTBLEND,
                                    D3DBLEND_INVSRCALPHA));
									
	HR( pMyGameDevice->pD3D9InstanceDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false));

	HR( pMyGameDevice->mFX->SetBool( pMyGameDevice->mhAlphaEnabled, FALSE ));
	
	HR( pMyGameDevice->mFX->Begin( &num, 0 ) );
	
	HR( pMyGameDevice->pD3D9InstanceDevice->SetIndices( pMyGameDevice->pUIIndexBuffer ) );
	
	HR( pMyGameDevice->mFX->BeginPass( 0 ) );
}

void MyGame3DDevice::StartRenderToTexture( MyGameTexture* _pTargetTexture )
{
	// save screen target
	HR( pMyGameDevice->pD3D9InstanceDevice->GetRenderTarget( 0, &(pMyGameDevice->pScreenTarget) ) );

	//pMyGameDevice->pTextureTarget = _pTargetTexture;

	HR( _pTargetTexture->GetD9Texture()->GetSurfaceLevel( 0, &(pMyGameDevice->pTextureTarget) ) );

	HR( pMyGameDevice->pD3D9InstanceDevice->SetRenderTarget( 0, pMyGameDevice->pTextureTarget ) );
	
	HR( pMyGameDevice->pD3D9InstanceDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0) );
	HR( pMyGameDevice->pD3D9InstanceDevice->BeginScene() );
}

void MyGame3DDevice::EndRenderToTexture()
{
	HR( pMyGameDevice->pD3D9InstanceDevice->EndScene());
	HR( pMyGameDevice->pD3D9InstanceDevice->SetRenderTarget(0, pMyGameDevice->pScreenTarget) );


	//RELEASE THEM !!!! OR THEY'LL CAUSE MEMORY LEAK!!!
	pMyGameDevice->pScreenTarget->Release();

	pMyGameDevice->pTextureTarget->Release();
}

void MyGame3DDevice::EndRenderUI()
{
	HR( pMyGameDevice->mFX->EndPass() );

	HR( pMyGameDevice->mFX->End() );
}

void MyGame3DDevice::InitUIIndexBuffer()
{
	if( pUIIndexBuffer )
		return;
	
		HR( this->pD3D9InstanceDevice->CreateIndexBuffer(
							sizeof(WORD)*6,
							D3DUSAGE_WRITEONLY,
							D3DFMT_INDEX16,
							D3DPOOL_MANAGED,
							&( pUIIndexBuffer ),
							0 ) );
		WORD* _indices = 0;
		pUIIndexBuffer->Lock( 0, 0, (void**)&_indices, 0 );
		memcpy( _indices, uiRectIndices, sizeof(WORD)*6);
		pUIIndexBuffer->Unlock();
}

void MyGame3DDevice::DestroyUIIndexBuffer()
{
	if( !pUIIndexBuffer )
		return;
	IRelease(pUIIndexBuffer);
}

void MyGame3DDevice::MoveUIMatrix( float _x, float _y )
{
	D3DXMatrixTranslation( &(pMyGameDevice->uiMoveMatrix), _x, _y, 0 );
	HR( pMyGameDevice->mFX->SetMatrix( pMyGameDevice->mhUIMoveMatHandle, &(pMyGameDevice->uiMoveMatrix) ) );
	HR( pMyGameDevice->mFX->CommitChanges());
}

void MyGame3DDevice::ScaleUIMatrix( float _x, float _y )
{
	pMyGameDevice->uiMoveMatrix._11 = _x;
	pMyGameDevice->uiMoveMatrix._22 = _y;
	HR( pMyGameDevice->mFX->SetMatrix( pMyGameDevice->mhUIMoveMatHandle, &(pMyGameDevice->uiMoveMatrix) ) );
	HR( pMyGameDevice->mFX->CommitChanges());
}

void MyGame3DDevice::ResetUIMatrix()
{
	HR( pMyGameDevice->mFX->SetMatrix( pMyGameDevice->mhUIMoveMatHandle, &(pMyGameDevice->uiMoveMatrix0) ) );
	pMyGameDevice->uiMoveMatrix = pMyGameDevice->uiMoveMatrix0;
}

void MyGame3DDevice::TestEnableTexture( IDirect3DTexture9* _textureToEnable)
{
	HR( pMyGameDevice->mFX->SetTexture( pMyGameDevice->mhTex, _textureToEnable));
	HR( pMyGameDevice->mFX->CommitChanges());
}

void MyGame3DDevice::EnableUIAlphaBlending()
{
	HR( pMyGameDevice->mFX->SetBool( pMyGameDevice->mhAlphaEnabled, TRUE ));
}

void MyGame3DDevice::DisableUIAlphaBlending()
{
	HR( pMyGameDevice->mFX->SetBool( pMyGameDevice->mhAlphaEnabled, FALSE ));
}

int MyGame3DDevice::CreateVertexBuffer( VertexType _type, void* _vertices, unsigned int verticeSize )
{
	static unsigned int key = 0;
	
	IDirect3DVertexBuffer9*	pVertexBuffer;

	HR( pMyGameDevice->pD3D9InstanceDevice->CreateVertexBuffer(
												verticeSize,
												D3DUSAGE_WRITEONLY,
												0,
												D3DPOOL_MANAGED,
												&pVertexBuffer,
												0 ) );

	myVertex* destVertices = 0;
	pVertexBuffer->Lock( 0, 0, (void**)&destVertices, 0 );
	memcpy( destVertices, _vertices, verticeSize );
	pVertexBuffer->Unlock();

	MyGameVertexBuffer* _myVertexBuffer = new MyGameVertexBuffer;
	//_myVertexBuffer.vertexBuffer = pVertexBuffer;
	//_myVertexBuffer.bufferSize	= verticeSize;

	_myVertexBuffer->SetBufferSize( verticeSize );

	_myVertexBuffer->SetVertexBuffer( pVertexBuffer );

	pMyGameDevice->myVertexBufferList[key] = _myVertexBuffer;

	return key++;
	/*
	switch(_type)
	{
	case uiVertex:		//if it is UI vertex

		break;
	default:
		break;
	}*/

}

void MyGame3DDevice::SetVertexBuffer( int _vertexBufferKey )
{
	if( !pMyGameDevice->myVertexBufferList.count( _vertexBufferKey ) )
		return;

	HR( pMyGameDevice->pD3D9InstanceDevice->SetStreamSource( 0,
											( pMyGameDevice->myVertexBufferList[_vertexBufferKey]->GetVertexBuffer()),
											0,
											sizeof( myVertex )));
}

void MyGame3DDevice::DrawIndexedTrianglePrimitive( int verticesCount, int triangleCount )
{
	HR( pMyGameDevice->pD3D9InstanceDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, verticesCount, 0, triangleCount) );
}

void MyGame3DDevice::DestroyVertexBuffer( int _bufferKey )
{
	if( !(pMyGameDevice->myVertexBufferList.count( _bufferKey )) )
		return;

	//pMyGameDevice->myVertexBufferList[ _bufferKey ].vertexBuffer->Release();

	delete (pMyGameDevice->myVertexBufferList[ _bufferKey ]);//因为是动态分配的所以要清除……么

	pMyGameDevice->myVertexBufferList.erase( _bufferKey );
}

void MyGame3DDevice::DrawTrianglePrimitive( D3DPRIMITIVETYPE _type, UINT StartVertex, UINT PrimitiveCount  )
{
	HR( pMyGameDevice->pD3D9InstanceDevice->DrawPrimitive( _type, StartVertex, PrimitiveCount) );
}

MyGame3DEffect*	MyGame3DDevice::CreateEffectFromResourceID( int _rsID )
{
	MyGame3DEffect* _pEffect = new MyGame3DEffect( _rsID );
	return _pEffect;
}