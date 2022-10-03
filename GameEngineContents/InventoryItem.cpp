#include "PreCompile.h"
#include "InventoryItem.h"
#include "Inventory.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Mouse.h"
#include "MouseSlot.h"
#include "ContentsUI.h"
#include "QuickSlotItem.h"
#include "ContentsFont.h"

InventoryItem::InventoryItem()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, IsInvenOn_(false)
	, ItemType_(ItemType::MAX)
	, ItemCountFont_(nullptr)
	, MouseCollision_(nullptr)
	, MouseRenderer_(nullptr)
	, MouseAnimationRenderer_(nullptr)
	, DragStartSound_(false)
	, DragEndSound_(false)
	, IsHold_(false)
	, MouseSlotRenderer_(nullptr)
	, Index_(0)
	, SlotIndex_(0)
	, IsDoneHolding_(false)
	, InventorySlotType_(InventorySlotType::MAX)
	, IsCollideSlot_(false)
	, IsSlot_(false)
	, MonsterName_(MONSTERNAME::MAX)
	, MouseSlot_(nullptr)
	, PotionType_(PotionType::MAX)
	, HPAmount_(0.f)
	, MPAmount_(0.f)
{
	ItemState_.Count_ = 0;
	ItemState_.Cost_ = 500;
}

InventoryItem::~InventoryItem() 
{
}

void InventoryItem::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	Renderer_->Off();

	ItemCountFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemCountFont_->SetFontType(FontType::Normal);
	ItemCountFont_->GetNormalFontRenderer()->SetText(std::to_string(ItemState_.Count_));
	ItemCountFont_->SetTextSize(17.f);
	ItemCountFont_->On();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({30.f, 28.f});
	Collision_->ChangeOrder((int)GAMEOBJGROUP::SLOTUI);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 76.f });

	SetLevelOverOn();
}

void InventoryItem::Update(float _DeltaTime)
{
	if (GetCount() <= 0)
	{
		SetItemType(ItemType::MAX);
		SetCount(0);
		ItemCountFont_->Off();
	}


	ItemMouseHold();
}

void InventoryItem::LevelStartEvent()
{
	// 인벤토리가 켜져있을 때만 아이템 카운트 On
	ItemCountFont_->GetNormalFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
}

void InventoryItem::ItemMouseHold()
{
	//// 인벤토리가 켜져있을 때만 충돌체크
	//if (true == Inventory::MainInventory_->IsInvenOn)
	//{
	//	// 인벤토리가 켜져있을 때만 아이템 카운트 On
	//	ItemCountFont_->GetNoramlFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
	//}

	// 아이템을 놨다
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsHold_)
	{
		GameEngineSound::SoundPlayOneShot("DragEnd.mp3");
		//dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_ = false;
		//dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsDoneHolding_ = true;

		Mouse::MainMouse_->GetMouseSlot()->IsHold_ = false;
		Mouse::MainMouse_->GetMouseSlot()->IsDoneHolding_ = true;

		IsHold_ = false;
		MouseSlotRenderer_->Off();
	}
	if (true == DragStartSound_)
	{
		DragStartSound_ = false;
		GameEngineSound::SoundPlayOneShot("DragStart.mp3");
	}
}

