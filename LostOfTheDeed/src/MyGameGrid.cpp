#include "StdAfx.h"
#include "MyGameGrid.h"


MyGameGrid::MyGameGrid(void)
	:pGridVertexBuffer(0),
	pGridIndexBuffer(0)
{
}


MyGameGrid::~MyGameGrid(void)
{
	IRelease( pGridVertexBuffer );
	IRelease( pGridIndexBuffer );
}
