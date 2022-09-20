#include "PreCompile.h"
#include "DamageNumber.h"
#include "Monster.h"

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

	DamageNumberRender();
}

void DamageNumber::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::DAMAGE});
}

void DamageNumber::Update(float _DeltaTime)
{
	// 데미지 길이만큼 반복문 
	for (int i = 0; i < DamageNumbers_.size(); i++)
	{
		if (Time_ > 0.4f)
		{
			DamageNumbers_[i]->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;
		}
		if (DamageNumbers_[i]->GetPixelData().MulColor.a < 0)
		{
			DamageNumbers_[i]->GetPixelData().MulColor.a = 0;
		}
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

void DamageNumber::DamageNumberRender()
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
		Renderer->GetTransform().SetLocalPosition({ MonsterPos.x + i * 27,  MonsterPos.y + 100.f});
		DamageNumbers_.push_back(Renderer);
	}
}

void DamageNumber::DamageNumberUpdate(GameEngineTextureRenderer* _Renderer)
{
	//if (Time_ > 0.4f)
	//{
	//	_Renderer->GetPixelData().MulColor.a -= GameEngineTime::GetDeltaTime() * 1.8f;
	//}
	//else if (Time_ > 1.5f)
	//{
	//	Time_ = 0.f;
	//	Death();
	//}

	//if (_Renderer->GetPixelData().MulColor.a < 0)
	//{
	//	_Renderer->GetPixelData().MulColor.a = 0;
	//}

	//MoveDir_ = { 0.f, 15.f };
	//_Renderer->GetTransform().SetLocalMove(MoveDir_ * GameEngineTime::GetDeltaTime());
}

