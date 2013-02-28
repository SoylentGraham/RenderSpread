#include "TSpreadModule.h"


TSpreadModule::TSpreadModule(const char* Name) :
	SoyModule	( Name ),
	mText		( *this, "Text", "hello" )
{
}

		
void TSpreadModule::Update(float TimeStep)
{
	//	do module update
	SoyModule::Update( TimeStep );
}
