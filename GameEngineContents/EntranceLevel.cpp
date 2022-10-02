#include "PreCompile.h"
#include "EntranceLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "Inventory.h"
#include "NPC_Entrance.h"
#include "GameBgmPlayer.h"
#include "Cloud.h"

EntranceLevel::EntranceLevel() 
{
}

EntranceLevel::~EntranceLevel() 
{
}

void EntranceLevel::Start()
{
	SetCollisionMap("ColMap_Entrance.png");
	SetBackGround("Back_Entrance.png");
	SetAriantSunLight(-600.f);
	SetStage("Stage_Entrance.png");
	Cloud* Cloud_ = CreateActor<Cloud>();
	Cloud_->CreateCloud("Entrance_Cloud.png", { 2340.f / 2.f, -850.f }, 90.f, true);
	//Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	//Player_->GetTransform().SetLocalPosition({ 2100.0f, -1000.0f});

	SetPortal({ 2123.f, -1109.f, (int)ZOrder::PORTAL });
	SetPortal({ 976.f, -643.f, (int)ZOrder::PORTAL });

	NPC_Entrance* NPC_ = CreateActor<NPC_Entrance>((int)GAMEOBJGROUP::OBJ);
	NPC_->SetNPCType(NPCType::NPC_Entrance);
	NPC_->GetTransform().SetLocalPosition({ 1070.f, -715.f, (int)ZOrder::NPC });
	NPC_->SetQuestRendererPosition();
	// UI
	/*if (nullptr == GetContentsUI())
	{
		CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	}*/
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
	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();
		Player::MainPlayer_->GetTransform().SetLocalPosition({ 1180.0f, -650.0f, (int)ZOrder::PLAYER });
	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}
}

void EntranceLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();
}
