#include "PreCompile.h"
#include "ContentsUI.h"
#include "Player.h"

ContentsUI* ContentsUI::MainUI = nullptr;
//GameEngineTextureRenderer* ContentsUI::HpBar_ = nullptr;

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
	, ratio_(0.f)
	, Level_(nullptr)
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

void ContentsUI::HPBarUpdate(float _CurHP, float _MaxHP)
{
	float ratio = _CurHP / _MaxHP;

	HpBar_->GetTransform().SetLocalScale({ HPBarScale_.x * ratio, HPBarScale_.y });
}

void ContentsUI::MPBarUpdate(float _CurMP, float _MaxMP)
{
	float ratio = _CurMP / _MaxMP;

	MpBar_->GetTransform().SetLocalScale({ MPBarScale_.x * ratio, MPBarScale_.y });
}

void ContentsUI::ExpBarUpdate(float _CurExp, float _MaxExp)
{
	float ratio = _CurExp / _MaxExp;

	ExpBar_->GetTransform().SetLocalScale({ ExpBarScale_.x * ratio, ExpBarScale_.y });
}

void ContentsUI::MainBarPosUpdate()
{
	CurHP_ = Player::MainPlayer_->GetHP();
	CurMP_ = Player::MainPlayer_->GetMP();
	CurExp_ = Player::MainPlayer_->GetExp();

	if (100.f == CurHP_)
	{
		HpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 11.f, CamPos_.y - 308.f, (int)ZOrder::UI });	// 초기 세팅
	}
	else
	{
		HpBar_->GetTransform().SetLocalPosition(float4{ (CamPos_.x + 11.f) - (100.f - CurHP_), CamPos_.y - 308.f, (int)ZOrder::UI });
	}

	if (100.f == CurMP_)
	{
		MpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 10.5f, CamPos_.y - 325.f, (int)ZOrder::UI});	// 초기 세팅
	}
	else
	{
		MpBar_->GetTransform().SetLocalPosition(float4{ (CamPos_.x + 10.5f) - (100.f - CurMP_), CamPos_.y - 325.f, (int)ZOrder::UI });
	}

	if (60.f == CurExp_)
	{		
		ExpBar_->GetTransform().SetLocalScale({ ExpBarScale_.x * 0.6f, ExpBarScale_.y });
		ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 252.f , CamPos_.y - 352.5f, (int)ZOrder::UI });	// 초기 세팅
	}
	else if (60.f < CurExp_)
	{
		ExpBar_->GetTransform().SetLocalPosition(float4{ (CamPos_.x - 252.f) + CurExp_, CamPos_.y - 352.5f, (int)ZOrder::UI});
	}
	else if(60.f > CurExp_)
	{
		ExpBar_->GetTransform().SetLocalPosition(float4{ (CamPos_.x - 252.f) + CurExp_, CamPos_.y - 352.5f, (int)ZOrder::UI });
	}
}

void ContentsUI::LevelImageUpdate()
{
	float PlayerLevel = Player::MainPlayer_->GetPlayerLevel();

	if (121.f == PlayerLevel)
	{
		Level_->SetTexture("Lv121.png");
	}
	else if (122.f == PlayerLevel)
	{
		Level_->SetTexture("Lv122.png");
	}
	else if (123.f == PlayerLevel)
	{
		Level_->SetTexture("Lv123.png");
	}
}

void ContentsUI::Start()
{
	//GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::UI});

	HpBar_ = CreateComponent<GameEngineTextureRenderer>();
	HpBar_->SetTexture("HP.png");
	HpBar_->ScaleToTexture();
	HpBar_->GetTransform().SetLocalScale({ HpBar_->GetTransform().GetLocalScale().x, HpBar_->GetTransform().GetLocalScale().y, (int)ZOrder::UI});
	HPBarScale_ = HpBar_->GetTransform().GetLocalScale();

	MpBar_ = CreateComponent<GameEngineTextureRenderer>();
	MpBar_->SetTexture("MP.png");
	MpBar_->ScaleToTexture();
	MPBarScale_ = MpBar_->GetTransform().GetLocalScale();

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
	ExpBarScale_ = ExpBar_->GetTransform().GetLocalScale();
	ExpBar_->SetPivot(PIVOTMODE::LEFTTOP);

	//ExpBar_->GetTransform().SetLocalScale({ ExpPos_.x * 0.7f, ExpPos_.y });

	QuickSlotBack_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlotBack_->SetTexture("QuickSlotBack.png");
	QuickSlotBack_->ScaleToTexture();

	QuickSlot_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlot_->SetTexture("QuickSlot.png");
	QuickSlot_->ScaleToTexture();

	Level_ = CreateComponent<GameEngineTextureRenderer>();
	Level_->SetTexture("Lv120.png");
	Level_->ScaleToTexture();
}

void ContentsUI::Update(float _DeltaTime)
{
	MainUI = this;

	CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	//MpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 10.5f, CamPos_.y - 325.f });
	//ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 1.f , CamPos_.y - 352.5f });

	MainBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x, CamPos_.y - 308.f });
	QuickSlotBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 465.f, CamPos_.y - 308.f });
	QuickSlot_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 465.f, CamPos_.y - 308.f });
	ExpBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 2.f, CamPos_.y - 352.f, (int)ZOrder::UI });
	Level_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 49.f, CamPos_.y - 286.f });

	MainBarPosUpdate();

	LevelImageUpdate();
}

