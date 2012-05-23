#include "StdAfx.h"
#include "MyGameNotify.h"

MyGameNotify* MyGameNotify::pNotifyInstance = 0;
MyGameNotify::MyGameNotify(void)
	:notifyBG("img/blackRect.png", true, 100, 0.0f, 0.0f, 1024.0f, 768.0f ),
	testTextSprite(0,390.0f, 416.0f, 165.0f ,101 ),
	//testTextSprite( 0, 390.0f, 800.0f, 600.0f, 101 ),
	notifyAni( &testTextSprite ),
	notifyText( 44.5, 16, 3, "Î¢ÈíÑÅºÚ", false ),
	timePassed( 0 )
{
	//notifyBG = new MyGameUISprite( "img/blackRect.png", true,100, 0.0f, 0.0f, 416.0f, 165.0f );
	int frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -416, 0, 1.0f, 1.0f );
	frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -356, 0, 1.0f, 1.0f );
	frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -306, 0, 1.0f, 1.0f );
	frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -256, 0, 1.0f, 1.0f );
	frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -206, 0, 1.0f, 1.0f );
		frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -156, 0, 1.0f, 1.0f );
		frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -100, 0, 1.0f, 1.0f );
		frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -50, 0, 1.0f, 1.0f );
		frameNum = notifyAni.createFrame( 20 );
	notifyAni.setImgToFrame( frameNum, 0, -0, 0, 1.0f, 1.0f );
	notifyBG.SetVisibility( false );
	notifyText.SetColor( 0xfffffffff );
	notifyText.SetFormat( DT_CENTER|DT_VCENTER );
	notifyText.SetDestRectForTexture( 0, 0, 416, 165 );
	notifyText.SetCount(0);

	//testTextSprite.SetText( "", &notifyText, &notifyBG );
	//testTextSprite.SetVisibility( true );
}


MyGameNotify::~MyGameNotify(void)
{
}

MyGameNotify* MyGameNotify::InitNotifyBox()
{
	if( !pNotifyInstance )
		pNotifyInstance = new MyGameNotify();
	return pNotifyInstance;
}
// annoying 
int textCount = 0;

void MyGameNotify::MyGameNotification( const char* _notifyText )
{
	pNotifyInstance->notifyAni.appear();
	textCount = pNotifyInstance->notifyText.SetText( _notifyText );
	pNotifyInstance->notifyText.SetCount( textCount );
	pNotifyInstance->testTextSprite.SetText( _notifyText, &(pNotifyInstance->notifyText), &(pNotifyInstance->notifyBG), 0 );
}

void MyGameNotify::update()
{
	
	static clock_t lastTime = clock();
	if( !notifyAni.getVisible() )
	{
		notifyBG.SetVisibility(false);
		return;
	}

	if( 3 == this->notifyAni.getAniState() )//if appeared
	{
		notifyText.SetCount( textCount );

		if( timePassed == 0 )	//start clock
		{
			lastTime = clock();
		}
		clock_t currentTime = clock();

		if( 0 == currentTime - lastTime )
			timePassed = 1;//this may make timePassed be 0
		else
			timePassed = currentTime - lastTime;
		if( timePassed > 1000 )	//after 20 clocks
		{
			notifyAni.disappear();
			notifyText.SetCount(0);
			lastTime = clock();
			timePassed = 0;
		}
	}
	//if( 0 == this->notifyAni.getAniState() )// if disappeared
	//	notifyBG.SetVisibility(false);
}