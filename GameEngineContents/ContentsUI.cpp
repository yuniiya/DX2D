#include "PreCompile.h"
#include "ContentsUI.h"
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "QuickSlotItem.h"

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

	Level_ = CreateComponent<GameEngineTextureRenderer>();
	Level_->SetTexture("Lv120.png");
	Level_->ScaleToTexture();


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
	}
}

void ContentsUI::Update(float _DeltaTime)
{
	CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	HpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 78.f, CamPos_.y - 300.f });
	MpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 78.f, CamPos_.y - 318.f });
	//ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 1.f , CamPos_.y - 352.5f });
	ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 634.f , CamPos_.y - 346.f });

	MainBar_->GetTransform().SetLocalPosition(float4{ CamPos_.x, CamPos_.y - 308.f });
	ExpBack_->GetTransform().SetLocalPosition(float4{ CamPos_.x + 2.f, CamPos_.y - 352.f});
	Level_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 49.f, CamPos_.y - 286.f });

	MainBarScaleUpdate();
	LevelImageUpdate();
//	CollisionCheck();
//	SlotKeyCheck();
}

void ContentsUI::CollisionCheck()
{
	//if (nullptr == InventoryItem_)
	//{
	//	return;
	//}

	// 아이템을 잡아서 슬롯에 놨다

}

void ContentsUI::SlotKeyCheck()
{
	//if (ItemType_ == ItemType::ITEM_HP300)
	//{
	//	if (true == GameEngineInput::GetInst()->IsDown("1"))
	//	{
	//		Player::MainPlayer_->AddHP(5.f);
	//	}
	//}
	//else if (ItemType_ == ItemType::ITEM_MP300)
	//{
	//	if (true == GameEngineInput::GetInst()->IsDown("2"))
	//	{
	//		Player::MainPlayer_->AddMP(5.f);
	//	}
	//}

	//if (nullptr == InventoryItem_)
	//{
	//	return;
	//}
	//if (true == SlotKeyInputCheck())
	//{
	//	InventoryItem_->UsePotion();
	//}
	//if (true == GameEngineInput::GetInst()->IsDown("1"))
	//{
	//	InventoryItem_->UsePotion();
	//}
	//else if (true == GameEngineInput::GetInst()->IsDown("2"))
	//{
	//	InventoryItem_->UsePotion();
	//}
}

bool ContentsUI::SlotKeyInputCheck()
{
	if (true == GameEngineInput::GetInst()->IsDown("1")
		|| true == GameEngineInput::GetInst()->IsDown("2"))
	{
		return true;
	}
	return false;
}

