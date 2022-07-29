#include "PreCompile.h"
#include "DesertLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"

DesertLevel::DesertLevel() 
{
}

DesertLevel::~DesertLevel() 
{
}

void DesertLevel::Start()
{
	SetCollisionMap("ColMap_Desert.png");
	SetBackGround("Back_Desert.png");
	SetStage("Stage_Desert.png");

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.0f, -100.0f, 0.0f });

}

void DesertLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Entrance");
	}
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	float4 PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 1619.f, 785.f });

}

void DesertLevel::End()
{
}
