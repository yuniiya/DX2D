#include "PreCompile.h"
#include "Sand.h"

Sand::Sand()
{
}

Sand::~Sand()
{
}

void Sand::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 100.f, 60.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 300.f, 300.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Sand_Idle", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Sand_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Sand_Hit", 0.5f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Sand_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100.f);
	SetSpeed(30.f);
	SetPixelCheckPos(18, -22);
	SetMonsterName(MONSTERNAME::Sand);
	SetMonsterType(MONSTERTYPE::DEFAULT);
}

void Sand::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

