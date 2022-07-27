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
	SetCamera();

	SetBackGround("Back_Desert.png");
	SetStage("Stage_Desert.png");
	SetCollisionMap("ColMap_Desert.png");

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 1200.0f, -750.0f, 0.0f });

}

void DesertLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Entrance");
	}

	float4 PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}
}

void DesertLevel::End()
{
}
