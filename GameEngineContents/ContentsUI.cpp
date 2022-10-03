#include "PreCompile.h"
#include "ContentsUI.h"
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "QuickSlotItem.h"

ContentsUI* ContentsUI::MainUI_ = nullptr;

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
	, SlotCollision_(nullptr)
	, StartPosition_(0.f)
	, QuickSlotItem_(nullptr)
	, ItemType_(ItemType::MAX)
	, SlotKey_1(0)
	, SlotKey_2(0)
	, SlotKey_(0)
	, BarBgr_1(nullptr)
	, BarBgr_2(nullptr)
	, ExitNotice_(nullptr)
	, YesButton_(nullptr)
	, NoButton_(nullptr)
	, YesCollision_(nullptr)
	, NoCollision_(nullptr)
	, IsExitNoticeOn_(false)
	, IsExitOn_(false)

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

	HpBar_->GetTransform().SetLocalScale({ HPBarScale_.x * HPratio, HPBarScale_.y});
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

	HPBarUpdate(CurHP_, Player::MainPlayer_->GetMaxHP());
	MPBarUpdate(CurMP_, Player::MainPlayer_->GetMaxMP());
	ExpBarUpdate(CurExp_, Player::MainPlayer_->GetMaxExp());

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

	BarBgr_1 = CreateComponent<GameEngineUIRenderer>();
	BarBgr_1->SetTexture("BarBgr.png");
	BarBgr_1->ScaleToTexture();
	BarBgr_1->SetPivot(PIVOTMODE::LEFTTOP);
	BarBgr_1->GetTransform().SetLocalPosition({ -78.f, -300.f });

	BarBgr_2 = CreateComponent<GameEngineUIRenderer>();
	BarBgr_2->SetTexture("BarBgr.png");
	BarBgr_2->ScaleToTexture();
	BarBgr_2->SetPivot(PIVOTMODE::LEFTTOP);
	BarBgr_2->GetTransform().SetLocalPosition({ -78.f, -318.f });

	HpBar_ = CreateComponent<GameEngineUIRenderer>();
	HpBar_->SetTexture("HP.png");
	HpBar_->ScaleToTexture(); 
	HpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	HpBar_->GetTransform().SetLocalScale({ HpBar_->GetTransform().GetLocalScale().x, HpBar_->GetTransform().GetLocalScale().y });
	HPBarScale_ = HpBar_->GetTransform().GetLocalScale(); 
	HpBar_->GetTransform().SetLocalPosition({ -78.f, -300.f });

	MpBar_ = CreateComponent<GameEngineUIRenderer>();
	MpBar_->SetTexture("MP.png");
	MpBar_->ScaleToTexture();
	MpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	MPBarScale_ = MpBar_->GetTransform().GetLocalScale();
	MpBar_->GetTransform().SetLocalPosition({ -78.f, -318.f });

	MainBar_ = CreateComponent<GameEngineUIRenderer>();
	MainBar_->SetTexture("mainBar2.png");
	MainBar_->ScaleToTexture();
	MainBar_->GetTransform().SetLocalPosition({ 0.f, -308.f });

	ExpBack_ = CreateComponent<GameEngineUIRenderer>();
	ExpBack_->SetTexture("ExpBarBack.png");
	ExpBack_->SetPivot(PIVOTMODE::LEFTTOP);
	ExpBack_->GetTransform().SetLocalScale({ 1280.f, 16.f });
	ExpBack_->GetTransform().SetLocalPosition({ -640.f, -344.f });

	ExpBar_ = CreateComponent<GameEngineUIRenderer>();
	ExpBar_->SetTexture("ExpBar.png");
	ExpBar_->GetTransform().SetLocalScale({ 1272.f, 12.5f });
	ExpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	ExpBarPos_ = ExpBar_->GetTransform().GetLocalScale();
	ExpBarScale_ = ExpBar_->GetTransform().GetLocalScale();
	ExpBar_->GetTransform().SetLocalPosition({ -636.f, -346.f });

	Level_ = CreateComponent<GameEngineUIRenderer>();
	Level_->SetTexture("Lv120.png");
	Level_->ScaleToTexture();
	Level_->GetTransform().SetLocalPosition({-49.f, -286.f});

	QuickSlotBack_ = CreateComponent<GameEngineUIRenderer>();
	QuickSlotBack_->SetTexture("QuickSlotBack.png");
	QuickSlotBack_->SetPivot(PIVOTMODE::LEFTTOP);
	QuickSlotBack_->ScaleToTexture();
	QuickSlotBack_->GetTransform().SetLocalPosition({ 291.f, -276.f });

	QuickSlot_ = CreateComponent<GameEngineUIRenderer>();
	QuickSlot_->SetTexture("QuickSlot.png");
	QuickSlot_->SetPivot(PIVOTMODE::LEFTTOP);
	QuickSlot_->ScaleToTexture();
	QuickSlot_->GetTransform().SetLocalPosition({ 290.f, -273.f });

	ExitNotice_ = CreateComponent<GameEngineUIRenderer>();
	ExitNotice_->SetTexture("ExitNotice.png");
	ExitNotice_->ScaleToTexture();
	//ExitNotice_->GetTransform().SetLocalScale({249.f * 1.1f, 142.f * 1.1f });
	ExitNotice_->GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::UI });
	ExitNotice_->Off();

	YesButton_ = CreateComponent<GameEngineUIRenderer>();
	YesButton_->SetTexture("Notice.BtYes.normal.0.png");
	YesButton_->ScaleToTexture();
