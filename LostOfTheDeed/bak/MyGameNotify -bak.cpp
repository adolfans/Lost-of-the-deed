#include "StdAfx.h"
#include "MyGameNotify.h"

MyGameNotify* MyGameNotify::gameNotifyInstance = 0;
MyGameNotify::MyGameNotify(void)
	:no1( "notify8.png", true, 30, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no2( "notify2.png", true, 31, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no3( "notify3.png", true, 32, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no4( "notify4.png", true, 33, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no5( "notify5.png", true, 34, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no6( "notify6.png", true, 35, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no7( "notify7.png", true, 36, 0.0f, 0.0f, 1024.0f, 768.0f ),
	//no8( "notify8.png", true, 37, 0.0f, 0.0f, 1024.0f, 768.0f ),
	numToDraw( 0.0f ),
	//picNumClock( numToDraw, 0.03, true, 9 ),
	visible(false),
	closing( false ),
	notifyText( 22, 15, 30, "ËÎÌו", false ),
	count(0),
	pNo1( &no1 ),
	myAnimation( pNo1 )
{
	no1.SetVisibility(false);
	//no2.SetVisibility(false);
	//no3.SetVisibility(false);
	//no4.SetVisibility(false);
	//no5.SetVisibility(false);
	//no6.SetVisibility(false);
	//no7.SetVisibility(false);
	//no8.SetVisibility(false);
	//picNumClock.StopUpdateAndReset();
	notifyText.SetColor( 0xffffffff );
	notifyText.SetDestRect( 0, 400, 1024, 100 );
	notifyText.SetFormat( DT_CENTER|DT_VCENTER );
	notifyText.SetCount(0);
	int fr = myAnimation.createFrame( 25 );
	myAnimation.setImgToFrame( fr, 0, 0,0, 1.0, 0.2 ); 
	fr = myAnimation.createFrame( 25 );
	myAnimation.setImgToFrame( fr, 0, 0,0, 1.0, 0.4 );
	fr = myAnimation.createFrame( 25 );
	myAnimation.setImgToFrame( fr, 0, 0,0, 1.0, 0.6 );
	fr = myAnimation.createFrame( 25 );
	myAnimation.setImgToFrame( fr, 0, 0,0, 1.0, 0.8 );
	fr = myAnimation.createFrame( 25 );
	myAnimation.setImgToFrame( fr, 0, 0,0, 1.0, 1.0 );


	//no1.SetVisibility( true );
}


MyGameNotify::~MyGameNotify(void)
{
}

void MyGameNotify::update()
{
	if( !visible )
		return;

	if( 3 == this->myAnimation.getAniState() )
	{
		notifyText.SetCount( count );
		if( LButton  == GetCurrentKeyState()|| Next  == GetCurrentKeyState()  )	//if so, close the game notify box
		{
			notifyText.SetCount( 0 );
			myAnimation.disappear();
			SendMyMessage(myMsgBoxClosed);
		}
	}
	if( 0 == this->myAnimation.getAniState() )
		no1.SetVisibility(false);
	//int num = numToDraw;
	//
	//if( numToDraw > 7 && ( LButton  == GetCurrentKeyState()|| Next  == GetCurrentKeyState() ) )	//if so, close the game notify box
	//{
	//	if( !closing )		//if it is not closing
	//	{
	//		picNumClock.StopUpdateAndReset();
	//		picNumClock.StartUpdate();
	//		closing = true;
	//		ResetCurrentKeyState();
	//	}
	//}
 //	if ( closing == true )
	//{
	//	notifyText.SetCount( 0 );
	//	num = 8 - num;
	//	if( !num )
	//	{
	//		visible = false;
	//		closing = false;
	//		picNumClock.StopUpdateAndReset();
	//		SendMyMessage(myMsgBoxClosed);
	//		notifyText.SetCount( 0 );
	//	}
	//}
	//if( num > 8 )
	//	num =8;
	//else if( num < 0 )
	//	num = 0;
	//no1.SetVisibility(false);
	//no2.SetVisibility(false);
	//no3.SetVisibility(false);
	//no4.SetVisibility(false);
	//no5.SetVisibility(false);
	//no6.SetVisibility(false);
	//no7.SetVisibility(false);
	//no8.SetVisibility(false);
	//switch( num )
	//{
	//case 0:
	//	break;
	//case 1:
	//	no1.SetVisibility(true);
	//	break;
	//case 2:
	//	no2.SetVisibility(true);
	//	break;
	//case 3:
	//	no3.SetVisibility(true);
	//	break;
	//case 4:
	//	no4.SetVisibility(true);
	//	break;
	//case 5:
	//	no5.SetVisibility(true);
	//	break;
	//case 6:
	//	no6.SetVisibility(true);
	//	break;
	//case 7:
	//	no7.SetVisibility(true);
	//	break;
	//case 8:
	//case 9:
	//case 10:
	//case 11:
	//case 12:
	//	no8.SetVisibility(true);
	//	notifyText.SetCount( count );
	//	//picNumClock.StopUpdateAndReset();
	//	break;
	//default:
	//	//no8.SetVisibility(true);
	//	break;
	//}
}

MyGameNotify* MyGameNotify::InitGameNotify()
{
	if( !gameNotifyInstance )
		gameNotifyInstance = new MyGameNotify();
	return gameNotifyInstance;		
}

void MyGameNotify::MyGameNotifyBox( const char* _text )
{
	ChangeGameSubState( myGameNotifyMsg );
	gameNotifyInstance->SetVisible( true );
	//gameNotifyInstance->picNumClock.StartUpdate();
	gameNotifyInstance->SetNotifyText( _text );
}

void MyGameNotify::SetNotifyText( const char* _text )
{
	count = notifyText.SetText( _text );
	myAnimation.appear();
}
//MyGameNotify::MyGameNotifyBox("");