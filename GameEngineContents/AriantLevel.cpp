#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "MapStage.h"


AriantLevel::AriantLevel() 
{
}

AriantLevel::~AriantLevel() 
{
}

void AriantLevel::Start()
{
	SetCamera();
	SetBackGround("Back_Ariant.png");
	SetCollisionMap("ColMap_Ariant.png");
	//SetStage("Stage_Ariant.png");


	Player::MainPlayer_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 1800.0f, -750.0f, 0.0f });
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

	

	CameraPos_ = GetMainCameraActor()->GetTransform().GetLocalPosition();
	PlayerPos_ = Player::MainPlayer_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_ });
	}

	//LimitCamera({ 5760.f, 995.f });
}

void AriantLevel::End()
{
}

void AriantLevel::BindTime()
{
}
