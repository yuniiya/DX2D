#include "PreCompile.h"
#include "ContentsUI.h"
#include "Player.h"

ContentsUI* ContentsUI::MainUI = nullptr;

ContentsUI::ContentsUI() 
	: MainBar_(nullptr)
	, ExpBack_(nullptr)
	, QuickSlot_(nullptr)
	, QuickSlotBack_(nullptr)
	, HpBar_(nullptr)
	, MpBar_(nullptr)
	, ExpBar_(nullptr)
	, CurHP_(0)
	, CurMP_(0)
	, CurExp_(0)
	, CamPos_(0.f)
	, HPBarScale_(0.f)
	, MPBarScale_(0.f)
	, ExpBarScale_(0.f)
	, HPBarPos_(0.f)
	, MPBarPos_(0.f)
	, ExpBarPos_(0.f)
	, HPratio_(0.f)
{
}

ContentsUI::~ContentsUI() 
{
}

bool ContentsUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void ContentsUI::CollisionCheck()
{
}

void ContentsUI::MainBarSizeUpdate()
{
	
}

void ContentsUI::HPBarUpdate(float _CurHP, float _MaxHP)
{
	HPratio_ = _CurHP / _MaxHP;

	HpBar_->GetTransform().SetLocalScale({ HPBarScale_.x * HPratio_, HPBarScale_.y });
}

void ContentsUI::MPBarUpdate(float _CurMP, float _MaxMP)
{
}

void ContentsUI::ExpBarUpdate(float _CurExp, float _MaxExp)
{
}

void ContentsUI::MainBarPosUpdate()
{
	CurHP_ = Player::MainPlayer_->GetHP();
	CurMP_ = Player::MainPlayer_->GetMP();
	CurExp_ = Player::MainPlayer_->GetExp();

	if (100.f == CurHP_)
	{
		HpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 10.5f, CamPos_.y - 308.f });	// 처음 세팅
	}
	else
	{
		HpBar_->GetTransform().SetLocalPosition(float4{ (CamPos_.x + 10.5f) - (100.f - CurHP_), CamPos_.y - 308.f });
	}
}

void ContentsUI::Start()
{
	HpBar_ = CreateComponent<GameEngineTextureRenderer>();
	HpBar_->SetTexture("HP.png");
	HpBar_->ScaleToTexture();
	HPBarScale_ = HpBar_->GetTransform().GetLocalScale();

	MpBar_ = CreateComponent<GameEngineTextureRenderer>();
	MpBar_->SetTexture("MP.png");
	MpBar_->ScaleToTexture();

	MainBar_ = CreateComponent<GameEngineTextureRenderer>();
	MainBar_->SetTexture("mainBar2.png");
	MainBar_->ScaleToTexture();

	ExpBack_ = CreateComponent<GameEngineTextureRenderer>();
	ExpBack_->SetTexture("ExpBarBack.png");
	ExpBack_->GetTransform().SetLocalScale({ 1280.f, 16.f });

	ExpBar_ = CreateComponent<GameEngineTextureRenderer>();
	ExpBar_->SetTexture("ExpBar.png");
	ExpBar_->GetTransform().SetLocalScale({ 1272.f, 12.5f });
	ExpBarPos_ = ExpBar_->GetTransform().GetLocalScale();

	//ExpBar_->GetTransform().SetLocalScale({ ExpPos_.x * 0.7f, ExpPos_.y });

	QuickSlotBack_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlotBack_->SetTexture("QuickSlotBack.png");
	QuickSlotBack_->ScaleToTexture();

	QuickSlot_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlot_->SetTexture("QuickSlot.png");
	QuickSlot_->ScaleToTexture();
}

void ContentsUI::Update(float _DeltaTime)
{
	MainUI = this;

	CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	MainBarPosUpdate();


	
	MpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 10.5f, CamPos_.y - 325.f });
	ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 1.f , CamPos_.y - 352.5f });

	MainBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x, CamPos_.y - 308.f });
	QuickSlotBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 465.f, CamPos_.y - 308.f });
	QuickSlot_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 465.f, CamPos_.y - 308.f });
	ExpBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 2.f, CamPos_.y - 352.f });
	
}

