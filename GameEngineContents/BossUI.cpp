#include "PreCompile.h"
#include "BossUI.h"
#include "Boss.h"

BossUI::BossUI() 
	: HPBack_(nullptr)
	, HPBar_(nullptr)
	, BossMaxHP_(0)
	, BossHP_(0)
	, Boss_(nullptr)
{
}

BossUI::~BossUI() 
{
}

void BossUI::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	HPBack_ = CreateComponent<GameEngineUIRenderer>();
	HPBack_->SetTexture("BossHp_Null.png");
	HPBack_->ScaleToTexture();
	HPBack_->SetPivot(PIVOTMODE::LEFTTOP);
	HPBack_->GetTransform().SetLocalPosition({ -400.f, 360.f });

	HPBar_ = CreateComponent<GameEngineUIRenderer>();
	HPBar_->SetTexture("BossHpbar.png");
	HPBar_->ScaleToTexture();
	HPBar_->SetPivot(PIVOTMODE::LEFTTOP);
	HPBar_->GetTransform().SetLocalPosition({ -360.f, 356.f });
	HPBarScale_ = HPBar_->GetTransform().GetLocalScale();
}

void BossUI::Update(float _DeltaTime)
{
	if (nullptr == Boss_)
	{
		return;
	}

	BossHP_ = Boss_->GetHP();
	BossMaxHP_ = Boss_->GetMaxHP();
	if (BossHP_ <= 0)
	{
		return;
	}

	float HPratio = BossHP_ / BossMaxHP_;

	HPBar_->GetTransform().SetLocalScale({ HPBarScale_.x * HPratio, HPBarScale_.y });

}

