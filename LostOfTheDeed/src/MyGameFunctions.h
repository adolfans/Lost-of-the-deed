#pragma once
#include <DxErr.h>
#include <stdio.h>
#include <string.h>
#ifdef _DEBUG
#include <iostream>
#define MyGameMessage(p) {std::cout<<p<<std::endl;}
#endif
#ifndef _DEBUG
#define MyGameMessage(p) {}
#endif
//inline void MyGameStringCopy(char** _ppdest, char* _source)
//{
//	if(*_ppdest == _source)
//		return;
//	if(*_ppdest)
//	{
//		delete _ppdest;
//		_ppdest = 0;
//	}
//	
//	int len = strlen(_source);
//	*_ppdest = new char[len+1];
//	strcpy(*_ppdest, _source);
//}

template <typename T>
inline void IRelease(T& IObject)
{
	if( IObject != 0 )
	{
		IObject->Release();
		IObject = 0;
	}
}

#if	defined(DEBUG) | defined(_DEBUG)
       #ifndef HR
       #define HR(x)                                          \
       {                                                      \
             HRESULT hr = x;                                  \
             if(FAILED(hr))                                   \
             {                                                \
			 DXTraceW(__FILE__, __LINE__, hr, NULL, TRUE); \
             }                                                \
       }
       #endif

#else
      #ifndef HR
      #define HR(x) x;
      #endif
#endif

//DXTraceW(__FILE__, __LINE__, hr, L#x, TRUE);