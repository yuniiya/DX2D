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
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	Renderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({28.f, 28.f});
	Collision_->ChangeOrder(GAMEOBJGROUP::UI);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 73.f });
}

void InventoryItem::Update(float _DeltaTime)
{

	IsInvenOn = true;	// 인벤토리 켜졌다

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