void InventoryItem::CollisionCheck()
{
	MouseCollision_ = Mouse::MainMouse_->GetMouseCol();
	MouseRenderer_ = Mouse::MainMouse_->GetMouseRenderer();
	MouseAnimationRenderer_ = Mouse::MainMouse_->GetMouseAnimationRenderer();
	MouseSlotRenderer_ = Mouse::MainMouse_->GetMouseSlot()->GetRenderer();
	MouseSlot_ = Mouse::MainMouse_->GetMouseSlot();

	// 3) 아이템을 잡은 상태에서 놨다
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && 
		MouseSlot_->GetInventoryItem() != nullptr)
	{
		// 4) 놓은 칸의 아이템 타입을 슬롯 아이템의 아이템 타입으로 지정
		// 5) 슬롯 렌더러 -> 빈 칸으로 지정 및 null로 초기화 
		// 6-1) 슬롯의 아이템과 인벤토리 아이템이 같다
		if (GetItemType() == MouseSlot_->GetInventoryItem()->GetItemType())
		{
			// 같은 칸이다
			if (SlotIndex_ == MouseSlot_->GetInventoryItem()->GetSlotIndex())
			{
	/*			MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
				MouseSlot_->GetInventoryItem()->SetCount(0);
				MouseSlot_->GetInventoryItem()->GetFontRenderer()->Off();
				MouseSlot_->SetInventoryItem(nullptr);*/
				return;
			}
			else // 다른 칸이다
			{
				SetCount(MouseSlot_->GetInventoryItem()->GetCount() + GetCount());
				//ItemCountFontUpdate();
				// 빈칸의 폰트 렌더러 위치 설정
				ItemCountFont_->GetNormalFontRenderer()->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });
				// 빈 칸의 아이템 타입 슬롯 아이템 타입으로 설정
				SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());

				MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
				// 슬롯 폰트 오프
				MouseSlot_->GetInventoryItem()->SetCount(0);
				MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->Off();
				// 슬롯 아이템 null로 만들기
				MouseSlot_->SetInventoryItem(nullptr);
			}
			
		}	// 6-2) 빈 칸이다
		else if (GetItemType() == ItemType::MAX)								
		{
			// 빈 칸의 아이템 카운트 슬롯 아이템 카운트로 설정
			SetCount(MouseSlot_->GetInventoryItem()->GetCount());
			//ItemCountFontUpdate();
			// 빈칸의 폰트 렌더러 위치 설정
			ItemCountFont_->GetNormalFontRenderer()->SetScreenPostion({GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });
			// 빈 칸의 아이템 타입 슬롯 아이템 타입으로 설정
			SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());

			MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
			// 슬롯 폰트 오프
			MouseSlot_->GetInventoryItem()->SetCount(0);
			MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->Off();
			// 슬롯 아이템 null로 만들기
			MouseSlot_->SetInventoryItem(nullptr);
			
			
		} // 6-3) 다른 아이템이 이미 있다	-> 체인지
		else if (GetItemType() != MouseSlot_->GetInventoryItem()->GetItemType() && GetItemType() != ItemType::MAX)
		{
			// 2를 3에 담아두기
			ItemType TempItemType = GetItemType();
			int TempCount = GetCount();
			//Slot->SetInventoryItem(Slot->GetInventoryItem());

			// 2를 1로
			SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());
			SetCount(MouseSlot_->GetInventoryItem()->GetCount());
			
			// 1을 3으로
			MouseSlot_->GetInventoryItem()->SetItemType(TempItemType);
			MouseSlot_->GetInventoryItem()->SetCount(TempCount);
		}
	}

	// 빈 칸이 아닐 때만 아래로 들어간다
	if (ItemType::MAX == ItemType_)
	{
		return;
	}

	// 아이템을 이미 잡은 상태 -> 리턴
	if (true == IsHold_
		|| true == Mouse::MainMouse_->GetMouseSlot()->IsHold_/*dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_*/)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		DragStartSound_ = true;
	}
	// 1) 마우스가 잡은 아이템이 없고, 아이템을 클릭 했을 때->슬롯의 아이템은 현재 아이템으로 지정
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseSlot_->IsHold_ = true;
		MouseSlot_->SetInventoryItem(this);

		IsHold_ = true;
		MouseAnimationRenderer_->Off();  
		MouseRenderer_->On();
		MouseRenderer_->SetTexture("Cursor_Hold.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });

		MouseSlotRenderer_->SetTexture("Item2.png", Index_);
		MouseSlotRenderer_->On();

		// 2) 슬롯의 아이템 = 현재 마우스로 잡은 아이템 (정보를 들고 있는다)

	}

	// 소비 아이템 사용
	if (InventorySlotType::SLOT_POTION == InventorySlotType_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("RightMouse"))
		{
			UsePotion();
		}
	}

}

void InventoryItem::ItemCountFontUpdate()
{
	ItemCountFont_->On();
	ItemCountFont_->SetText(std::to_string(ItemState_.Count_));
}

