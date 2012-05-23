#pragma once
/*********************
automatically update the variable on time
after you set up frequency
**********************/
#include <time.h>
#include <map>
using std::map;
class MyGameClock
{
private:
	float initValue;
	float &variable;
	float frequency;//update "frenquency" times per second
	bool	destroyed;
	bool	plus;
	bool	stopped;
	int		key;
	float	limit;
	clock_t	currentTime;
	clock_t lastTime;
	static	map<int, MyGameClock*> clockList;

public:
	MyGameClock(float &_variable, float _frequency, bool _ifPlus, float _limit):
				variable( _variable ), frequency( _frequency ),initValue( _variable),
					plus( _ifPlus ),stopped( false ), destroyed( false ), limit( _limit )
	{
		//MessageBoxA(0,"囧，MyGameClock构造函数开始",0,0);
		static int _key = 0;
		key = _key;
		clockList[key] = this;
		_key++;
		lastTime = clock();
		currentTime = clock();
	}
	//if the variable will be destroyed or is destroyed, destroy its clock
	//to make sure that MyGameClock will not update it automatically
/*	void DestroyClock(){
		destroyed = true;
	}*/
	~MyGameClock(void){
		clockList.erase(this->key);
	}

	void StopUpdateAndReset()
	{
		stopped = true;
		variable = initValue;
	}

	void SetLimit(float _limit)
	{
		this->limit = _limit;
		variable = initValue;	//reset variable
		// reset the two clock (especially lastTime) so that
		// lastTime will not be too early
		currentTime = clock();
		lastTime	= clock();
	}

	void StartUpdate()
	{
		stopped = false;
	}

	void UpdateClock()
	{
		if( true == stopped )
		{
			currentTime = clock();
			lastTime = currentTime;
			return;
		}
		currentTime = clock();
		if( currentTime - lastTime  > (CLOCKS_PER_SEC/100 ) /*&& variable < limit*/ )//if time passed 1 second from last time updated on
		{
			if( variable < limit )
			{
				//printf("time:%d\n", currentTime - lastTime);
				variable += frequency*(currentTime - lastTime);
			}
			lastTime = currentTime;
		}
		
	}

	static void UpdateAllClock(){
		///if( desstroyed ) then not to update it
		for( map<int, MyGameClock*>::iterator _itr = clockList.begin();
			_itr != clockList.end();
			++ _itr )
		{
			(*_itr).second->UpdateClock();
		}
	}
};

