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

		// ������ ���̸�ŭ �ݺ��� 
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

		// ������ ���̸�ŭ �ݺ��� 
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
	// int ������ �������� ���ڿ��� ��ȯ
	std::string DamageStr = std::to_string(Damage_);	
	// ������ �ڸ�����ŭ �ݺ����� ���� ���� �ؽ�ó ��������
	for (int i = 0; i < DamageStr.size(); i++)
	{
		int Idx = DamageStr[i] - '0';
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		// ��� ������ �ؽ�ó�� �����ص� vector���� ������ ���ڿ� �´� �ؽ�ó ��������
		GameEngineTexture* Texture = DamageRenderManager::DamageMgr_->GetDamageTexture(DamageType_, Idx);
		// �ؽ�ó�� �������� ������ ��� ���� ó��
		if (nullptr == Texture)
		{
			MsgBoxAssert("������ �ؽ�ó�� �������� �� �߽��ϴ�.");
			return;
		}
		// ������ �ؽ�ó ����
		Renderer->SetTexture(Texture);
		Renderer->ScaleToTexture();
		// ���� ������ �ΰ� ��ġ ����
		Renderer->GetTransform().SetLocalPosition({ _Pos.x + i * 27 ,  _Pos.y + 100.f + GameEngineRandom::MainRandom.RandomFloat(-5.f, 5.f) });
		// �ؽ�ó���� ��¿� vector�� ������ ��, ȭ�鿡 ������
		_Vector.push_back(Renderer);
	}
}

