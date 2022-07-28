#include "PreCompile.h"
#include "CastleLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Player.h"

CastleLevel::CastleLevel() 
{
}

CastleLevel::~CastleLevel() 
{
}

void CastleLevel::Start()
{
	SetCamera();
	SetCollisionMap("ColMap_Castle.png");
	SetBackGround("Back_Castle.png");
	SetStage("Stage_Castle2.png");


	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 300.0f, -400.0f, 0.0f });
}

void CastleLevel::Update(float _DeltaTime)
{ 
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Aqua");
	}

	float4 PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}
}

void CastleLevel::End()
{
}
