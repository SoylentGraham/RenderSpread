#include "TSpreadModule.h"


TSpreadModule::TSpreadModule(const char* Name) :
	SoyModule	( Name ),
	mText		( "Text", "hello" )
{
	//ofAddListener( mOnStateChanged, this, &TSpreadModule::OnNetStateChanged );

	//	connect to first port
	ChangeState<SoyModuleState_DiscoveryBind>();
}

