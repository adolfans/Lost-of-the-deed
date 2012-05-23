#pragma once
#include "MyGameDecoration.h"
#include "MyGameUISprite.h"
#include <ctime>
#include <vector>
using std::vector;

class MyGameUIAnimation :
	public MyGameDecoration
{
	typedef struct MyUIAnimationFrame{
		int frameTime;
		int imgID;
		int xDest;
		int yDest;
		float xScale;
		float yScale;
		MyUIAnimationFrame():
		frameTime(0),imgID(0),xDest(0),yDest(0),xScale(1.0),yScale(1.0){}
	}MyUIAnimationFrame;
private:
	MyGameUISprite*	aniSprite;
	int					spriteVisibleState;	//0 is unvisible, 1 is appear, 2 is disappear, 3 is now rendering
	int					currentFrame;
	int					frameNum;
	vector<MyUIAnimationFrame>			frameTimeList;
	clock_t				lastUpdatedTime;
public:
	MyGameUIAnimation( MyGameUISprite* _aniSprite );
	//MyGameUIAnimation( string _fileName, bool _transparent, int _key );
	~MyGameUIAnimation(void);
	bool getVisible();
	void appear();
	void disappear();
	void update();		// inherited from the MyGameDecoration class
	//int createImage( int _xSource, int _ySource, int _width, int _height ); //create image from texture of sprite
	int createFrame( int _time );	//returns frame serial number
	void setImgToFrame( int _frameID, int _imgID, int _xDest, int _yDest);
	void setImgToFrame( int _frameID, int _imgID, int _xDest, int _yDest, float _xScale, float _yScale );
	int getAniState()
	{
		return spriteVisibleState;
	}

};