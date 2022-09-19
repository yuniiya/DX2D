#include "PreCompile.h"
#include "DamageNumber.h"

DamageNumber::DamageNumber() 
	: Renderer_(nullptr)
	, Time_(0.f)
{
}

DamageNumber::~DamageNumber() 
{
}

void DamageNumber::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::DAMAGE});

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("RedDamage1_00.png");
	Renderer_->ScaleToTexture();
}

void DamageNumber::Update(float _DeltaTime)
{
	if (Time_ > 0.4f)
	{
		Renderer_->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;
	}
	else if (Time_ > 1.5f)
	{
		Time_ = 0.f;
		Death();
	}

	if (Renderer_->GetPixelData().MulColor.a < 0)
	{
		Renderer_->GetPixelData().MulColor.a = 0;
	}

	MoveDir_ = { 0.f, 15.f };
	Renderer_->GetTransform().SetLocalMove(MoveDir_ * _DeltaTime);
	Time_ += _DeltaTime;
}

