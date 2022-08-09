#include "PreCompile.h"
#include "BrownRabbit.h"

BrownRabbit::BrownRabbit() 
{
}

BrownRabbit::~BrownRabbit() 
{
}

void BrownRabbit::Start()
{
	Monster::Start();
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 50.f, 50.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 60.f, 58.f });
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Rabbit2_Idle", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Rabbit2_Walk", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Rabbit2_Hit", 0.5f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Rabbit2_Die", 0.2f));
	Renderer_->ChangeFrameAnimation("Idle");
	ChangeState(MONSTERSTATE::MOVE);

	SetHP(100);
	SetSpeed(30.f);
	SetPixelCheckPos(10.f, -28.f);
	SetMonsterName(MONSTERNAME::Rabbit);
	SetMonsterType(MONSTERTYPE::DEFAULT);
	SetMonsterDir(ACTORDIR::NONE);
}

void BrownRabbit::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

