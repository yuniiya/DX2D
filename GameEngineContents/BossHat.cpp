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
	Collision_->Off();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({275.f, 1235.f});
	Renderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Hat_Fall", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Ground", FrameAnimation_DESC("Hat_Ground", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Hat_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("End", FrameAnimation_DESC("Hat_End", 0.1f));
	Renderer_->ChangeFrameAnimation("Fall");
	ChangeState(BossHatState::Fall);

	HitRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	HitRenderer_->GetTransform().SetLocalScale({ 230.f, 176.f });
	HitRenderer_->CreateFrameAnimationFolder("Hit", FrameAnimation_DESC("Hat_Hit", 0.12f));
	HitRenderer_->ChangeFrameAnimation("Hit");
	HitRenderer_->Off();


	Renderer_->AnimationBindStart("Fall", std::bind(&BossHat::BindFallEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Ground", std::bind(&BossHat::BindGroundEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Idle", std::bind(&BossHat::BindIdleEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("End", std::bind(&BossHat::BindEndEnd, this, std::placeholders::_1));
	HitRenderer_->AnimationBindStart("Hit", std::bind(&BossHat::BindHitEnd, this, std::placeholders::_1));
}

void BossHat::Update(float _DeltaTime)
{
	StateUpdate();
}

void BossHat::ChangeState(BossHatState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case BossHatState::Fall:
			FallStart();
			break;
		case BossHatState::Ground:
			GroundStart();
			break;
		case BossHatState::Idle:
			IdleStart();
			break;
		case BossHatState::End:
			EndStart();
			break;
		}
	}

	CurState_ = _State;
}

void BossHat::StateUpdate()
{
	switch (CurState_)
	{
	case BossHatState::Fall:
		FallUpdate();
		break;
	case BossHatState::Ground:
		GroundUpdate();
		break;
	case BossHatState::Idle:
		IdleUpdate();
		break;
	case BossHatState::End:
		EndUpdate();
		break;
	}
}

void BossHat::FallStart()
{
	Renderer_->ChangeFrameAnimation("Fall");
	Renderer_->ScaleToTexture();
}

void BossHat::GroundStart()
{
	Renderer_->ChangeFrameAnimation("Ground");
	Renderer_->ScaleToTexture();
}

void BossHat::IdleStart()
{
	Renderer_->ChangeFrameAnimation("Idle");
	Renderer_->ScaleToTexture();
}

void BossHat::EndStart()
{
	Renderer_->ChangeFrameAnimation("End");
	Renderer_->ScaleToTexture();
}

void BossHat::FallUpdate()
{

}

void BossHat::GroundUpdate()
{

}

void BossHat::IdleUpdate()
{
}

void BossHat::EndUpdate()
{
}

void BossHat::BindFallEnd(const FrameAnimation_DESC& _Info)
{
	ChangeState(BossHatState::Ground);
	return;
}

void BossHat::BindGroundEnd(const FrameAnimation_DESC& _Info)
{
	Collision_->On();
	HitRenderer_->On();
	ChangeState(BossHatState::Idle);
	return;
}

void BossHat::BindIdleEnd(const FrameAnimation_DESC& _Info)
{
	ChangeState(BossHatState::End);
	return;
}

void BossHat::BindEndEnd(const FrameAnimation_DESC& _Info)
{
	Death();
}

void BossHat::BindHitEnd(const FrameAnimation_DESC& _Info)
{
	HitRenderer_->Off();
}
