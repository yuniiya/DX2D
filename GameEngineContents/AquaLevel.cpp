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
#include "MapAnimationObject.h"
#include "GameBgmPlayer.h"

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
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light0", "Aqua_SunLight0", 0.05f, { 300.f, -500.f }, { 526.f, 372.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light1", "Aqua_SunLight1", 0.05f, { 1400.f, -500.f }, { 526.f, 372.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light3", "Aqua_SunLight3", 0.05f, { 600.f, -300.f }, { 380.f, 340.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light1", "Light1", 0.2f, { 400.f, -500.f }, { 768.f, 825.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light1", "Light1", 0.2f, { 1000.f, -600.f }, { 768.f, 825.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light0", "Light0", 0.6f, { 1400.f, -500.f }, { 262.f, 380.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light0", "Light0", 0.6f, { 300.f, -1000.f }, { 262.f, 380.f });
	}
	{
		MapAnimationObject* Obj_ = CreateActor<MapAnimationObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateAnimation("Light0", "Light0", 0.6f, { 1250.f, -1000.f }, { 262.f, 380.f });
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Fish0", "Fish0", 0.5f, 0.2f, { 900.f, -80.f }, {326.f, 65.f}, ACTORDIR::LEFT);
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Fish1", "Fish1", 0.5f, 0.35f, { 1200.f, -200.f }, { 402.f, 67.f }, ACTORDIR::LEFT);
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Fish2", "Fish2", 0.5f, 0.45f, { 200.f, -380.f }, { 362.f, 86.f }, ACTORDIR::RIGHT);
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Turtle1", "Turtle1", 0.2f, 0.25f, { 200.f, -340.f }, { 63.f, 38.f }, ACTORDIR::RIGHT);
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Turtle0", "Turtle0", 0.2f, 0.25f, { 120.f, -365.f }, { 41.f, 25.f }, ACTORDIR::RIGHT);
	}
	{
		MapObject* Obj_ = CreateActor<MapObject>((int)GAMEOBJGROUP::BACKGROUND);
		Obj_->CreateXMoveAnimaition("Turtle0", "Turtle0", 0.2f, 0.25f, { 160.f, -300.f }, { 41.f, 25.f }, ACTORDIR::RIGHT);
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
	GameBgmPlayer::BgmPlay_->Stop();
	GameBgmPlayer::BgmPlay_->ChangeBgm("BlueWorld.mp3");

	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();
		if (true == Player::MainPlayer_->IsPrevLevel_)
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 1494.f, -1020.f, (int)ZOrder::PLAYER });
		}
		else
		{
			Player::MainPlayer_->GetTransform().SetLocalPosition({ 97.f, -1123.f, (int)ZOrder::PLAYER });
		}


	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}
}

void AquaLevel::LevelEndEvent()
{
	//GameBgmPlayer::BgmPlay_->Stop();
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();
}
