#pragma once
#include <map>
using std::map;
class MyGameDecoration
{
private:
	static map<unsigned int, MyGameDecoration*> decorationMap; 
	int key;
public:
	MyGameDecoration(void);
	virtual ~MyGameDecoration(void);
	virtual void update() = 0;
	static void updateAllDecration();
};

