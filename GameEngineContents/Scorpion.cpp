#include "PreCompile.h"
#include "Scorpion.h"

Scorpion::Scorpion() 
{
}

Scorpion::~Scorpion() 
{
}

void Scorpion::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 70.f, 55.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 79.f, 61.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Scol_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Scol_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Scol_Hit", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Scol_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100);
	SetSpeed(30.f);
	SetPixelCheckPos(15.f, -25.f);
	SetMonsterName(MONSTERNAME::Scorpion);
	SetMonsterType(MONSTERTYPE::DEFAULT);
	SetMonsterDir(ACTORDIR::NONE);
}

void Scorpion::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

