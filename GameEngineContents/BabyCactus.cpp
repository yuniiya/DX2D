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
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 50.f, 65.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 54.f, 67.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Cactus_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Cactus_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Cactus_Hit", 0.5f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Cactus_Die", 0.2f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::IDLE);

	SetHP(100);
	SetSpeed(30.f);
	SetPixelCheckPos(9.f, -33.f);
	SetMonsterName(MONSTERNAME::BabyCactus);
	SetMonsterType(MONSTERTYPE::DEFAULT);
	//SetDir(ACTORDIR::LEFT);
}

void BabyCactus::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

