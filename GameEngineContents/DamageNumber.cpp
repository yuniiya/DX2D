#include "PreCompile.h"
#include "DamageNumber.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "DamageRenderManager.h"

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
	float4 Pos = {};

	switch (DamageType_)
	{
	case DamageTextureType::Player:
	{
		Pos = Player::MainPlayer_->GetPosition();
		DamageNumberRender(Pos, PlayerDamageNumbers_);
	}
		break;
	case DamageTextureType::Monster:
	{
		Pos = Monster_->GetTransform().GetLocalPosition();
		DamageNumberRender(Pos, MonsterDamageNumbers_);
	}
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
	case DamageTextureType::Player:
	{
		if (true == PlayerDamageNumbers_.empty())
			return;

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
	case DamageTextureType::Monster:
	{
		if (true == MonsterDamageNumbers_.empty())
			return;

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

void DamageNumber::DamageNumberRender(float4 _Pos, std::vector<GameEngineTextureRenderer*>& _Vector)
{
	IsDamaged_ = true;
	// int 정수형 데미지를 문자열로 변환
	std::string DamageStr = std::to_string(Damage_);	
	// 데미지 자릿수만큼 반복문을 돌며 숫자 텍스처 가져오기
	for (int i = 0; i < DamageStr.size(); i++)
	{
		int Idx = DamageStr[i] - '0';
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		// 모든 데미지 텍스처를 보관해둔 vector에서 데미지 숫자에 맞는 텍스처 꺼내오기
		GameEngineTexture* Texture = DamageRenderManager::DamageMgr_->GetDamageTexture(DamageType_, Idx);
		// 텍스처를 가져오지 못했을 경우 예외 처리
		if (nullptr == Texture)
		{
			MsgBoxAssert("데미지 텍스처를 가져오지 못 했습니다.");
			return;
		}
		// 가져온 텍스처 지정
		Renderer->SetTexture(Texture);
		Renderer->ScaleToTexture();
		// 일정 간격을 두고 위치 지정
		Renderer->GetTransform().SetLocalPosition({ _Pos.x + i * 27 ,  _Pos.y + 100.f + GameEngineRandom::MainRandom.RandomFloat(-5.f, 5.f) });
		// 텍스처들을 출력용 vector에 보관한 뒤, 화면에 렌더링
		_Vector.push_back(Renderer);
	}
}

