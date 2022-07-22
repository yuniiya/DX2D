#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"


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
	SetStage("Stage_Ariant.png");

	Player::MainPlayer_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 100.0f, -250.f, 0.0f });
	//Player::MainPlayer_->GetTransform().SetWorldScale(float4(100.0f, 100.f, 100.0f));
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
}

void AriantLevel::End()
{
}

void AriantLevel::BindTime()
{
}
