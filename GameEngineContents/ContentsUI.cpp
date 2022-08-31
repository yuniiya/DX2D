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
	, SlotPosition_(0.f)
	, Level_(nullptr)
	, SlotCollision_1(nullptr)
	, SlotCollision_2(nullptr)
	, SlotCollision_3(nullptr)
	, SlotCollision_4(nullptr)
	, SlotCollision_5(nullptr)

{
}

ContentsUI::~ContentsUI() 
{
}

void ContentsUI::HPBarUpdate(float _CurHP, float _MaxHP)
{
	if (_CurHP <= 0)
	{
		return;
	}

	float HPratio = _CurHP / _MaxHP;

	HpBar_->GetTransform().SetLocalScale({ HPBarScale_.x * HPratio, HPBarScale_.y });
}

void ContentsUI::MPBarUpdate(float _CurMP, float _MaxMP)
{
	if (_CurMP <= 0)
	{
		return;
	}

	float MPratio = _CurMP / _MaxMP;

	MpBar_->GetTransform().SetLocalScale({ MPBarScale_.x * MPratio, MPBarScale_.y });
}

void ContentsUI::ExpBarUpdate(float _CurExp, float _MaxExp)
{
	float Expratio = _CurExp / _MaxExp;

	ExpBar_->GetTransform().SetLocalScale({ ExpBarScale_.x * Expratio, ExpBarScale_.y });
}

void ContentsUI::MainBarScaleUpdate()
{
	CurHP_ = Player::MainPlayer_->GetHP();
	CurMP_ = Player::MainPlayer_->GetMP();
	CurExp_ = Player::MainPlayer_->GetExp();

	HPBarUpdate(CurHP_, 100.f);
	MPBarUpdate(CurMP_, 100.f);
	ExpBarUpdate(CurExp_, 100.f);

	if (60.f == CurExp_)
	{
		ExpBar_->GetTransform().SetLocalScale({ ExpBarScale_.x * 0.6f, ExpBarScale_.y });
		//ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 252.f , CamPos_.y - 352.5f, (int)ZOrder::UI });	// 초기 세팅
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
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::UI});

	HpBar_ = CreateComponent<GameEngineTextureRenderer>();
	HpBar_->SetTexture("HP.png");
	HpBar_->ScaleToTexture(); 
	HpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	HpBar_->GetTransform().SetLocalScale({ HpBar_->GetTransform().GetLocalScale().x, HpBar_->GetTransform().GetLocalScale().y });
	HPBarScale_ = HpBar_->GetTransform().GetLocalScale();

	MpBar_ = CreateComponent<GameEngineTextureRenderer>();
	MpBar_->SetTexture("MP.png");
	MpBar_->ScaleToTexture();
	MpBar_->SetPivot(PIVOTMODE::LEFTTOP);
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
	ExpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	ExpBarPos_ = ExpBar_->GetTransform().GetLocalScale();
	ExpBarScale_ = ExpBar_->GetTransform().GetLocalScale();


	QuickSlotBack_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlotBack_->SetTexture("QuickSlotBack.png");
	QuickSlotBack_->SetPivot(PIVOTMODE::LEFTTOP);
	QuickSlotBack_->ScaleToTexture();

	QuickSlot_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlot_->SetTexture("QuickSlot.png");
	QuickSlot_->SetPivot(PIVOTMODE::LEFTTOP);
	QuickSlot_->ScaleToTexture();

	Level_ = CreateComponent<GameEngineTextureRenderer>();
	Level_->SetTexture("Lv120.png");
	Level_->ScaleToTexture();

	// QuickSlot Collision //
	SlotCollision_1 = CreateComponent<GameEngineCollision>();
	SlotCollision_1->GetTransform().SetLocalScale({ 30.f, 30.f });
	SlotCollision_1->ChangeOrder(GAMEOBJGROUP::UI);

	SlotCollision_2 = CreateComponent<GameEngineCollision>();
	SlotCollision_2->GetTransform().SetLocalScale({ 30.f, 30.f });
	SlotCollision_2->ChangeOrder(GAMEOBJGROUP::UI);

	SlotCollision_3 = CreateComponent<GameEngineCollision>();
	SlotCollision_3->GetTransform().SetLocalScale({ 30.f, 30.f });
	SlotCollision_3->ChangeOrder(GAMEOBJGROUP::UI);

	SlotCollision_4 = CreateComponent<GameEngineCollision>();
	SlotCollision_4->GetTransform().SetLocalScale({ 30.f, 30.f });
	SlotCollision_4->ChangeOrder(GAMEOBJGROUP::UI);

	SlotCollision_5 = CreateComponent<GameEngineCollision>();
	SlotCollision_5->GetTransform().SetLocalScale({ 30.f, 30.f });
	SlotCollision_5->ChangeOrder(GAMEOBJGROUP::UI);

}

void ContentsUI::Update(float _DeltaTime)
{
	MainUI = this;

	CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	HpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 78.f, CamPos_.y - 300.f });
	MpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 78.f, CamPos_.y - 318.f });
	//ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 1.f , CamPos_.y - 352.5f });
	ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 634.f , CamPos_.y - 346.f });

	MainBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x, CamPos_.y - 308.f });
	QuickSlotBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 290.f, CamPos_.y - 275.f });
	QuickSlot_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 289.f, CamPos_.y - 273.f });
	ExpBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 2.f, CamPos_.y - 352.f});
	Level_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 49.f, CamPos_.y - 286.f });

	// QuickSlot Collision //
	SlotPosition_ = QuickSlotBack_->GetTransform().GetLocalPosition();
	SlotCollision_1->GetTransform().SetLocalPosition({ SlotPosition_.x + 15.f, SlotPosition_.y - 15.f});
	SlotCollision_2->GetTransform().SetLocalPosition({ SlotPosition_.x + 15.f + (35.f * 1.f), SlotPosition_.y - 15.f });
	SlotCollision_3->GetTransform().SetLocalPosition({ SlotPosition_.x + 15.f + (35.f * 2.f), SlotPosition_.y - 15.f });
	SlotCollision_4->GetTransform().SetLocalPosition({ SlotPosition_.x + 15.f + (35.f * 3.f), SlotPosition_.y - 15.f });
	SlotCollision_5->GetTransform().SetLocalPosition({ SlotPosition_.x + 15.f + (35.f * 4.f), SlotPosition_.y - 15.f });

	MainBarScaleUpdate();
	LevelImageUpdate();

}

