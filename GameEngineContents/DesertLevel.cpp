#include "PreCompile.h"
#include "DesertLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"

DesertLevel::DesertLevel() 
	: Player_(nullptr)
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

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.0f, -100.0f, 0.0f });

	SetPortal({ 168.f, -240.f, 0.0f });
	SetPortal({ 1489.f, -542.f, 0.0f });

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

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
