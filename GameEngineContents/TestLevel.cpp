#include "PreCompile.h"
#include "TestLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

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
	Renderer_->CreateFrameAnimationFolder("Skill_Ji", FrameAnimation_DESC("Skill_Ji", 0.04f));
	Renderer_->GetTransform().SetLocalPosition({ 600.f, 100.f });
	Renderer_->ChangeFrameAnimation("Skill_Ji");
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
