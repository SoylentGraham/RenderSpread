#pragma once

#include "Main.h"
#include "TSpreadModule.h"






class TApp : public SoyApp, public TStateManager<TApp>
{
public:
	TApp();

	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void exit();


	virtual TSpreadModule&	GetModule()=0;
	virtual ofColour		GetClearColour() const		{	return ofColour( 240, 24, 68 );	}

protected:
	virtual TApp&			GetStateParent()			{	return *this;	}
};



