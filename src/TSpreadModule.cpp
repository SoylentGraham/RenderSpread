#include "TSpreadModule.h"


TSpreadModule::TSpreadModule(const char* Name) :
	SoyModule	( Name ),
	mText		( *this, "Text", "hello" )
{
	//	connect to first port
	ChangeState<SoyModuleState_ServerBind>();
}

