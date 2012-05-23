#include "StdAfx.h"
#include "MyGameUIAnimation.h"
#include <cassert>

MyGameUIAnimation::MyGameUIAnimation( MyGameUISprite* _aniSprite )
	://aniSprite( &_aniSprite ),
	aniSprite( _aniSprite ),
	spriteVisibleState( 0 ),
	frameNum(0),
	currentFrame(0)
{
	//assert( *aniSprite );
}




MyGameUIAnimation::~MyGameUIAnimation(void)
{
	aniSprite = 0;
}

void MyGameUIAnimation::update()
{
	//assert( *aniSprite );

	if( !(aniSprite)->GetVisibility() )
	{
		currentFrame = 0;
		return;
	}
	switch( spriteVisibleState)
	{
	case 0://unvisible
		return;
		break;
	case 1://appear
		{
		clock_t currentTime = clock();//get current time
		// get current frame time
		int frameTime = frameTimeList[currentFrame].frameTime;
		//if the passed time < frameTime, don't change frame
		if( (currentTime - lastUpdatedTime) < frameTime )
		{
			//don't change frame
		}else
		{
			//change frame and lastUpdatedTime
			if( currentFrame < frameNum - 1 )
			{
				currentFrame++;
				lastUpdatedTime = currentTime;
			}else
			{
				currentFrame = frameNum - 1;
				spriteVisibleState = 3;
			}
		}
		}
		break;
	case 2:
		{
		clock_t currentTime = clock(); // get current time
		//get current frame time
		int frameTime = frameTimeList[currentFrame].frameTime;
		//if the passed time < frameTime, don't change frame
		if( (currentTime - lastUpdatedTime) < frameTime )
		{
			//don't change frame
		}else
		{
			//change frame and lastUpdatedTime
			if( currentFrame > 0 )
			{
				currentFrame --;
				lastUpdatedTime = currentTime;
			}else
			{
				currentFrame = 0;
				spriteVisibleState = 0;
			}
		}
		}
		break;
	case 3: //if rendering
		break;
	default:
		break;
	}
	//遍历所有的帧, i是frameID
	(aniSprite)->DisableAllRects();
	(aniSprite)->SetRectVisibility( frameTimeList[currentFrame].imgID, true );
	(aniSprite)->MoveRect( frameTimeList[currentFrame].imgID, frameTimeList[currentFrame].xDest, frameTimeList[currentFrame].yDest );
	(aniSprite)->ScaleRect( frameTimeList[currentFrame].imgID, frameTimeList[currentFrame].xScale, frameTimeList[currentFrame].yScale );
}

int MyGameUIAnimation::createFrame( int _time )
{
	//assert( *aniSprite );
	//vector的下标操作不能添加元素
	MyUIAnimationFrame newFrame;
	newFrame.frameTime = _time;
	frameTimeList.push_back( newFrame );
	//frameNum++;
	return frameNum++;
}

void MyGameUIAnimation::setImgToFrame( int _frameID, int _imgID, int _xDest, int _yDest)
{
	//assert( *aniSprite ); 
	frameTimeList[_frameID].imgID = _imgID;
	frameTimeList[_frameID].xDest = _xDest;
	frameTimeList[_frameID].yDest = _yDest;
}

void MyGameUIAnimation::setImgToFrame( int _frameID, int _imgID/*this is rect id of that sprite*/, int _xDest, int _yDest, float _xScale, float _yScale )
{
	//assert( *aniSprite ); 
	frameTimeList[_frameID].imgID = _imgID;
	frameTimeList[_frameID].xDest = _xDest;
	frameTimeList[_frameID].yDest = _yDest;
	frameTimeList[_frameID].xScale = _xScale;
	frameTimeList[_frameID].yScale = _yScale;
}

void MyGameUIAnimation::appear()
{
	(aniSprite)->SetVisibility(true);
	spriteVisibleState = 1;
	currentFrame = 0;
	lastUpdatedTime = clock();
}

bool MyGameUIAnimation::getVisible()
{
	if( spriteVisibleState == 0 )
		return false;
	else
		return true;
}

void MyGameUIAnimation::disappear()
{
	spriteVisibleState = 2;
	currentFrame = frameNum - 1;
	lastUpdatedTime = clock();
}