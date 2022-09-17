#include "PreCompile.h"
#include "SelectLevel.h"
#include "MapBackGround.h"
#include <GameEngineCore/GEngine.h>
#include "SelectUI.h"
#include "Mouse.h"
#include "Fade.h"

SelectLevel::SelectLevel() 
{
}

SelectLevel::~SelectLevel() 
{
}

void SelectLevel::Start()
{
	{
		MapBackGround* BackGround_ = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
		GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

		BackGroundRenderer_->SetTexture("Select.png");
		BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());
		BackGroundRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
		BackGroundRenderer_->GetTransform().SetLocalPosition({
			  BackGroundRenderer_->GetTransform().GetLocalPosition().x - GameEngineWindow::GetScale().x / 2.f
			, BackGroundRenderer_->GetTransform().GetLocalPosition().y + GameEngineWindow::GetScale().y / 2.f
			, (int)ZOrder::BACKGROUND });
	}

	SelectUI* UIActor = CreateActor<SelectUI>(GAMEOBJGROUP::UI);
	if (nullptr == Mouse::MainMouse_)
	{
		CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
	}

	//ShowCursor(false);
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

void SelectLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);

	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->GetTransform().SetWorldMove({ 0.f, -500.f });
	}
}