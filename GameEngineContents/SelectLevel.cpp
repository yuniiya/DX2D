#include "PreCompile.h"
#include "SelectLevel.h"
#include "MapBackGround.h"
#include <GameEngineCore/GEngine.h>
#include "SelectUI.h"
#include "Mouse.h"

SelectLevel::SelectLevel() 
{
}

SelectLevel::~SelectLevel() 
{
}

void SelectLevel::Start()
{
	MapBackGround* BackGround_ = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

	BackGroundRenderer_->SetTexture("Select.png");
	BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());

	SelectUI* UIActor = CreateActor<SelectUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

}

void SelectLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Ariant");
	}
}

void SelectLevel::End()
{
}
