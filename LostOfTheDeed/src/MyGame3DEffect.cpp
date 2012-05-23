#include "StdAfx.h"
#include "MyGame3DEffect.h"


IDirect3DDevice9*	MyGame3DEffect::pD9Device = 0;

MyGame3DEffect::MyGame3DEffect(void)
{
}

MyGame3DEffect::MyGame3DEffect( int _resourceID )
{
	HRSRC hResource = ::FindResource( NULL, MAKEINTRESOURCE(_resourceID), RT_RCDATA );
	HGLOBAL hResourceData = ::LoadResource( NULL, hResource );
	LPVOID pData = ::LockResource( hResourceData );

	ID3DXBuffer* errorBuffer = 0;
	HR( D3DXCreateEffect( pD9Device,
							pData,
							::SizeofResource( NULL, hResource ),
							0,
							0,
							0,
							0,
							&pD9Effect,
							&errorBuffer ) );
	if( errorBuffer )
	{
		MyGameMessage( (char*)errorBuffer->GetBufferPointer() );
		errorBuffer->Release();
		return;
	}

	//initialize matrix in shader

	//D3DXMATRIX worldMatrix;

	//D3DXMatrixTranslation( &worldMatrix, -512.0f, -384.0f, 0 );

	//D3DXVECTOR3 position( 0.0f, 0.0f, 20.0f );
	//D3DXVECTOR3 targetPoint( 0.0f, 0.0f ,0.0f );
	//D3DXVECTOR3 upVector( 0.0f, -1.0f, 0.0f );

	//D3DXMATRIX	viewMatrix;

	//D3DXMatrixLookAtLH( &viewMatrix, &position, &targetPoint, &upVector );

	//D3DXMATRIX  projMatrix;

	//D3DXMatrixOrthoLH( &projMatrix, 1024.0f, 768.0f, -1009.0f, 5000.0f );

	//D3DXMatrixTranslation( &uiMoveMatrix, 0.0f, 0.0f, 0 );

	//mhUIWorldMatHandle	= pD9Effect->GetParameterByName( 0, worldMatName );
	//mhUIViewMatHandle	= pD9Effect->GetParameterByName( 0, viewMatName );
	//mhUIProjMatHandle	= pD9Effect->GetParameterByName( 0, projMatName );
	//mhUIMoveMatHandle	= pD9Effect->GetParameterByName( 0, moveMatName );
	//mhAlphaEnabled		= pD9Effect->GetParameterByName( 0, "alphaEnable" );
	//D3DXHANDLE mhTech	= pD9Effect->GetTechniqueByName( techniqueName );

	//mhTex = mFX->GetParameterByName( 0, "gTex" );

	//mFX->SetMatrix( mhUIWorldMatHandle, &worldMatrix );
	//mFX->SetMatrix( mhUIViewMatHandle, &viewMatrix );
	//mFX->SetMatrix( mhUIProjMatHandle, &projMatrix );
	//mFX->SetMatrix( mhUIMoveMatHandle, &uiMoveMatrix );

	//mFX->SetTechnique( mhTech );

	//HR(mFX->SetBool( mhAlphaEnabled, FALSE ));

	return;
}

void MyGame3DEffect::SetMatrixByName( D3DXMATRIX _matrix, const char* _matrixName )
{
	D3DXHANDLE mhMatrix = pD9Effect->GetParameterByName( 0, _matrixName );
	pD9Effect->SetMatrix( mhMatrix, &_matrix );
}

void MyGame3DEffect::SetTechniqueByName( const char* _techName )
{
	D3DXHANDLE mhTech = pD9Effect->GetTechniqueByName( _techName );
	pD9Effect->SetTechnique( mhTech );
}

void MyGame3DEffect::SetBOOLByName( BOOL _ifEnable, const char* _boolVarName )
{
	D3DXHANDLE mhBOOL = pD9Effect->GetParameterByName( 0, _boolVarName );
	pD9Effect->SetBool( mhBOOL, _ifEnable );
}

MyGame3DEffect::~MyGame3DEffect(void)
{
	pD9Effect->Release();
}

void MyGame3DEffect::SetEffectDevice( IDirect3DDevice9* _pDevice )
{
	pD9Device = _pDevice;
}