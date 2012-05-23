#include "StdAfx.h"
#include "MyGameVertexBuffer.h"


MyGameVertexBuffer::MyGameVertexBuffer(void)
{
}


MyGameVertexBuffer::~MyGameVertexBuffer(void)
{
	vertexBuffer->Release();
}
