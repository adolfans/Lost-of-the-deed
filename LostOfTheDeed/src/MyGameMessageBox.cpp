#include "StdAfx.h"
#include "MyGameMessageBox.h"

MyGameMessageBox* MyGameMessageBox::gameNotifyInstance = 0;
MyGameMessageBox::MyGameMessageBox(void)
	:no1( "img/notify8.png", true, 30, 0.0f, 0.0f, 1024.0f, 768.0f ),
	numToDraw( 0.0f ),
	visible(false),
	closing( false ),
	notifyText( 22, 15, 30, "ËÎÌו", false ),
	count(0),
	pNo1( &no1 ),
	myAnimation( pNo1 )
{
	no1.SetVisibility(false);
	notifyText.SetColor( 0xffffffff );
	notifyText.SetDestRectForScreen( 0, 400, 1024, 100 );
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

}


MyGameMessageBox::~MyGameMessageBox(void)
{
}

void MyGameMessageBox::update()
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
			ResetCurrentKeyState();
		}
	}
	if( 0 == this->myAnimation.getAniState() )
		no1.SetVisibility(false);

}

MyGameMessageBox* MyGameMessageBox::InitGameMessageBox()
{
	if( !gameNotifyInstance )
		gameNotifyInstance = new MyGameMessageBox();
	return gameNotifyInstance;		
}

void MyGameMessageBox::MyGameNotifyBox( const char* _text )
{
	ChangeGameSubState( myGameNotifyMsg );
	gameNotifyInstance->SetVisible( true );
	gameNotifyInstance->SetNotifyText( _text );
}

void MyGameMessageBox::SetNotifyText( const char* _text )
{
	count = notifyText.SetText( _text );
	myAnimation.appear();
}