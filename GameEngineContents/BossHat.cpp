#include "PreCompile.h"
#include "BossHat.h"

BossHat::BossHat() 
	: Renderer_(nullptr)
	, HitRenderer_(nullptr)
	, Collision_(nullptr)
{
}

BossHat::~BossHat() 
{
}

void BossHat::Start()
{
	GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::BOSSSKILL});

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 170.f, 180.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTERSKILL);

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Hat_Fall", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Hat_0", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Hat_1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("End", FrameAnimation_DESC("Hat_End", 0.1f));
	Renderer_->ChangeFrameAnimation("Fall");
	Renderer_->ScaleToTexture();
}

void BossHat::Update(float _DeltaTime)
{

}

