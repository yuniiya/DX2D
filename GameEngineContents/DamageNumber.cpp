#include "PreCompile.h"
#include "DamageNumber.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>

DamageNumber::DamageNumber() 
	: Time_(0.f)
	, IsDamaged_(false)
	, Monster_(nullptr)
	, Damage_(0)
{
}

DamageNumber::~DamageNumber() 
{
}

void DamageNumber::SetDamage(int _Damage)
{
	Damage_ = _Damage;

	switch (DamageType_)
	{
	case DamageType::Player:
		PlayerDamageNumberRender();
		break;
	case DamageType::Monster:
		MonsterDamageNumberRender();
		break;
	default:
		break;
	}
}

void DamageNumber::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::DAMAGE});
}

void DamageNumber::Update(float _DeltaTime)
{
	switch (DamageType_)
	{
	case DamageType::Player:
	{
		// 데미지 길이만큼 반복문 
		for (int i = 0; i < PlayerDamageNumbers_.size(); i++)
		{
			if (Time_ > 0.4f)
			{
				PlayerDamageNumbers_[i]->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;
			}
			if (PlayerDamageNumbers_[i]->GetPixelData().MulColor.a < 0)
			{
				PlayerDamageNumbers_[i]->GetPixelData().MulColor.a = 0;
			}
		}
	}
		break;
	case DamageType::Monster:
	{
		// 데미지 길이만큼 반복문 
		for (int i = 0; i < MonsterDamageNumbers_.size(); i++)
		{
			if (Time_ > 0.4f)
			{
				MonsterDamageNumbers_[i]->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;
			}
			if (MonsterDamageNumbers_[i]->GetPixelData().MulColor.a < 0)
			{
				MonsterDamageNumbers_[i]->GetPixelData().MulColor.a = 0;
			}
		}
	}
		break;
	default:
		break;
	}

	if (Time_ > 1.5f)
	{
		Time_ = 0.f;
		Death();
	}

	MoveDir_ = { 0.f, 15.f };
	GetTransform().SetLocalMove(MoveDir_ * _DeltaTime);

	if (true == IsDamaged_)
	{
		Time_ += _DeltaTime;
	}
}

void DamageNumber::MonsterDamageNumberRender()
{
	IsDamaged_ = true;
	// 몬스터 랜덤 데미지를 string으로 변환
	std::string DamageStr = std::to_string(Damage_);			
	float4 MonsterPos = Monster_->GetTransform().GetLocalPosition();

	// 데미지 길이만큼 반복문 
	for (int i = 0; i < DamageStr.size(); i++)
	{
		std::string SubStr = DamageStr.substr(i, 1);
		TextureName_ = SubStr;

		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("RedDamage1_0" + SubStr + ".png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ MonsterPos.x + i * 27 ,  MonsterPos.y + 100.f + GameEngineRandom::MainRandom.RandomFloat(-5.f, 5.f)});
		MonsterDamageNumbers_.push_back(Renderer);
	}
}

void DamageNumber::PlayerDamageNumberRender()
{
	IsDamaged_ = true;
	// 몬스터 랜덤 데미지를 string으로 변환
	std::string DamageStr = std::to_string(Damage_);
	float4 Pos = Player::MainPlayer_->GetPosition();

	// 데미지 길이만큼 반복문 
	for (int i = 0; i < DamageStr.size(); i++)
	{
		std::string SubStr = DamageStr.substr(i, 1);
		TextureName_ = SubStr;

		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("VioletDamage1_0" + SubStr + ".png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ Pos.x + i * 27 ,  Pos.y + 100.f + GameEngineRandom::MainRandom.RandomFloat(-5.f, 5.f) });
		PlayerDamageNumbers_.push_back(Renderer);
	}
}

