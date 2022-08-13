#include "PreCompile.h"
#include "WhiteRabbit.h"

WhiteRabbit::WhiteRabbit() 
{
}

WhiteRabbit::~WhiteRabbit() 
{
}

void WhiteRabbit::Start()
{
	Monster::Start();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 50.f, 50.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 67.f, 68.f });	// Move
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Rabbit1_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Rabbit1_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Rabbit1_Hit", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Rabbit1_Die", 0.1f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100);
	SetSpeed(30.f);
	SetPixelCheckPos(10.f, -28.f);
	SetMonsterName(MONSTERNAME::WhiteRabbit);
	SetMonsterType(MONSTERTYPE::DEFAULT);
	SetMonsterDir(ACTORDIR::NONE);
}

void WhiteRabbit::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

