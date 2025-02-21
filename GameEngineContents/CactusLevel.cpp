#include "PreCompile.h"
#include "CactusLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "WhiteRabbit.h"
#include "BrownRabbit.h"
#include "BabyCactus.h"
#include "Inventory.h"
#include "NPC_Cactus.h"
#include "GameBgmPlayer.h"
#include "Cloud.h"

CactusLevel::CactusLevel() 
	: Player_(nullptr)
{
}

CactusLevel::~CactusLevel() 
{
}

void CactusLevel::Start()
{
	SetCollisionMap("ColMap_Cactus2.png");
	SetBackGround("Back_Cactus.png");
//	SetAriantCloud(-500.f);
	SetAriantSunLight(-300.f);
	SetStage("Stage_Cactus.png");

	Cloud* Cloud_ = CreateActor<Cloud>();
	Cloud_->CreateCloud("Cactus_Cloud.png", { 2060.f / 2.f, -500.f }, 90.f, true);

	// Monster
	{
		WhiteRabbit* Rabbit1 = CreateActor<WhiteRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit1->GetTransform().SetLocalPosition({ 1050.f, -750.f, (int)ZOrder::MONSTER });
		Rabbit1->SetMonsterDir(ACTORDIR::LEFT);

		WhiteRabbit* Rabbit2 = CreateActor<WhiteRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit2->GetTransform().SetLocalPosition({ 300.f, -750.f, (int)ZOrder::MONSTER });
		Rabbit2->SetMonsterDir(ACTORDIR::RIGHT);

		WhiteRabbit* Rabbit3 = CreateActor<WhiteRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit3->GetTransform().SetLocalPosition({ 500.f, -750.f, (int)ZOrder::MONSTER });
		Rabbit3->SetMonsterDir(ACTORDIR::RIGHT);
	}

	{
		BrownRabbit* Rabbit1 = CreateActor<BrownRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit1->GetTransform().SetLocalPosition({ 800.f, -500.f, (int)ZOrder::MONSTER });
		Rabbit1->SetMonsterDir(ACTORDIR::RIGHT);

		BrownRabbit* Rabbit2 = CreateActor<BrownRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit2->GetTransform().SetLocalPosition({ 500.f, -500.f, (int)ZOrder::MONSTER });
		Rabbit2->SetMonsterDir(ACTORDIR::LEFT);

		BrownRabbit* Rabbit3 = CreateActor<BrownRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit3->GetTransform().SetLocalPosition({ 600.f, -500.f, (int)ZOrder::MONSTER });
		Rabbit3->SetMonsterDir(ACTORDIR::LEFT);
	}


	{
		BabyCactus* Cactus1 = CreateActor<BabyCactus>(GAMEOBJGROUP::MONSTER);
		Cactus1->GetTransform().SetLocalPosition({ 820.f, -500.f, (int)ZOrder::MONSTER });
		Cactus1->SetMonsterDir(ACTORDIR::LEFT);

		BabyCactus* Cactus2 = CreateActor<BabyCactus>(GAMEOBJGROUP::MONSTER);
		Cactus2->GetTransform().SetLocalPosition({ 520.f, -500.f, (int)ZOrder::MONSTER });
		Cactus2->SetMonsterDir(ACTORDIR::RIGHT);

		BabyCactus* Cactus3 = CreateActor<BabyCactus>(GAMEOBJGROUP::MONSTER);
		Cactus3->GetTransform().SetLocalPosition({ 1000.f, -750.f, (int)ZOrder::MONSTER });
		Cactus3->SetMonsterDir(ACTORDIR::LEFT);
	}

	SetPortal({ 111.f, -776.f, (int)ZOrder::PORTAL });
	SetPortal({ 1864.f, -776.f, (int)ZOrder::PORTAL });

	NPC_Cactus* NPC_ = CreateActor<NPC_Cactus>((int)GAMEOBJGROUP::OBJ);
	NPC_->SetNPCType(NPCType::NPC_Cactus);
	NPC_->GetTransform().SetLocalPosition({ 170.f, -327.f, (int)ZOrder::NPC });
	NPC_->SetQuestRendererPosition();
	// UI
	/*if (nullptr == GetContentsUI())
	{
		CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	}*/	//CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
}

void CactusLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Desert");
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

	CameraFix(GetCollisionMap()->GetTransform().GetLocalScale());
}

void CactusLevel::End()
{
}

void CactusLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	GameBgmPlayer::BgmPlay_->Stop();
	GameBgmPlayer::BgmPlay_->ChangeBgm("HotDesert.mp3");
	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();

		if (true == Player::MainPlayer_->IsPrevLevel_)
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 1864.f, -700.f, (int)ZOrder::PLAYER });
		}
		else
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 111.f, -700.0f, (int)ZOrder::PLAYER });
		}
	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}

}

void CactusLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();

}
