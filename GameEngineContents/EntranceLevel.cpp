#include "PreCompile.h"
#include "EntranceLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "Inventory.h"

EntranceLevel::EntranceLevel() 
{
}

EntranceLevel::~EntranceLevel() 
{
}

void EntranceLevel::Start()
{
	GlobalLevel::Start();

	SetCollisionMap("ColMap_Entrance.png");
	SetBackGround("Back_Entrance.png");
	SetStage("Stage_Entrance.png");

	//Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	//Player_->GetTransform().SetLocalPosition({ 2100.0f, -1000.0f});

	SetPortal({ 2123.f, -1109.f, (int)ZOrder::PORTAL });
	SetPortal({ 976.f, -643.f, (int)ZOrder::PORTAL });

	// UI
	//ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	//CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

}

void EntranceLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Castle");
	}
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	float4 PlayerPos_ = Player::MainPlayer_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 2340.f, 1355.f });

}

void EntranceLevel::End()
{
}

void EntranceLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 1200.0f, -500.0f, (int)ZOrder::PLAYER });
}

void EntranceLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
}
