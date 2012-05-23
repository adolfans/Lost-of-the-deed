#include "StdAfx.h"
#include "MyGameDecoration.h"

map<unsigned int,MyGameDecoration*> MyGameDecoration::decorationMap;
MyGameDecoration::MyGameDecoration(void)
{
	static int _key = 0;
	this->key = _key;
	_key++;
	decorationMap[key] = this;
}


MyGameDecoration::~MyGameDecoration(void)
{
	decorationMap.erase( key );
}

void MyGameDecoration::updateAllDecration()
{
	for( map<unsigned int, MyGameDecoration*>::iterator _itr = decorationMap.begin();
		_itr != decorationMap.end();
		++_itr )
	{
		(*_itr).second->update();
	}
}
