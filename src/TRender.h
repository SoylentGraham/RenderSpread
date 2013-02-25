#pragma once

#include "Main.h"


namespace TRender
{
	extern ofTrueTypeFont	Font;
	bool					InitFont();
};

//	push/pop style for immediate rendering
class TRenderSceneScope
{
public:
	TRenderSceneScope(const char* SceneName);
	~TRenderSceneScope();
};



