#include "PreCompile.h"
#include "DesertLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "Sand.h"
#include "Scorpion.h"
#include "Inventory.h"
#include "GameBgmPlayer.h"
#include "Cloud.h"

DesertLevel::DesertLevel() 
	: Player_(nullptr)
{
}

DesertLevel::~DesertLevel() 
{
}

void DesertLevel::Start()
{
	SetCollisionMap("ColMap_Desert.png");
	SetBackGround("Back_Desert.png");
	SetStage("Stage_Desert.png");
	Cloud* Cloud_ = CreateActor<Cloud>();
	Cloud_->CreateCloud("Desert_Cloud.png", { 1619.f / 2.f, -380.f }, 90.f, true);


	// Monster
	{
		Sand* Sand1 = CreateActor<Sand>(GAMEOBJGROUP::MONSTER);
		Sand1->GetTransform().SetLocalPosition({ 1050.f, -600.f, (int)ZOrder::MONSTER });
		Sand1->SetMonsterDir(ACTORDIR::LEFT);

		Sand* Sand2 = CreateActor<Sand>(GAMEOBJGROUP::MONSTER);
		Sand2->GetTransform().SetLocalPosition({ 300.f, -600.f, (int)ZOrder::MONSTER });
		Sand2->SetMonsterDir(ACTORDIR::RIGHT);
	}

	{
		Scorpion* Scor1 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor1->GetTransform().SetLocalPosition({ 1000.f, -600.f, (int)ZOrder::MONSTER });
		Scor1->SetMonsterDir(ACTORDIR::LEFT);

		Scorpion* Scor2 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor2->GetTransform().SetLocalPosition({ 400.f, -600.f, (int)ZOrder::MONSTER });
		Scor2->SetMonsterDir(ACTORDIR::RIGHT);

		Scorpion* Scor3 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor3->GetTransform().SetLocalPosition({ 600.f, -600.f, (int)ZOrder::MONSTER });
		Scor3->SetMonsterDir(ACTORDIR::RIGHT);

		Scorpion* Scor4 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor4->GetTransform().SetLocalPosition({ 800.f, -600.f, (int)ZOrder::MONSTER });
		Scor4->SetMonsterDir(ACTORDIR::LEFT);

		Scorpion* Scor5 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor5->GetTransform().SetLocalPosition({ 500.f, -600.f, (int)ZOrder::MONSTER });
		Scor5->SetMonsterDir(ACTORDIR::LEFT);
	}


	SetPortal({ 168.f, -240.f, (int)ZOrder::PORTAL});
	SetPortal({ 1489.f, -542.f, (int)ZOrder::PORTAL});

	// UI
	//if (nullptr == GetContentsUI())
	//{
	//	CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	//}	//CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

}

void DesertLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Entrance");
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

	CameraFix(GetCollisionMap()->GetTransform().GetLocalScale());

}

void DesertLevel::End()
{
}

void DesertLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	GameBgmPlayer::BgmPlay_->Stop();
	GameBgmPlayer::BgmPlay_->ChangeBgm("SunsetDesert.mp3");
	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();

		if (true == Player::MainPlayer_->IsPrevLevel_)
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 1489.0f, -542.0f, (int)ZOrder::PLAYER });

		}
		else
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 168.0f, -240.0f, (int)ZOrder::PLAYER });
		}

	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}
}

void DesertLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();
}
