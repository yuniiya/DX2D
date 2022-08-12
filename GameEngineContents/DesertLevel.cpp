#include "PreCompile.h"
#include "DesertLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "Sand.h"
#include "Scorpion.h"

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

	//Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	//Player_->GetTransform().SetLocalPosition({ 200.0f, -100.0f});

	SetPortal({ 168.f, -240.f});
	SetPortal({ 1489.f, -542.f});

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

	// Monster
	{
		Sand* Sand1 = CreateActor<Sand>(GAMEOBJGROUP::MONSTER);
		Sand1->GetTransform().SetLocalPosition({ 1050.f, -600.f });
		Sand1->SetMonsterDir(ACTORDIR::LEFT);

		Sand* Sand2 = CreateActor<Sand>(GAMEOBJGROUP::MONSTER);
		Sand2->GetTransform().SetLocalPosition({ 300.f, -600.f });
		Sand2->SetMonsterDir(ACTORDIR::RIGHT);
	}

	{
		Scorpion* Scor1 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor1->GetTransform().SetLocalPosition({ 1000.f, -600.f });
		Scor1->SetMonsterDir(ACTORDIR::LEFT);

		Scorpion* Scor2 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor2->GetTransform().SetLocalPosition({ 400.f, -600.f });
		Scor2->SetMonsterDir(ACTORDIR::RIGHT);

		Scorpion* Scor3 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor3->GetTransform().SetLocalPosition({ 600.f, -600.f });
		Scor3->SetMonsterDir(ACTORDIR::RIGHT);

		Scorpion* Scor4 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor4->GetTransform().SetLocalPosition({ 800.f, -600.f });
		Scor4->SetMonsterDir(ACTORDIR::LEFT);

		Scorpion* Scor5 = CreateActor<Scorpion>(GAMEOBJGROUP::MONSTER);
		Scor5->GetTransform().SetLocalPosition({ 500.f, -600.f });
		Scor5->SetMonsterDir(ACTORDIR::LEFT);
	}
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

	CameraFix({ 1619.f, 785.f });

}

void DesertLevel::End()
{
}

void DesertLevel::OnEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 200.0f, -100.0f });
}

void DesertLevel::OffEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
}
