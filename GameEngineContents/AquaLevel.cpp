#include "PreCompile.h"
#include "AquaLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"

AquaLevel::AquaLevel() 
{
}

AquaLevel::~AquaLevel() 
{
}

void AquaLevel::Start()
{
	SetCollisionMap("ColMap_Aqua.png");
	SetBackGround("Back_Aqua2.png");
	SetStage("Stage_Aqua.png");

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 1200.0f, -750.0f, 0.0f });
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
