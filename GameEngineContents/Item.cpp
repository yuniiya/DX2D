#include "PreCompile.h"
#include "Monster.h"
#include "Item.h"
#include "Player.h"

Item::Item() 
	: Renderer_(nullptr)
	, MonsterName_(MONSTERNAME::MAX)
	, IsCreate(false)
	, Time_(0.0f)
	, MoveDir_({0.f, 6.f})
	, MoveTime_(0.0f)
	, IsPick(false)
	, Collision_(nullptr)
	, PickTime_(0.f)
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
	UpDownMove();
	PickUpItem(_Renderer);

	if (nullptr == _Renderer)
	{
		return;
	}

	if (true == IsPick)
	{
		return;
	}

	/*if (Time_ > 10.f)
	{
		_Renderer->GetColorData().MulColor.a -= GameEngineTime::GetDeltaTime() * 1.8f;

		if (_Renderer->GetColorData().MulColor.a < 0)
		{
			Death();
		}
	}*/

	if (true == IsCreate)
	{
		Time_ += GameEngineTime::GetDeltaTime();
		MoveTime_ += GameEngineTime::GetDeltaTime();
	}
}

void Item::UpDownMove()
{
	if (0.8f < MoveTime_)
	{
		if (6.f == MoveDir_.y)
		{
			MoveDir_.y = -6.f;
		}
		else if (-6.f == MoveDir_.y)
		{
			MoveDir_.y = 6.f;
		}
		
		MoveTime_ = 0.f;
	}

	GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());
}

void Item::PickUpItem(GameEngineTextureRenderer* _Renderer)
{
	if (nullptr == this)
	{
		return;
	}

	float4 PlayerPos = Player::MainPlayer_->GetPosition();

	if (30.f < abs(PlayerPos.x - GetItemPosition().x))
	{
		return;
	}

	
	if (false == IsPick)
	{
		if (true == GameEngineInput::GetInst()->IsDown("Pick"))
		{
			GameEngineSound::SoundPlayOneShot("PickUpItem.mp3");	// 플레이어쪽으로 끌려오게?
			IsPick = true;

			if (PlayerPos.x < GetItemPosition().x)		// 플레이어가 왼쪽
			{
				MoveDir_ = { -40.f, 20.f };
			}
			else if (PlayerPos.x >= GetItemPosition().x)	// 오른쪽
			{
				MoveDir_ = { 40.f, 20.f };
			}

			GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		}

	}
}

void Item::PickUpItemCheck(GameEngineTextureRenderer* _Renderer)
{
	// 다 주워졌다
	if (PickTime_ > 0.5f)
	{
		Death();	// 저장
		_Renderer->GetColorData().MulColor.a = 0;

		PickTime_ = 0.f;
		IsPick = false;
	}
	if (true == IsPick)
	{
		PickTime_ += GameEngineTime::GetDeltaTime();
		_Renderer->GetColorData().MulColor.a -= GameEngineTime::GetDeltaTime() * 3.f;
	}
}


void Item::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::ITEM});
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({25.f, 25.f});
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



	PickUpItemCheck(Renderer_);
	TimeAttackUpdate(Renderer_);
	
}

