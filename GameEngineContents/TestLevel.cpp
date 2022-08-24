#include "PreCompile.h"
#include "TestLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Item.h"

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
	Renderer_->GetTransform().SetLocalScale({ 972.f, 398.f });
	Renderer_->CreateFrameAnimationFolder("SinD", FrameAnimation_DESC("SinD", 0.04f));
	Renderer_->GetTransform().SetLocalPosition({ 1280.f, 720.f });
	Renderer_->ChangeFrameAnimation("SinD");


	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BabyCactus;
		ItemActor->GetTransform().SetLocalPosition({ 3200.f, -800.f });
		ItemActor->TimeAttackStart();
	}
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
