#include "PreCompile.h"
#include "Freezer.h"

Freezer::Freezer() 
{
}

Freezer::~Freezer() 
{
}

void Freezer::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 70.f, 70.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 80.f, 82.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Freezer_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Freezer_Walk", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Attack", FrameAnimation_DESC("Freezer_Att", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Freezer_Hit", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Freezer_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100);
	SetSpeed(45.f);
	SetPixelCheckPos(15.f, -37.f);
	SetMonsterName(MONSTERNAME::Freezer);
	SetMonsterType(MONSTERTYPE::ATTACK);
	SetMonsterDir(ACTORDIR::NONE);
}

void Freezer::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}


