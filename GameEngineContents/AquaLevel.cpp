#include "PreCompile.h"
#include "AquaLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"

AquaLevel::AquaLevel() 
	: Player_(nullptr)
{
}

AquaLevel::~AquaLevel() 
{
}

void AquaLevel::Start()
{
	SetCollisionMap("ColMap_Aqua2.png");
	SetBackGround("Back_Aqua2.png");
	SetStage("Stage_Aqua.png");

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 1200.0f, -1000.0f});

	SetPortal({ 97.f, -1123.f});
	SetPortal({ 1494.f, -1064.f});

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
}

void AquaLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Boss");
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

	CameraFix({ 1614.f, 1380.f });
}

void AquaLevel::End()
{
}
