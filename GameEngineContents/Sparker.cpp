#include "PreCompile.h"
#include "Sparker.h"

Sparker::Sparker() 
{
}

Sparker::~Sparker() 
{
}

void Sparker::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 70.f, 70.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);

	SparkerAttCol_ = CreateComponent<GameEngineCollision>();
	SparkerAttCol_->GetTransform().SetLocalScale({ 70.f, 70.f });
	SparkerAttCol_->ChangeOrder(GAMEOBJGROUP::MONSTERSKILL);
	SparkerAttCol_->Off();

	SparkerAttEffect_ = CreateComponent<GameEngineTextureRenderer>();
	SparkerAttEffect_->CreateFrameAnimationFolder("Effect", FrameAnimation_DESC("Sparker_Eff", 0.08f));
	SparkerAttEffect_->GetTransform().SetLocalScale({ 79.f, 75.f });
	SparkerAttEffect_->ChangeFrameAnimation("Effect");
	SparkerAttEffect_->Off();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 80.f, 81.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Sparker_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Sparker_Walk", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Attack", FrameAnimation_DESC("Sparker_Att", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Sparker_Hit", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Sparker_Die", 0.1f));

	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100);
	SetSpeed(45.f);
	SetPixelCheckPos(15.f, -37.f);
	SetMonsterName(MONSTERNAME::Sparker);
	SetMonsterType(MONSTERTYPE::ATTACK);
	SetMonsterDir(ACTORDIR::NONE);
}

void Sparker::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}
