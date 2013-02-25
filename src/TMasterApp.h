#pragma once

#include "TApp.h"
#include "TSpreadModule.h"
#include "TStateGui.h"


class TSpreadModuleMaster : public TSpreadModule
{
public:
	TSpreadModuleMaster() :
		TSpreadModule	( "Master" )
	{
	}
};



namespace TMasterWidgets
{
	enum Type
	{
		Invalid,
		Title,
		NetworkStatus,	

		Text,			//	our sync'd member
	};

	BufferString<100>	ToString(TMasterWidgets::Type Button);
	void				GetArray(ArrayBridge<TMasterWidgets::Type>& Array);
};
SOY_DECLARE_ENUM( TMasterWidgets );


class TMasterApp : public TApp
{
public:
	TMasterApp();

	virtual void			update();
	virtual void			draw();
	virtual TSpreadModule&	GetModule()		{	return mModule;	}

	ofxUILabel*				GetLabel(TMasterWidgets::Type Widget)	{	return static_cast<ofxUILabel*>( mCanvas.getWidget( static_cast<const char*>( SoyEnum::ToString( Widget ) ) ) );	}

public:
	TSpreadModuleMaster		mModule;
	ofxUICanvas				mCanvas;
};







