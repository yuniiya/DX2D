#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "MapStage.h"
#include "Mouse.h"
#include "Fade.h"


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

	if (nullptr == Player::MainPlayer_)
	{
		Player::MainPlayer_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	}
	//Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	//Player_->GetTransform().SetLocalPosition({ 2600.f, -600.0f});

	SetPortal({ 3008.f, -750.f, (int)ZOrder::PORTAL});
	SetPortal({ 3410.f, -750.f, (int)ZOrder::PORTAL });

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

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

	PlayerPos_ = Player::MainPlayer_->GetTransform().GetLocalPosition();

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

void AriantLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 3200.f, -600.0f, (int)ZOrder::PLAYER});
}

void AriantLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
}

