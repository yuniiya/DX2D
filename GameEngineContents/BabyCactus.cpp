#include "PreCompile.h"
#include "BabyCactus.h"

BabyCactus::BabyCactus() 
{
}

BabyCactus::~BabyCactus() 
{
}

void BabyCactus::Start()
{
	Monster::Start();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 50.f, 65.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 54.f, 67.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Cactus_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Cactus_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Cactus_Hit", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Cactus_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100.f);
	SetSpeed(30.f);
	SetPixelCheckPos(9, -33);
	SetMonsterName(MONSTERNAME::BabyCactus);
	SetMonsterType(MONSTERTYPE::DEFAULT);
	SetMonsterDir(ACTORDIR::NONE);
}

void BabyCactus::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

