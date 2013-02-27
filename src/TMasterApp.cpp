#include "TMasterApp.h"
#include "TRender.h"


#define CONNECT_TO_SERVER_BUTTON_PREFIX	"Connect_to_"
#define EDIT_MODULE_MEMBER_PREFIX		"Member_"
#define BUTTON_SIZE		vec2f( 20, 20 )
#define TEXTBOX_SIZE	vec2f( BUTTON_SIZE.x * 10, BUTTON_SIZE.y )



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
	AddModuleMemberTextEdit( mModule.mText );

	//	catch peer changes
	ofAddListener( mModule.mOnPeersChanged, this, &TMasterApp::OnPeersChanged );
	ofAddListener( mCanvas.newGUIEvent, this, &TMasterApp::OnCanvasEvent );
	ofAddListener( mModule.mOnMemberChanged, this, &TMasterApp::OnMemberChanged );

	SoyModulePeerAddress LocalAddress("localhost", mModule.GetClusterPortRange()[0]);
	mModule.OnFoundPeer( SoyRef("Master"), LocalAddress );
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
	

void TMasterApp::OnCanvasEvent(ofxUIEventArgs &e)
{
	if ( !e.widget )
		return;

	BufferString<100> WidgetName = e.widget->getName().c_str();
	
	//	is it a connect-to-server button?
	if ( WidgetName.StartsWith(CONNECT_TO_SERVER_BUTTON_PREFIX) )
	{
		//	extract ref
		WidgetName.RemoveAt( 0, strlen(CONNECT_TO_SERVER_BUTTON_PREFIX) );
		SoyRef PeerRef( WidgetName );
		OnConnectToServerButton( PeerRef );
		return;
	}
	
	//	reflection of variable change
	if ( WidgetName.StartsWith(EDIT_MODULE_MEMBER_PREFIX) )
	{
		//	extract ref
		WidgetName.RemoveAt( 0, strlen(EDIT_MODULE_MEMBER_PREFIX) );
		SoyRef MemberRef( WidgetName );
		auto* pTextWidget = static_cast<ofxUITextInput*>( e.widget );
		BufferString<100> Value = pTextWidget->getTextString().c_str();
		
		//	push change to module...
		OnModuleMemberEdited( MemberRef, Value, *pTextWidget );
		return;
	}
	
}


void TMasterApp::OnPeersChanged(const Array<SoyRef>& Peers)
{
	//	re-make buttons
	for ( int i=0;	i<Peers.GetSize();	i++ )
	{
		auto& PeerRef = Peers[i];
		AddConnectToServerButton( PeerRef );
	}
}

void TMasterApp::OnConnectToServerButton(const SoyRef& PeerRef)
{
	//	change module state
	mModule.ChangeState<SoyModuleState_ClientConnect>( PeerRef );
}


void TMasterApp::OnMemberChanged(const SoyRef& MemberRef)
{
	auto* pMember = mModule.GetMember( MemberRef );
	assert( pMember );
	if ( !pMember )
		return;

	//	update reflection
	AddModuleMemberTextEdit( *pMember );
}


bool TMasterApp::OnModuleMemberEdited(const SoyRef& MemberRef,const char* Value,ofxUITextInput& Widget)
{
	auto* pMember = mModule.GetMember( MemberRef );
	if ( !pMember )
		return false;
	auto& Member = *pMember;
	
	//	set value
	if ( !Member.SetData( Value ) )
	{
		BufferString<100> ValueString;
		Member.GetData( ValueString );
		Widget.setTextString( static_cast<const char*>( ValueString ) );
	}

	return true;
}


void TMasterApp::AddModuleMemberTextEdit(const SoyModuleMemberBase& Member)
{
	BufferString<100> WidgetName;
	WidgetName << EDIT_MODULE_MEMBER_PREFIX << Member.mRef;

	//	make text edit
	BufferString<100> Value;
	Member.GetData( Value );

	//	grab existing widget
	auto* pWidget = static_cast<ofxUITextInput*>( mCanvas.getWidget( static_cast<const char*>( WidgetName ) ) );
	if ( pWidget )
	{
		pWidget->setTextString( static_cast<const char*>( Value ) );
	}
	else
	{
		pWidget = mCanvas.addTextInput( static_cast<const char*>( WidgetName ), static_cast<const char*>( Value ), TEXTBOX_SIZE.x, TEXTBOX_SIZE.y, OFX_UI_FONT_MEDIUM );
		pWidget->setAutoClear( false );
	}
}

void TMasterApp::AddConnectToServerButton(const SoyRef& PeerRef)
{
	BufferString<100> RefString;
	RefString << PeerRef;
	BufferString<100> WidgetName;
	WidgetName << CONNECT_TO_SERVER_BUTTON_PREFIX << RefString;

	auto* pButton = mServerButtons.Find( WidgetName );
	if ( pButton )
	{
		//	update button
		return;
	}

	//	make button for this server
	mCanvas.addButton( static_cast<const char*>( WidgetName ), false, BUTTON_SIZE.x, BUTTON_SIZE.y );
}