void InventoryItem::SetItemType(ItemType _ItemType)
{
	ItemType_ = _ItemType;


	if (ItemType_ == ItemType::MAX)
	{
		Renderer_->Off();
		ItemCountFont_->Off();

		return;
	}

	Renderer_->On();
	ItemCountFont_->On();

	switch (ItemType_)
	{
	case ItemType::ITEM_CACTUS:
	{
		Renderer_->SetTexture("Item2.png", 0);
		Index_ = 0;
		MonsterName_ = MONSTERNAME::BabyCactus;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_WHITERABBIT:
	{
		Renderer_->SetTexture("Item2.png", 1);
		Index_ = 1;
		MonsterName_ = MONSTERNAME::WhiteRabbit;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_BROWNRABBIT:
	{
		Renderer_->SetTexture("Item2.png", 2);
		Index_ = 2;
		MonsterName_ = MONSTERNAME::BrownRabbit;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_SCOR:
	{
		Renderer_->SetTexture("Item2.png", 4);
		Index_ = 4;
		MonsterName_ = MONSTERNAME::Scorpion;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_SAND:
	{
		Renderer_->SetTexture("Item2.png", 3);
		Index_ = 3;
		MonsterName_ = MONSTERNAME::Sand;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_SPARKER:
	{
		Renderer_->SetTexture("Item2.png", 6);
		Index_ = 6;
		MonsterName_ = MONSTERNAME::Sparker;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_FREEZER:
	{
		Renderer_->SetTexture("Item2.png", 5);
		Index_ = 5;
		MonsterName_ = MONSTERNAME::Freezer;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	case ItemType::ITEM_HP300:
	{
		Renderer_->SetTexture("Item2.png", 7);
		Index_ = 7;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::HP);
		SetAddHPAmount(4.f);
	}
	break;
	case ItemType::ITEM_HP2000:
	{
		Renderer_->SetTexture("Item2.png", 9);
		Index_ = 9;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::HP);
		SetAddHPAmount(7.f);
	}
	break;
	case ItemType::ITEM_HP4000:
	{
		Renderer_->SetTexture("Item2.png", 12);
		Index_ = 12;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::HP);
		SetAddHPAmount(9.f);
	}
	break;
	case ItemType::ITEM_HP5000:
	{
		Renderer_->SetTexture("Item2.png", 13);
		Index_ = 13;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::HP);
		SetAddHPAmount(11.f);
	}
	break;
	case ItemType::ITEM_MP100:
	{
		Renderer_->SetTexture("Item2.png", 11);
		Index_ = 11;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::MP);
		SetAddMPAmount(2.f);
	}
	break;
	case ItemType::ITEM_MP300:
	{
		Renderer_->SetTexture("Item2.png", 8);
		Index_ = 8;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::MP);
		SetAddMPAmount(4.f);
	}
	break;
	case ItemType::ITEM_MP2000:
	{
		Renderer_->SetTexture("Item2.png", 10);
		Index_ = 10;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::MP);
		SetAddMPAmount(7.f);
	}
	break;
	case ItemType::ITEM_MP4000:
	{
		Renderer_->SetTexture("Item2.png", 14);
		Index_ = 14;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::MP);
		SetAddMPAmount(9.f);
	}
	break;
	case ItemType::ITEM_MP5000:
	{
		Renderer_->SetTexture("Item2.png", 15);
		Index_ = 15;
		InventorySlotType_ = InventorySlotType::SLOT_POTION;
		SetPotionType(PotionType::MP);
		SetAddMPAmount(11.f);
	}
	break;
	case ItemType::ITEM_QUEST:
	{
		Renderer_->SetTexture("Item2.png", 18);
		Index_ = 18;
		MonsterName_ = MONSTERNAME::None;
		InventorySlotType_ = InventorySlotType::SLOT_ETC;
	}
	break;
	}

}

void InventoryItem::UsePotion()
{
	if (ItemType::ITEM_HP300 == ItemType_)
	{
		Player::MainPlayer_->AddHP(GetAddHPAmount());
	}
	else if (ItemType::ITEM_HP2000 == ItemType_)
	{
		Player::MainPlayer_->AddHP(GetAddHPAmount());
	}
	else if (ItemType::ITEM_HP4000 == ItemType_)
	{
		Player::MainPlayer_->AddHP(GetAddHPAmount());
	}
	else if (ItemType::ITEM_HP5000 == ItemType_)
	{
		Player::MainPlayer_->AddHP(GetAddHPAmount());
	}
	else if (ItemType::ITEM_MP100 == ItemType_)
	{
		Player::MainPlayer_->AddMP(GetAddHPAmount());
	}
	else if (ItemType::ITEM_MP300 == ItemType_)
	{
		Player::MainPlayer_->AddMP(GetAddMPAmount());
	}
	else if (ItemType::ITEM_MP2000 == ItemType_)
	{
		Player::MainPlayer_->AddMP(GetAddMPAmount());
	}
	else if (ItemType::ITEM_MP4000 == ItemType_)
	{
		Player::MainPlayer_->AddMP(GetAddMPAmount());
	}
	else if (ItemType::ITEM_MP5000 == ItemType_)
	{
		Player::MainPlayer_->AddMP(GetAddMPAmount());
	}

	std::vector<QuickSlotItem*> CurItem = ContentsUI::MainUI_->GetQuickSlotItemsList();
	for (size_t i = 0; i < CurItem.size(); i++)
	{
		if (ItemType_ == CurItem[i]->GetItemType())
		{
			CurItem[i]->SetCount(CurItem[i]->GetCount() - 1);
			break;
		}
	}
	
	//QuickSlotItem_->SetCount(QuickSlotItem_->GetCount() - 1);

	GameEngineSound::SoundPlayOneShot("ItemUse.mp3");
	SetCount(GetCount() - 1);
	//SetCount(GetCount() - 1);
	//ItemCountFont_->SetText(std::to_string(ItemState_.Count_));

	if (GetCount() <= 0)
	{
		SetItemType(ItemType::MAX);
		ItemCountFont_->Off();
	}
}

