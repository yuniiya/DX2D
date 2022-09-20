#include "PreCompile.h"
#include "DamageNumber.h"
#include "Monster.h"

DamageNumber::DamageNumber() 
	: Renderer_(nullptr)
	, Time_(0.f)
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

	//Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	//Renderer_->SetTexture("RedDamage1_00.png");
	//Renderer_->ScaleToTexture();
}

void DamageNumber::Update(float _DeltaTime)
{
	//if (Time_ > 0.4f)
	//{
	//	Renderer_->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;
	//}

	//if (Renderer_->GetPixelData().MulColor.a < 0)
	//{
	//	Renderer_->GetPixelData().MulColor.a = 0;
	//}

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
	// ���� ���� �������� string���� ��ȯ
	std::string DamageStr = std::to_string(Damage_);			
	float4 MonsterPos = Monster_->GetTransform().GetLocalPosition();

	// ������ ���̸�ŭ �ݺ��� 
	for (int i = 0; i < DamageStr.size(); i++)
	{
		std::string SubStr = DamageStr.substr(i, 1);
		TextureName_ = SubStr;

		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("RedDamage1_0" + SubStr + ".png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ MonsterPos.x + i * 22,  MonsterPos.y + 100.f});
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

