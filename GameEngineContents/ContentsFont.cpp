#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::Start()
{

	SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	SetSize(17);
	ChangeCamera(CAMERAORDER::UICAMERA);
	//Off();
}

void ContentsFont::Render(float _DeltaTime)
{
	SetText("けけけけけけけけけけ");

}

