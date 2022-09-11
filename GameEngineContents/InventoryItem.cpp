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
	// 인벤토리가 켜져있을 때만 충돌체크
	if (true == Inventory::MainInventory_->IsInvenOn)
	{
		// 인벤토리가 켜져있을 때만 아아템 카운트 On
		ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	}

	// 아이템을 놨다
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

	// 3) 아이템을 잡은 상태에서 놨다
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && 
		Slot->GetInventoryItem() != nullptr)
	{
		// 4) 놓은 칸의 아이템 타입을 슬롯 아이템의 아이템 타입으로 지정
		// 5) 슬롯 렌더러 -> 빈 칸으로 지정
		// 슬롯 -> null

		// 6-1) 슬롯의 아이템과 인벤토리 아이템이 같다 -> 리턴
		if (GetItemType() == Slot->GetInventoryItem()->GetItemType())
		{
			// 같은 칸이다
			if (SlotIndex_ == Slot->GetInventoryItem()->GetSlotIndex())
			{
				return;
			}
			else // 다른 칸이다
			{
				SetCount(Slot->GetInventoryItem()->GetCount() + GetCount());
				ItemCountFontUpdate();

				// 빈칸의 폰트 렌더러 위치 설정
				ItemCountFont_->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

				// 빈 칸의 아이템 타입 슬롯 아이템 타입으로 설정
				SetItemType(Slot->GetInventoryItem()->GetItemType());
				Slot->GetInventoryItem()->SetItemType(ItemType::MAX);

				// 슬롯 폰트 오프
				Slot->GetInventoryItem()->SetCount(0);
				Slot->GetInventoryItem()->GetFontRenderer()->Off();
				// 슬롯 아이템 null로 만들기
				Slot->SetInventoryItem(nullptr);
			}
			
		}	// 6-2) 빈 칸이다
		else if (GetItemType() == ItemType::MAX)								
		{
			// 빈 칸의 아이템 카운트 슬롯 아이템 카운트로 설정
			SetCount(Slot->GetInventoryItem()->GetCount());
			ItemCountFontUpdate();

			// 빈칸의 폰트 렌더러 위치 설정
			ItemCountFont_->SetScreenPostion({GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

			// 빈 칸의 아이템 타입 슬롯 아이템 타입으로 설정
			SetItemType(Slot->GetInventoryItem()->GetItemType());
			Slot->GetInventoryItem()->SetItemType(ItemType::MAX);

			// 슬롯 폰트 오프
			Slot->GetInventoryItem()->SetCount(0);
			Slot->GetInventoryItem()->GetFontRenderer()->Off();
			// 슬롯 아이템 null로 만들기
			Slot->SetInventoryItem(nullptr);
			
			
		} // 6-3) 아이템이 이미 있다	
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
	// 빈 칸이 아닐 때만 아래로 들어간다
	if (ItemType::MAX == ItemType_)
	{
		return;
	}

	// 아이템을 이미 잡은 상태 -> 리턴
	if (true == IsHold_
		|| true == dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_)
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
		Slot->IsHold_ = true;
		IsHold_ = true;
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
		MouseRenderer_->SetTexture("Cursor_Hold.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });

		MouseSlotRenderer_->SetTexture("Item2.png", Index_);
		MouseSlotRenderer_->On();

		// 2) 슬롯의 아이템 = 현재 마우스로 잡은 아이템 (정보를 들고 있는다)
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

