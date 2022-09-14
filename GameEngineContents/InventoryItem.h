#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

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
class MouseSlot;
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
	virtual void CollisionCheck();

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

	inline GameEngineUIRenderer* GetMouseSlotRenderer()
	{
		return MouseSlotRenderer_;
	}

	inline int GetIndex()
	{
		return Index_;
	}

	inline int GetSlotIndex()
	{
		return SlotIndex_;
	}

	inline MONSTERNAME GetMonsterName()
	{
		return MonsterName_;
	}

	inline InventorySlotType GetInventorySlotType()
	{
		return InventorySlotType_;
	}

	inline void SetCount(int _Count)
	{
		ItemState_.Count_ = _Count;

		ItemCountFont_->SetText(std::to_string(_Count));
	}

	inline void SetSlotIndex(int _SlotIndex)
	{
		SlotIndex_ = _SlotIndex;
	}

	void SetItemType(ItemType _ItemType);

	bool IsHold_;
	bool IsDoneHolding_;
	bool IsCollideSlot_;
	bool IsSlot_;
	bool IsSlotItemCountChange_;
	
	void UsePotion();

protected:
	//InventoryItemType InventoryItemType_;
	//PortionItemType PortionItemType_;
	InventorySlotType InventorySlotType_;
	ItemType ItemType_;
	InventoryItemState ItemState_;
	MONSTERNAME MonsterName_;

	bool IsInvenOn_;
	bool DragStartSound_;
	bool DragEndSound_;

	int Index_;
	int SlotIndex_;

	MouseSlot* MouseSlot_;
	QuickSlotItem* QuickSlotItem_;

//private:
	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* MouseRenderer_;
	GameEngineUIRenderer* MouseAnimationRenderer_;
	GameEngineUIRenderer* MouseSlotRenderer_;
	GameEngineFontRenderer* ItemCountFont_;

	GameEngineCollision* Collision_;
	GameEngineCollision* MouseCollision_;
};

