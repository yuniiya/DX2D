#include "PreCompile.h"
#include "InventoryItem.h"
#include "Inventory.h"
#include "GameEngineCore/GameEngineFontRenderer.h"

InventoryItem::InventoryItem() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, IsInvenOn(false)
	, ItemType_(ItemType::MAX)
	, ItemCountFont_(nullptr)
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
	Collision_->GetTransform().SetLocalScale({28.f, 28.f});
	Collision_->ChangeOrder(GAMEOBJGROUP::SLOTUI);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 73.f });

	SetLevelOverOn();
}

void InventoryItem::Update(float _DeltaTime)
{
	//IsInvenOn = true;	// 인벤토리 켜졌다

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

