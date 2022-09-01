#pragma once
#include <GameEngineCore/GameEngineActor.h>

//enum class PortionItemType
//{
//	HP,
//	MP,
//
//	MAX,
//};

class GameEngineTextureRenderer;
class InventoryItem : public GameEngineActor
{
public:
	// constrcuter destructer
	InventoryItem();
	~InventoryItem();

	// delete Function
	InventoryItem(const InventoryItem& _Other) = delete;
	InventoryItem(InventoryItem&& _Other) noexcept = delete;
	InventoryItem& operator=(const InventoryItem& _Other) = delete;
	InventoryItem& operator=(InventoryItem&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void OnOffCheck();

public:
	inline void SetItemType(ItemType _ItemType)
	{
		Renderer_->On();

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

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	inline ItemType GetItemType()
	{
		return ItemType_;
	}

	//inline void SetInventoryItemType(InventoryItemType _InventoryItemType)
	//{c
	//	InventoryItemType_ = _InventoryItemType;
	//}

	//MONSTERNAME MonsterName_;

protected:
	//InventoryItemType InventoryItemType_;
	//PortionItemType PortionItemType_;
	ItemType ItemType_;


	bool IsInvenOn;

private:
	GameEngineUIRenderer* Renderer_;
	GameEngineCollision* Collision_;

};

