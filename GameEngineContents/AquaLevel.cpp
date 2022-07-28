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
	SetCamera();
	SetCollisionMap("ColMap_Aqua.png");
	SetBackGround("Back_Aqua2.png");
	SetStage("Stage_Aqua.png");

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 1200.0f, -750.0f, 0.0f });
}

void AquaLevel::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Boss");
	}*/

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
