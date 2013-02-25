#include "TApp.h"
#include "TRender.h"


TApp::TApp()
{
}


void TApp::setup()
{
	//	sys init
	//TRender::InitFont();
}


void TApp::update()
{
	//	work this out!
	float TimeStep = 1.f / ofGetFrameRate();

	//	update module
	GetModule().Update( TimeStep );

	//	update app state machine
	UpdateStates( TimeStep );
}




void TApp::draw()
{
	//	render game
	float TimeStep = 1.f / ofGetFrameRate();

	//	render game background
	ofClear( GetClearColour() );

	RenderStates( TimeStep );
}


void TApp::exit()
{
	//	kill states...
	
}
