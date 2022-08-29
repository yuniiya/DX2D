#include "PreCompile.h"
#include "TestLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Item.h"
#include "Scorpion.h"

TestLevel::TestLevel() 
	: Renderer_(nullptr)
	, Player_(nullptr)
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	SetCollisionMap("ColMap_Desert.png");
	SetBackGround("Back_Desert.png");
	SetStage("Stage_Desert.png");

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.0f, -400.0f});

	Renderer_ = Player_->CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 1280.f, 720.f });
	Renderer_->CreateFrameAnimationFolder("SinD", FrameAnimation_DESC("SinD", 0.08f));
	Renderer_->GetTransform().SetLocalPosition({GetMainCameraActor()->GetTransform().GetLocalPosition()});
	Renderer_->ChangeFrameAnimation("SinD");

}

void TestLevel::Update(float _DeltaTime)
{
	float4 PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 1619.f, 785.f });
}

void TestLevel::LevelStartEvent()
{
	Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::ITEM);
	ItemActor->MonsterName_ = MONSTERNAME::BabyCactus;
	ItemActor->GetTransform().SetLocalPosition({ 400.f, -500.f });
	ItemActor->TimeAttackStart();

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
}
