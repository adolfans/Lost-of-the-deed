#pragma once
#include "MyGame3DDevice.h"
class MyGameGrid
{
private:
	IDirect3DVertexBuffer9*	pGridVertexBuffer;
	IDirect3DIndexBuffer9*	pGridIndexBuffer;
	static MyGame3DDevice* pMyDevice;
public:
//	bool	MyGameGenerateGrid( int _width, int _height, float stride );
	MyGameGrid(void);
	~MyGameGrid(void);
};

