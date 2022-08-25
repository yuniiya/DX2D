#include "PreCompile.h"
#include "Meso.h"
#include <GameEngineBase/GameEngineRandom.h>

Meso::Meso() 
	: Random_(0)
	, MesoAmount_(0.f)
	, Renderer_(nullptr)
	, Collision_(nullptr)
{
}

Meso::~Meso() 
{
}

void Meso::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::ITEM });
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
//	Renderer_->GetTransform().SetLocalScale({25.f, 24.f});		// MesoA
	Renderer_->GetTransform().SetLocalScale({ 33.f, 33.f });	// MesoB
	//Renderer_->GetTransform().SetLocalScale({ 32.f, 31.f });	// MesoC

	Renderer_->CreateFrameAnimationFolder("MesoA", FrameAnimation_DESC("MesoA", 0.1f));
	Renderer_->CreateFrameAnimationFolder("MesoB", FrameAnimation_DESC("MesoB", 0.16f));
	Renderer_->CreateFrameAnimationFolder("MesoC", FrameAnimation_DESC("MesoC", 0.16f));
	Renderer_->ChangeFrameAnimation("MesoA");
	Renderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 25.f, 25.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::OBJ);
	Collision_->Off();

	Random_ = GameEngineRandom::MainRandom.RandomInt(0, 2);
}

void Meso::Update(float _DeltaTime)
{
	Renderer_->On();

	switch (Random_)
	{
	case 0:
	{
		Renderer_->ChangeFrameAnimation("MesoA");
		Renderer_->GetTransform().SetLocalScale({ 25.f, 24.f });
		MesoAmount_ = 50.f;
	}
	break;
	case 1:
	{
		Renderer_->ChangeFrameAnimation("MesoB");
		Renderer_->GetTransform().SetLocalScale({ 33.f, 33.f });
		MesoAmount_ = 500.f;
	}
	break;
	case 2:
	{
		Renderer_->ChangeFrameAnimation("MesoC");
		Renderer_->GetTransform().SetLocalScale({ 32.f, 31.f });
		MesoAmount_ = 5000.f;
	}
	break;
	}

	TimeAttackUpdate(Renderer_);
	PickUpItemCheck(Renderer_);
}
