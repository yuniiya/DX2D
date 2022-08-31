#include "PreCompile.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	//, MonsterName_(MONSTERNAME::MAX)
	//, PortionItemType_(PortionItemType::MAX)
	, IsInvenOn(false)
	, ItemType_(ItemType::MAX)
{
}

InventoryItem::~InventoryItem() 
{
}

void InventoryItem::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });
	Renderer_ = CreateComponent<GameEngineUIRenderer>();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({28.f, 28.f});
	Collision_->ChangeOrder(GAMEOBJGROUP::UI);
}

void InventoryItem::Update(float _DeltaTime)
{
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

	IsInvenOn = true;	// 인벤토리 켜졌다
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 73.f });

	OnOffCheck();
}

void InventoryItem::OnOffCheck()
{
	// 인벤토리가 켜져있는 상태에서 키를 누른다 -> 렌더러 Off
	if (true == IsInvenOn)	
	{
		if (true == GameEngineInput::GetInst()->IsDown("Inventory"))
		{
			Death();
			IsInvenOn = false; // 꺼진 상태이다
		}
	}

}

