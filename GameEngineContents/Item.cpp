#include "PreCompile.h"
#include "Monster.h"
#include "Item.h"

Item::Item() 
	: Renderer_(nullptr)
	, MonsterName_(MONSTERNAME::MAX)
	, IsCreate(false)
	, Time_(0.0f)
{
}

Item::~Item() 
{
}

void Item::TimeAttackStart()
{
	IsCreate = true;
}

void Item::TimeAttackUpdate(GameEngineTextureRenderer* _Renderer)
{
	if (nullptr == _Renderer)
	{
		return;
	}

	if (Time_ > 10.f)
	{
		_Renderer->GetColorData().MulColor.a -= GameEngineTime::GetDeltaTime() * 1.8f;

		if (_Renderer->GetColorData().MulColor.a < 0)
		{
			Death();
		}
	}

	if (true == IsCreate)
	{
		Time_ += GameEngineTime::GetDeltaTime();
	}
}

void Item::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::ITEM});
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void Item::Update(float _DeltaTime)
{
	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->SetTexture("Item1_Rabbit1.png");
		Renderer_->GetTransform().SetLocalScale({28.f, 26.f});
	}
		break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->SetTexture("Item1_Rabbit2.png");
		Renderer_->GetTransform().SetLocalScale({ 29.f, 30.f });
	}
		break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->SetTexture("Item_Cactus1.png");
		Renderer_->GetTransform().SetLocalScale({ 32.f, 34.f });
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->SetTexture("Item_Sand1.png");
		Renderer_->GetTransform().SetLocalScale({ 33.f, 29.f });
	}
		break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->SetTexture("Item_Scor1.png");
		Renderer_->GetTransform().SetLocalScale({ 25.f, 27.f });
	}
		break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->SetTexture("Item_Freezer1.png");
		Renderer_->GetTransform().SetLocalScale({ 31.f, 31.f });
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->SetTexture("Item_Sparker1.png");
		Renderer_->GetTransform().SetLocalScale({ 28.f, 28.f });
	}
		break;
	}

	TimeAttackUpdate(Renderer_);
}

