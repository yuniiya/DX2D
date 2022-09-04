#include "PreCompile.h"
#include "InventoryItem.h"
#include "Inventory.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Mouse.h"

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
	ItemCountFont_->ChangeCamera(CAMERAORDER::MAINCAMERA);
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

	SetLevelOverOn();
}

void InventoryItem::Update(float _DeltaTime)
{
	// 인벤토리가 켜져있을 때만 충돌체크
	if (true == Inventory::MainInventory_->IsInvenOn)
	{
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
	if (true == IsHold_
		&& true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		GameEngineSound::SoundPlayOneShot("DragEnd.mp3");
		IsHold_ = false;
	}
}

void InventoryItem::CollisionCheck()
{


	if (true == MouseCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SLOTUI, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			DragStartSound_ = true;
		}
	
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			IsHold_ = true;

			MouseAnimationRenderer_->Off();
			MouseRenderer_->On();
			MouseRenderer_->SetTexture("Cursor_Hold.png");
			MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });
		}
		else
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
	}
	break;
	case ItemType::ITEM_WHITERABBIT:
	{
		Renderer_->SetTexture("Item2.png", 1);
	}
	break;
	case ItemType::ITEM_BROWNRABBIT:
	{
		Renderer_->SetTexture("Item2.png", 2);
	}
	break;
	case ItemType::ITEM_SCOR:
	{
		Renderer_->SetTexture("Item2.png", 4);
	}
	break;
	case ItemType::ITEM_SAND:
	{
		Renderer_->SetTexture("Item2.png", 3);
	}
	break;
	case ItemType::ITEM_SPARKER:
	{
		Renderer_->SetTexture("Item2.png", 6);
	}
	break;
	case ItemType::ITEM_FREEZER:
	{
		Renderer_->SetTexture("Item2.png", 5);
	}
	break;
	}
}

