#include "PreCompile.h"
#include "Boss.h"

Boss::Boss() 
{
}

Boss::~Boss() 
{
}

void Boss::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 50.f, 50.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 201.f, 237.f });	// Idle
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Boss_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Boss_Move", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Attack", FrameAnimation_DESC("Boss_Att1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Boss_Damaged", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Boss_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::IDLE);

	SetHP(1000);
	SetSpeed(30.f);
	SetPixelCheckPos(35.f, -110.f);
	SetMonsterName(MONSTERNAME::Boss);
	SetMonsterType(MONSTERTYPE::ATTACK);
	SetMonsterDir(ACTORDIR::NONE);

}

void Boss::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

