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
	// �κ��丮�� �������� ���� ������ ī��Ʈ On
	ItemCountFont_->GetNormalFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
}

void InventoryItem::ItemMouseHold()
{
	//// �κ��丮�� �������� ���� �浹üũ
	//if (true == Inventory::MainInventory_->IsInvenOn)
	//{
	//	// �κ��丮�� �������� ���� ������ ī��Ʈ On
	//	ItemCountFont_->GetNoramlFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
	//}

	// �������� ����
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

	// 3) �������� ���� ���¿��� ����
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && 
		MouseSlot_->GetInventoryItem() != nullptr)
	{
		// 4) ���� ĭ�� ������ Ÿ���� ���� �������� ������ Ÿ������ ����
		// 5) ���� ������ -> �� ĭ���� ���� �� null�� �ʱ�ȭ 
		// 6-1) ������ �����۰� �κ��丮 �������� ����
		if (GetItemType() == MouseSlot_->GetInventoryItem()->GetItemType())
		{
			// ���� ĭ�̴�
			if (SlotIndex_ == MouseSlot_->GetInventoryItem()->GetSlotIndex())
			{
	/*			MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
				MouseSlot_->GetInventoryItem()->SetCount(0);
				MouseSlot_->GetInventoryItem()->GetFontRenderer()->Off();
				MouseSlot_->SetInventoryItem(nullptr);*/
				return;
			}
			else // �ٸ� ĭ�̴�
			{
				SetCount(MouseSlot_->GetInventoryItem()->GetCount() + GetCount());
				//ItemCountFontUpdate();
				// ��ĭ�� ��Ʈ ������ ��ġ ����
				ItemCountFont_->GetNormalFontRenderer()->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });
				// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
				SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());

				MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
				// ���� ��Ʈ ����
				MouseSlot_->GetInventoryItem()->SetCount(0);
				MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->Off();
				// ���� ������ null�� �����
				MouseSlot_->SetInventoryItem(nullptr);
			}
			
		}	// 6-2) �� ĭ�̴�
		else if (GetItemType() == ItemType::MAX)								
		{
			// �� ĭ�� ������ ī��Ʈ ���� ������ ī��Ʈ�� ����
			SetCount(MouseSlot_->GetInventoryItem()->GetCount());
			//ItemCountFontUpdate();
			// ��ĭ�� ��Ʈ ������ ��ġ ����
			ItemCountFont_->GetNormalFontRenderer()->SetScreenPostion({GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });
			// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
			SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());

			MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
			// ���� ��Ʈ ����
			MouseSlot_->GetInventoryItem()->SetCount(0);
			MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->Off();
			// ���� ������ null�� �����
			MouseSlot_->SetInventoryItem(nullptr);
			
			
		} // 6-3) �ٸ� �������� �̹� �ִ�	-> ü����
		else if (GetItemType() != MouseSlot_->GetInventoryItem()->GetItemType() && GetItemType() != ItemType::MAX)
		{
			// 2�� 3�� ��Ƶα�
			ItemType TempItemType = GetItemType();
			int TempCount = GetCount();
			//Slot->SetInventoryItem(Slot->GetInventoryItem());

			// 2�� 1��
			SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());
			SetCount(MouseSlot_->GetInventoryItem()->GetCount());
			
			// 1�� 3����
			MouseSlot_->GetInventoryItem()->SetItemType(TempItemType);
			MouseSlot_->GetInventoryItem()->SetCount(TempCount);
		}
	}

	// �� ĭ�� �ƴ� ���� �Ʒ��� ����
	if (ItemType::MAX == ItemType_)
	{
		return;
	}

	// �������� �̹� ���� ���� -> ����
	if (true == IsHold_
		|| true == Mouse::MainMouse_->GetMouseSlot()->IsHold_/*dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_*/)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		DragStartSound_ = true;
	}
	// 1) ���콺�� ���� �������� ����, �������� Ŭ�� ���� ��->������ �������� ���� ���������� ����
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

		// 2) ������ ������ = ���� ���콺�� ���� ������ (������ ��� �ִ´�)

	}

	// �Һ� ������ ���
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

