#include "PreCompile.h"
#include "InventoryItem.h"
#include "Inventory.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Mouse.h"
#include "MouseSlot.h"

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
{
	ItemState_.Count_ = 0;
	ItemState_.Price_ = 500;
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

	ItemCountFont_ = CreateComponent<GameEngineFontRenderer>();
	ItemCountFont_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	ItemCountFont_->SetText(std::to_string(ItemState_.Count_));
	ItemCountFont_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	ItemCountFont_->SetSize(17);
	ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	ItemCountFont_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({30.f, 26.f});
	Collision_->ChangeOrder((int)GAMEOBJGROUP::SLOTUI);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 76.f });

	MouseCollision_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseCol();
	MouseRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer();
	MouseAnimationRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseAnimationRenderer();
	MouseSlotRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->GetRenderer();

	SetLevelOverOn();
}

void InventoryItem::Update(float _DeltaTime)
{
	ItemMouseHold();
}

void InventoryItem::ItemMouseHold()
{
	// �κ��丮�� �������� ���� �浹üũ
	if (true == Inventory::MainInventory_->IsInvenOn)
	{
		// �κ��丮�� �������� ���� �ƾ��� ī��Ʈ On
		ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	// �������� ����
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsHold_)
	{
		GameEngineSound::SoundPlayOneShot("DragEnd.mp3");

		dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_ = false;
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
	MouseSlot* Slot = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot();

	// 3) �������� ���� ���¿��� ����
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && 
		Slot->GetInventoryItem() != nullptr)
	{
		// 4) ���� ĭ�� ������ Ÿ���� ���� �������� ������ Ÿ������ ����
		// 5) ���� ������ -> �� ĭ���� ����
		// ���� -> null

		// 6-1) ������ �����۰� �κ��丮 �������� ���� -> ����
		if (GetItemType() == Slot->GetInventoryItem()->GetItemType())
		{
			// ���� ĭ�̴�
			if (SlotIndex_ == Slot->GetInventoryItem()->GetSlotIndex())
			{
				return;
			}
			else // �ٸ� ĭ�̴�
			{
				SetCount(Slot->GetInventoryItem()->GetCount() + GetCount());
				ItemCountFontUpdate();

				// ��ĭ�� ��Ʈ ������ ��ġ ����
				ItemCountFont_->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

				// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
				SetItemType(Slot->GetInventoryItem()->GetItemType());
				Slot->GetInventoryItem()->SetItemType(ItemType::MAX);

				// ���� ��Ʈ ����
				Slot->GetInventoryItem()->SetCount(0);
				Slot->GetInventoryItem()->GetFontRenderer()->Off();
				// ���� ������ null�� �����
				Slot->SetInventoryItem(nullptr);
			}
			
		}	// 6-2) �� ĭ�̴�
		else if (GetItemType() == ItemType::MAX)								
		{
			// �� ĭ�� ������ ī��Ʈ ���� ������ ī��Ʈ�� ����
			SetCount(Slot->GetInventoryItem()->GetCount());
			ItemCountFontUpdate();

			// ��ĭ�� ��Ʈ ������ ��ġ ����
			ItemCountFont_->SetScreenPostion({GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

			// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
			SetItemType(Slot->GetInventoryItem()->GetItemType());
			Slot->GetInventoryItem()->SetItemType(ItemType::MAX);

			// ���� ��Ʈ ����
			Slot->GetInventoryItem()->SetCount(0);
			Slot->GetInventoryItem()->GetFontRenderer()->Off();
			// ���� ������ null�� �����
			Slot->SetInventoryItem(nullptr);
			
			
		} // 6-3) �������� �̹� �ִ�	
		else if (GetItemType() != Slot->GetInventoryItem()->GetItemType() && GetItemType() != ItemType::MAX)	
		{
			//InventoryItem* temp = Slot->GetInventoryItem();

		}
		else
		{

		}
	


		//Slot->GetInventoryItem();
		//Renderer_->SetTexture(Slot->GetInventoryItem()->Renderer_->GetCurTexture());

	}
	// �� ĭ�� �ƴ� ���� �Ʒ��� ����
	if (ItemType::MAX == ItemType_)
	{
		return;
	}

	// �������� �̹� ���� ���� -> ����
	if (true == IsHold_
		|| true == dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_)
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
		Slot->IsHold_ = true;
		IsHold_ = true;
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
		MouseRenderer_->SetTexture("Cursor_Hold.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });

		MouseSlotRenderer_->SetTexture("Item2.png", Index_);
		MouseSlotRenderer_->On();

		// 2) ������ ������ = ���� ���콺�� ���� ������ (������ ��� �ִ´�)
		Slot->SetInventoryItem(this);
		
	/*	if (Slot->GetInventoryItem() != nullptr)
		{
	
		}*/
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
	}
	break;
	case ItemType::ITEM_WHITERABBIT:
	{
		Renderer_->SetTexture("Item2.png", 1);
		Index_ = 1;
	}
	break;
	case ItemType::ITEM_BROWNRABBIT:
	{
		Renderer_->SetTexture("Item2.png", 2);
		Index_ = 2;
	}
	break;
	case ItemType::ITEM_SCOR:
	{
		Renderer_->SetTexture("Item2.png", 4);
		Index_ = 4;
	}
	break;
	case ItemType::ITEM_SAND:
	{
		Renderer_->SetTexture("Item2.png", 3);
		Index_ = 3;
	}
	break;
	case ItemType::ITEM_SPARKER:
	{
		Renderer_->SetTexture("Item2.png", 6);
		Index_ = 6;
	}
	break;
	case ItemType::ITEM_FREEZER:
	{
		Renderer_->SetTexture("Item2.png", 5);
		Index_ = 5;
	}
	break;
	case ItemType::ITEM_HP300:
	{
		Renderer_->SetTexture("Item2.png", 7);
		Index_ = 7;
	}
	break;
	case ItemType::ITEM_MP300:
	{
		Renderer_->SetTexture("Item2.png", 8);
		Index_ = 8;
	}
	break;
	}
}