//	YesButton_->GetTransform().SetLocalScale({ 50.f * 1.1f, 23.f * 1.1f });
	YesButton_->GetTransform().SetLocalPosition({ -30.f, -47.f, (int)ZOrder::UI });
	YesButton_->Off();

	NoButton_ = CreateComponent<GameEngineUIRenderer>();
	NoButton_->SetTexture("Notice.BtNo.normal.0.png");
	NoButton_->ScaleToTexture();
	//NoButton_->GetTransform().SetLocalScale({ 50.f * 1.1f, 23.f * 1.1f });
	NoButton_->GetTransform().SetLocalPosition({ 30.f, -47.f, (int)ZOrder::UI });
	NoButton_->Off();

	YesCollision_ = CreateComponent<GameEngineCollision>();
	YesCollision_->SetUIDebugCamera();
	YesCollision_->GetTransform().SetLocalScale({45.f, 20.f });
	YesCollision_->ChangeOrder(GAMEOBJGROUP::UI);
	YesCollision_->GetTransform().SetLocalPosition({ YesButton_->GetTransform().GetLocalPosition().x, YesButton_->GetTransform().GetLocalPosition().y });
	YesCollision_->Off();

	NoCollision_ = CreateComponent<GameEngineCollision>();
	NoCollision_->SetUIDebugCamera();
	NoCollision_->GetTransform().SetLocalScale({ 45.f, 20.f });
	NoCollision_->ChangeOrder(GAMEOBJGROUP::UI);
	NoCollision_->GetTransform().SetLocalPosition({ NoButton_->GetTransform().GetLocalPosition().x, NoButton_->GetTransform().GetLocalPosition().y });
	NoCollision_->Off();

	StartPosition_ = float4{ 198.f, -215.f };
	float4 Pos = StartPosition_;
	for (int i = 0; i < 20; ++i)
	{
		if (i != 0 && 0 == i % 10)
		{
			Pos.y -= 37.f;
			Pos.x = StartPosition_.x;
		}

		Pos.x += 35.f;

		QuickSlotItem* ItemActor = GetLevel()->CreateActor<QuickSlotItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos.x, Pos.y, (int)ZOrder::UI});
		QuickSlotItemsList_.push_back(ItemActor);
		ItemActor->IsSlot_ = true;
		ItemActor->SetQuickSlotIndex(i);
	}

	SetLevelOverOn();
}

void ContentsUI::Update(float _DeltaTime)
{
	// 게임 종료
	GameExit();

	CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	MainBarScaleUpdate();
	LevelImageUpdate();

	// 4번키까지
	for (size_t i = 0; i < 4; i++)
	{
		// 퀵슬롯에 아이템이 있을 때만 체크
		if (ItemType::MAX == QuickSlotItemsList_[i]->GetItemType())
		{
			continue;
		}

		// 1 ~ 4번 키 
		std::string Input = std::to_string(i + 1);

		if (true == GameEngineInput::GetInst()->IsDown(Input))
		{
			QuickSlotItemsList_[i]->SlotKeyCheck();

			break;
		}
	}

}

void ContentsUI::GameExit()
{
	if (true == GameEngineInput::GetInst()->IsDown("Exit"))
	{
		if (true == IsExitOn_)
		{
			IsExitOn_ = false;
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			ExitNotice_->Off();
			YesButton_->Off();
			NoButton_->Off();
			YesCollision_->Off();
			NoCollision_->Off();
		}
		else
		{
			IsExitOn_ = true;
			GameEngineSound::SoundPlayOneShot("DlgNotice.mp3");
			ExitNotice_->On();
			YesButton_->On();
			NoButton_->On();
			YesCollision_->On();
			NoCollision_->On();
		}
	}

	if (true == YesCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			YesButton_->SetTexture("Notice.BtYes.pressed.0.png");

			GameEngineWindow::GetInst()->Off();
		}
		else
		{
			YesButton_->SetTexture("Notice.BtYes.mouseOver.0.png");
		}
	}
	else
	{
		YesButton_->SetTexture("Notice.BtYes.normal.0.png");
	}

	if (true == NoCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			NoButton_->SetTexture("Notice.BtNo.pressed.0.png");

			IsExitOn_ = false;
			ExitNotice_->Off();
			YesButton_->Off();
			NoButton_->Off();
			YesCollision_->Off();
			NoCollision_->Off();
		}
		else
		{
			NoButton_->SetTexture("Notice.BtNo.mouseOver.0.png");
		}
	}
	else
	{
		NoButton_->SetTexture("Notice.BtNo.normal.0.png");
	}

}


