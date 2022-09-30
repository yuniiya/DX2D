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
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::EFFECT});

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 130.f, 130.f });
	Collision_->ChangeOrder(BossAttackType::Hat);
	Collision_->Off();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({275.f, 1235.f});
	Renderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Hat_Fall", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Ground", FrameAnimation_DESC("Hat_Ground", 0.16f));
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Hat_Idle", 0.08f));
	Renderer_->CreateFrameAnimationFolder("End", FrameAnimation_DESC("Hat_End", 0.08f));
	Renderer_->ChangeFrameAnimation("Fall");
	ChangeState(BossHatState::Fall);

	HitRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	HitRenderer_->GetTransform().SetLocalScale({ 230.f, 176.f });
	HitRenderer_->CreateFrameAnimationFolder("Hit", FrameAnimation_DESC("Hat_Hit", 0.12f));
	HitRenderer_->ChangeFrameAnimation("Hit");
	HitRenderer_->Off();


	Renderer_->AnimationBindEnd("Fall", std::bind(&BossHat::BindFallEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Ground", std::bind(&BossHat::BindGroundEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Idle", std::bind(&BossHat::BindIdleEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("End", std::bind(&BossHat::BindEndEnd, this, std::placeholders::_1));
	HitRenderer_->AnimationBindEnd("Hit", std::bind(&BossHat::BindHitEnd, this, std::placeholders::_1));
}

void BossHat::Update(float _DeltaTime)
{
	StateUpdate();
	CollisionCheck();
}

GameEngineTexture* BossHat::GetCurMapTexture()
{
	if (CurLevelName_ == "BOSS")
	{
	}

	MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();
	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	return MapTexture_;
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

void BossHat::CollisionCheck()
{
}

bool BossHat::StagePixelCheck()
{
	float4 Pos = 0.0f;
	GetCurMapTexture();

	float4 DownColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() - 18);

	// 땅에 닿았다
	if (true == DownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		IsGround_ = true;
		ChangeState(BossHatState::Ground);
		return true;
	}

	return true;
}

void BossHat::FallStart()
{
	Renderer_->ChangeFrameAnimation("Fall");
	Renderer_->ScaleToTexture();
}

void BossHat::GroundStart()
{
	IsGround_ = false;
	GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, -440.f + 28.f, (int)ZOrder::EFFECT });
	//HitRenderer_->On();
	//HitRenderer_->GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, Player::MainPlayer_->GetPosition().y + 28.f });
	Collision_->On();
	Renderer_->ChangeFrameAnimation("Ground");
	Renderer_->ScaleToTexture();
}

void BossHat::IdleStart()
{
	GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x - 4.5f, -440.f + 10.f, (int)ZOrder::EFFECT });
	Renderer_->ChangeFrameAnimation("Idle");
	Renderer_->ScaleToTexture();
}

void BossHat::EndStart()
{
	Collision_->Off();
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
	IsGround_ = true;
	ChangeState(BossHatState::Ground);
	return;
}

void BossHat::BindGroundEnd(const FrameAnimation_DESC& _Info)
{
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
	IsGround_ = false;
	Death();
}

void BossHat::BindHitEnd(const FrameAnimation_DESC& _Info)
{
	HitRenderer_->Off();
}
