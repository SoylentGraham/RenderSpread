#pragma once

#include "TApp.h"
#include "TSpreadModule.h"
#include "TStateGui.h"

inline SoyRef RandomIncrementedRef(const char* BaseName,int MaxInc)
{
	SoyRef Ref( BaseName );
	MaxInc = ofRandom( MaxInc-1 ) + 1;
	while ( MaxInc-- > 0 )
		Ref++;
	return Ref;
}

class TSpreadModuleMaster : public TSpreadModule
{
public:
	TSpreadModuleMaster() :
		TSpreadModule	( RandomIncrementedRef("Master",100).ToString() )
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
	
	void					OnPeersChanged(const Array<SoyRef>& Peers);
	void					OnMemberChanged(const SoyRef& MemberRef);
	
	void					OnCanvasEvent(ofxUIEventArgs& e);
	void					OnConnectToServerButton(const SoyRef& PeerRef);
	bool					OnModuleMemberEdited(const SoyRef& MemberRef,const char* Value,ofxUITextInput& Widget);

protected:
	void					AddModuleMemberTextEdit(const SoyModuleMemberBase& Member);
	void					AddConnectToServerButton(const SoyRef& PeerRef);

public:
	TSpreadModuleMaster			mModule;
	ofxUICanvas					mCanvas;
	Array<BufferString<100>>	mServerButtons;	//	connect to server X
};







