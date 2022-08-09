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

CactusLevel::CactusLevel() 
{
}

CactusLevel::~CactusLevel() 
{
}

void CactusLevel::Start()
{
	SetCollisionMap("ColMap_Cactus2.png");
	SetBackGround("Back_Cactus.png");
	SetStage("Stage_Cactus.png");


	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.0f, -600.0f});

	SetPortal({ 111.f, -776.f});
	SetPortal({ 1864.f, -776.f});

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

	// Monster
	{
		WhiteRabbit* Rabbit1 = CreateActor<WhiteRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit1->GetTransform().SetLocalPosition({ 1050.f, -600.f });
		Rabbit1->SetMonsterDir(ACTORDIR::RIGHT);
	//	Rabbit1->SetChangeTime(5, 43);

		WhiteRabbit* Rabbit2 = CreateActor<WhiteRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit2->GetTransform().SetLocalPosition({ 300.f, -600.f });
		Rabbit2->SetMonsterDir(ACTORDIR::RIGHT);
	//	Rabbit2->SetChangeTime(3, 50);
	}

	{
		BrownRabbit* Rabbit1 = CreateActor<BrownRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit1->GetTransform().SetLocalPosition({ 800.f, -300.f });
		Rabbit1->SetMonsterDir(ACTORDIR::RIGHT);
	//	Rabbit1->SetChangeTime(6, 44);

		BrownRabbit* Rabbit2 = CreateActor<BrownRabbit>(GAMEOBJGROUP::MONSTER);
		Rabbit2->GetTransform().SetLocalPosition({ 500.f, -300.f });
		Rabbit2->SetMonsterDir(ACTORDIR::RIGHT);
		//Rabbit2->SetChangeTime(2, 46);
	}


	{
		BabyCactus* Cactus1 = CreateActor<BabyCactus>(GAMEOBJGROUP::MONSTER);
		Cactus1->GetTransform().SetLocalPosition({ 820.f, -300.f });
		Cactus1->SetMonsterDir(ACTORDIR::LEFT);
		//Cactus1->SetChangeTime(3, 47);

		BabyCactus* Cactus2 = CreateActor<BabyCactus>(GAMEOBJGROUP::MONSTER);
		Cactus2->GetTransform().SetLocalPosition({ 520.f, -300.f });
		Cactus2->SetMonsterDir(ACTORDIR::LEFT);
	//	Cactus2->SetChangeTime(5, 51);
	}

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

	PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 2060.f, 1030.f });
}

void CactusLevel::End()
{
}

void CactusLevel::OnEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
}
