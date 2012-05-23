#pragma once
#include <d3dx9.h>
class MyGame3DEffect
{
private:
	ID3DXEffect*	pD9Effect;
	static IDirect3DDevice9* pD9Device;
public:
	MyGame3DEffect(void);
	MyGame3DEffect( int _resourceID );
	~MyGame3DEffect(void);

	static void SetEffectDevice( IDirect3DDevice9* _pDevice );

	void SetMatrixByName( D3DXMATRIX _matrix, const char* _matrixName );
	void SetTechniqueByName( const char* _techName );
	void SetBOOLByName( BOOL _ifEnable, const char* _boolVarName );
};

