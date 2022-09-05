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
	Collision_->GetTransform().SetLocalScale({24.f, 26.f});
	Collision_->ChangeOrder(GAMEOBJGROUP::SLOTUI);

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
		ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);

		// 빈 칸이 아니다
		if (ItemType_ != ItemType::MAX)
		{
			CollisionCheck();
		}
	}

	if (true == DragStartSound_)
	{
		GameEngineSound::SoundPlayOneShot("DragStart.mp3");
		DragStartSound_ = false;
	}

	// 마우스로 아이템 집었을 때
	if (true == IsHold_)
	{
		//std::string Name = Renderer_->GetCurTexture()->GetNameCopy();
		dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_ = true;
		MouseSlotRenderer_->SetTexture("Item2.png", Index_);
		MouseSlotRenderer_->On();
		//GetTransform().SetLocalPosition({ MouseRenderer_->GetTransform().GetLocalPosition().x - 78.f
		//	, MouseRenderer_->GetTransform().GetLocalPosition().y + 80.f, (int)ZOrder::UI });

		//Collision_->GetTransform().SetLocalPosition(
		//	{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		//	, Renderer_->GetTransform().GetLocalPosition().y - 76.f });
	}

	if (true == IsHold_ && true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		MouseSlotRenderer_->Off();
		dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_ = false;
		GameEngineSound::SoundPlayOneShot("DragEnd.mp3");
		IsHold_ = false;
	}
}

void InventoryItem::CollisionCheck()
{
	if (true == MouseCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SLOTUI, CollisionType::CT_OBB2D))
	{
		// 아이템 잡았을 때 소리재생
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			DragStartSound_ = true;
		}
	
		// 아이템 잡았다
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			IsHold_ = true;

			MouseAnimationRenderer_->Off();
			MouseRenderer_->On();
			MouseRenderer_->SetTexture("Cursor_Hold.png");
			MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });

			
		}
		else  // 아이템 잡지 않은 상태에서는 애니메이션 재생
		{
			MouseAnimationRenderer_->On();
			MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_Hold");
			MouseRenderer_->Off();
		}
	}
	else
	{
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
	}
}

void InventoryItem::ItemCountFontUpdate()
{
	ItemCountFont_->On();
	ItemCountFont_->SetText(std::to_string(ItemState_.Count_));
}

void InventoryItem::SetItemType(ItemType _ItemType)
{
	Renderer_->On();
	ItemCountFont_->On();

	ItemType_ = _ItemType;

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
	}
}

