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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

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
	ChangeState(MONSTERSTATE::IDLE);

	SetHP(100);
	SetSpeed(30.f);
	SetPixelCheckPos(10.f, -28.f);
	SetMonsterName(MONSTERNAME::Rabbit);
	SetMonsterType(MONSTERTYPE::DEFAULT);
}

void BrownRabbit::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);
}

