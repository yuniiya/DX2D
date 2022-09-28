#include "PreCompile.h"
#include "AquaLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "Mouse.h"
#include "Fade.h"
#include "Freezer.h"
#include "Sparker.h"
#include "Inventory.h"
#include "MapObject.h"
#include "Cloud.h"

AquaLevel::AquaLevel() 
	: Player_(nullptr)
{
}

AquaLevel::~AquaLevel() 
{
}

void AquaLevel::Start()
{
	SetCollisionMap("ColMap_Aqua3.png");
	SetBackGround("Back_Aqua2.png");
	SetStage("Stage_Aqua.png");

	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light0", "Aqua_SunLight0", 0.05f, { 300.f, -500.f }, { 526.f, 372.f });
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light1", "Aqua_SunLight1", 0.05f, { 1400.f, -500.f }, { 526.f, 372.f });
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light3", "Aqua_SunLight3", 0.05f, { 600.f, -300.f }, { 380.f, 340.f });
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Fish0", "Fish0", 1.f, 30.f, { 1000.f, -200.f }, {326.f, 65.f}, ACTORDIR::LEFT);
	}



	// Monster
	// 1Ãþ
	{
		Sparker* Spark1 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark1->GetTransform().SetLocalPosition({ 1000.f, -1100.f, (int)ZOrder::MONSTER });
		Spark1->SetMonsterDir(ACTORDIR::LEFT);

		Sparker* Spark2 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark2->GetTransform().SetLocalPosition({ 800.f, -1100.f, (int)ZOrder::MONSTER });
		Spark2->SetMonsterDir(ACTORDIR::RIGHT);

		Sparker* Spark3 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark3->GetTransform().SetLocalPosition({ 300.f, -1100.f, (int)ZOrder::MONSTER });
		Spark3->SetMonsterDir(ACTORDIR::RIGHT);
	}
	{
		Freezer* Freez1 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez1->GetTransform().SetLocalPosition({ 250.f, -1100.f, (int)ZOrder::MONSTER });
		Freez1->SetMonsterDir(ACTORDIR::LEFT);

		Freezer* Freez2 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez2->GetTransform().SetLocalPosition({ 550.f, -1100.f, (int)ZOrder::MONSTER });
		Freez2->SetMonsterDir(ACTORDIR::RIGHT);

		//Freezer* Freez3 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		//Freez3->GetTransform().SetLocalPosition({ 950.f, -1000.f, (int)ZOrder::MONSTER });
		//Freez3->SetMonsterDir(ACTORDIR::LEFT);
	}


	// 2Ãþ
	{
		Sparker* Spark1 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark1->GetTransform().SetLocalPosition({ 450.f, -800.f, (int)ZOrder::MONSTER });
		Spark1->SetMonsterDir(ACTORDIR::LEFT);

		//Sparker* Spark2 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		//Spark2->GetTransform().SetLocalPosition({ 350.f, -600.f, (int)ZOrder::MONSTER });
		//Spark2->SetMonsterDir(ACTORDIR::RIGHT);
	}
	{
		//Sparker* Spark1 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		//Spark1->GetTransform().SetLocalPosition({ 1300.f, -600.f, (int)ZOrder::MONSTER });
		//Spark1->SetMonsterDir(ACTORDIR::LEFT);

		Sparker* Spark2 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark2->GetTransform().SetLocalPosition({ 1320.f, -800.f, (int)ZOrder::MONSTER });
		Spark2->SetMonsterDir(ACTORDIR::RIGHT);

		//Sparker* Spark3 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		//Spark3->GetTransform().SetLocalPosition({ 930.f, -600.f, (int)ZOrder::MONSTER });
		//Spark3->SetMonsterDir(ACTORDIR::RIGHT);
	}
	{
		Freezer* Freez1 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez1->GetTransform().SetLocalPosition({ 300.f, -800.f, (int)ZOrder::MONSTER });
		Freez1->SetMonsterDir(ACTORDIR::LEFT);

		Freezer* Freez2 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez2->GetTransform().SetLocalPosition({ 320.f, -800.f, (int)ZOrder::MONSTER });
		Freez2->SetMonsterDir(ACTORDIR::RIGHT);

		//Freezer* Freez3 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		//Freez3->GetTransform().SetLocalPosition({ 340.f, -600.f, (int)ZOrder::MONSTER });
		//Freez3->SetMonsterDir(ACTORDIR::LEFT);
	}
	{
		Freezer* Freez1 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez1->GetTransform().SetLocalPosition({ 1380.f, -500.f, (int)ZOrder::MONSTER });
		Freez1->SetMonsterDir(ACTORDIR::LEFT);

		//Freezer* Freez2 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		//Freez2->GetTransform().SetLocalPosition({ 1320.f, -500.f, (int)ZOrder::MONSTER });
		//Freez2->SetMonsterDir(ACTORDIR::RIGHT);

		//Freezer* Freez3 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		//Freez3->GetTransform().SetLocalPosition({ 940.f, -600.f, (int)ZOrder::MONSTER });
		//Freez3->SetMonsterDir(ACTORDIR::LEFT);
	}


	// 3Ãþ
	{
		Sparker* Spark1 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark1->GetTransform().SetLocalPosition({ 400.f, -500.f, (int)ZOrder::MONSTER });
		Spark1->SetMonsterDir(ACTORDIR::RIGHT);

		Sparker* Spark2 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		Spark2->GetTransform().SetLocalPosition({ 1350.f, -500.f, (int)ZOrder::MONSTER });
		Spark2->SetMonsterDir(ACTORDIR::LEFT);
	}
	{
		//Sparker* Spark1 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		//Spark1->GetTransform().SetLocalPosition({ 800.f, -500.f, (int)ZOrder::MONSTER });
		//Spark1->SetMonsterDir(ACTORDIR::RIGHT);

		//Sparker* Spark2 = CreateActor<Sparker>(GAMEOBJGROUP::MONSTER);
		//Spark2->GetTransform().SetLocalPosition({ 900.f, -500.f, (int)ZOrder::MONSTER });
		//Spark2->SetMonsterDir(ACTORDIR::LEFT);
	}
	{
		Freezer* Freez1 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez1->GetTransform().SetLocalPosition({ 350.f, -400.f, (int)ZOrder::MONSTER });
		Freez1->SetMonsterDir(ACTORDIR::LEFT);

		Freezer* Freez2 = CreateActor<Freezer>(GAMEOBJGROUP::MONSTER);
		Freez2->GetTransform().SetLocalPosition({ 1300.f, -400.f, (int)ZOrder::MONSTER });
		Freez2->SetMonsterDir(ACTORDIR::RIGHT);
	}





	SetPortal({ 97.f, -1123.f, (int)ZOrder::PORTAL});
	SetPortal({ 1494.f, -1064.f, (int)ZOrder::PORTAL });

}

void AquaLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Boss");
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

	CameraFix({ 1614.f, 1380.f });
}

void AquaLevel::End()
{
}

void AquaLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();
		Player::MainPlayer_->GetTransform().SetLocalPosition({ 1000.0f, -400.0f, (int)ZOrder::PLAYER });

	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}
}

void AquaLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();
}
