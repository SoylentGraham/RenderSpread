#include "TStateGui.h"
#include "TApp.h"






TStateGuiBase::TStateGuiBase(TApp& App) :
	TState	( App )
{
	mCanvas.disableAppEventCallbacks();
	ofAddListener( mCanvas.newGUIEvent, this, &TStateGuiBase::OnCanvasEvent );
}

void TStateGuiBase::Update(float TimeStep)
{
	mCanvas.update();
}

	 
void TStateGuiBase::Render(float TimeStep)
{
	mCanvas.draw();
}

