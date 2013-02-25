#include "TMasterApp.h"
#include "TRender.h"




BufferString<100> TMasterWidgets::ToString(TMasterWidgets::Type Button)
{
	switch( Button )
	{ 
	default:
	case Invalid:			return "Invalid";
	case Title:				return "Title";
	case NetworkStatus:		return "NetworkStatus";
	case Text:				return "Text";
	}
}

void TMasterWidgets::GetArray(ArrayBridge<TMasterWidgets::Type>& Array)
{
	//Array.PushBack( Invalid );
	Array.PushBack( Title );
	Array.PushBack( NetworkStatus );
	Array.PushBack( Text );
}



TMasterApp::TMasterApp()
{
	mCanvas.disableAppEventCallbacks();

	//	init canvas
	BufferString<100> ModuleLabel; 
	ModuleLabel << mModule.mRef;
	mCanvas.addLabel( static_cast<const char*>( SoyEnum::ToString(TMasterWidgets::Title) ), static_cast<const char*>(ModuleLabel), OFX_UI_FONT_LARGE );
	mCanvas.addSpacer( 0, 10 );

	mCanvas.addLabel( static_cast<const char*>( SoyEnum::ToString(TMasterWidgets::NetworkStatus) ), OFX_UI_FONT_MEDIUM );
	mCanvas.addLabel( static_cast<const char*>( SoyEnum::ToString(TMasterWidgets::Text) ), OFX_UI_FONT_MEDIUM );
}


void TMasterApp::draw()
{
	TRenderSceneScope( __FUNCTION__ );
	TApp::draw();

	mCanvas.draw();
}


void TMasterApp::update()
{
	TApp::update();

	//	update network status
	ofxUILabel* pNetworkStatus = GetLabel( TMasterWidgets::NetworkStatus );
	if ( pNetworkStatus )
	{
		auto Status = mModule.GetNetworkStatus();
		pNetworkStatus->setLabel( static_cast<const char*>(Status) );
	}

	//	update our sync'd text
	ofxUILabel* pText = GetLabel( TMasterWidgets::Text );
	if ( pText )
	{
		BufferString<100> Text;
		Text << mModule.mText.GetData();
		pText->setLabel( static_cast<const char*>(Text) );
	}

}
