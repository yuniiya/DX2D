#pragma once
#include <GameEngineCore/GameEngineActor.h>

//enum class PotionItemType
//{
//	HP,
//	MP,
//
//	MAX,
//};

struct InventoryItemState
{
	int Count_;
	int Price_;
};

class GameEngineFontRenderer;
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

public:
	void ItemCountFontUpdate();
	void CollisionCheck();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void ItemMouseHold();

public:
	inline int GetCount()
	{
		return ItemState_.Count_;
	}

	inline int GetPrice()
	{
		return ItemState_.Price_;
	}

	void SetItemType(ItemType _ItemType);

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	inline GameEngineFontRenderer* GetFontRenderer()
	{
		return ItemCountFont_;
	}

	inline GameEngineCollision* GetCollision()
	{
		return Collision_;
	}

	inline ItemType GetItemType()
	{
		return ItemType_;
	}

	inline void SetCount(int _Count)
	{
		ItemState_.Count_ = _Count;
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
	InventoryItemState ItemState_;

	bool IsInvenOn_;
	bool IsHold_;
	bool DragStartSound_;
	bool DragEndSound_;

	int Index_;
private:
	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* MouseRenderer_;
	GameEngineUIRenderer* MouseAnimationRenderer_;
	GameEngineUIRenderer* MouseSlotRenderer_;
	GameEngineFontRenderer* ItemCountFont_;

	GameEngineCollision* Collision_;
	GameEngineCollision* MouseCollision_;
};

