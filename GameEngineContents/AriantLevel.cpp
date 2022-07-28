#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "MapStage.h"


AriantLevel::AriantLevel() 
	: Player_(nullptr)
{
}

AriantLevel::~AriantLevel() 
{
}

void AriantLevel::Start()
{
	SetCollisionMap("ColMap_Ariant.png");
	SetBackGround("Back_Ariant.png");
	SetStage("Stage_Ariant.png");

	// UI
	{
		ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	//	UIActor_->SetMainUI();

		//float4 Pos = GetUICameraActorTransform().GetLocalPosition() + float4{ 0.f, 0.f, 0.f };
		//GetUICameraActorTransform().SetLocalPosition(Pos);
	}


	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 2200.f, -600.0f, 0.0f });

	{

	} 
}

void AriantLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Cactus");
	}

	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 5760.f, 995.f });
}

void AriantLevel::End()
{
	//Player_->GetTransform().SetLocalPosition(float4::ZERO);
}

