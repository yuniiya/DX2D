#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsFont.h"

enum class PotionType
{
	HP,
	MP,

	MAX,
};

struct InventoryItemState
{
	std::string Name_;
	int Count_;
	int Cost_;
};

class GameEngineFontRenderer;
class GameEngineTextureRenderer;
class MouseSlot;
class ContentsFont;
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
	void LevelStartEvent() override;

	void ItemMouseHold();

public:
	inline int GetCount()
	{
		return ItemState_.Count_;
	}

	inline int GetItemCost()
	{
		return ItemState_.Cost_;
	}

	inline std::string GeItemtName()
	{
		return ItemState_.Name_;
	}

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	//inline GameEngineFontRenderer* GetFontRenderer()
	//{
	//	return ItemCountFont_;
	//}

	inline ContentsFont* GetContensFont()
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

	inline float GetAddHPAmount()
	{
		return HPAmount_;
	}

	inline float GetAddMPAmount()
	{
		return MPAmount_;
	}

	inline PotionType GetPotionType()
	{
		return PotionType_;
	}

	inline void SetCount(int _Count)
	{
		ItemState_.Count_ = _Count;

		ItemCountFont_->GetNormalFontRenderer()->SetText(std::to_string(_Count));
	}

	inline void SetItemName(std::string _Name)
	{
		ItemState_.Name_ = _Name;
	}

	inline void SetItemCost(int _Cost)
	{
		ItemState_.Cost_ = _Cost;
	}

	inline void SetSlotIndex(int _SlotIndex)
	{
		SlotIndex_ = _SlotIndex;
	}

	inline void SetMonsterName(MONSTERNAME _MonsterName)
	{
		MonsterName_ = _MonsterName;
	}

	inline void SetInventorySlotType(InventorySlotType _InventorySlotType)
	{
		InventorySlotType_ = _InventorySlotType;
	}

	inline void SetAddHPAmount(float _HPAmount)
	{
		HPAmount_ = _HPAmount;
	}

	inline void SetAddMPAmount(float _MPAmount)
	{
		MPAmount_ = _MPAmount;
	}

	inline void SetPotionType(PotionType _PotionType)
	{
		PotionType_ = _PotionType;
	}

	void SetItemType(ItemType _ItemType);

	bool IsHold_;
	bool IsDoneHolding_;
	bool IsCollideSlot_;
	bool IsSlot_;
	
	void UsePotion();

protected:
	//InventoryItemType InventoryItemType_;
	//PortionItemType PortionItemType_;
	InventorySlotType InventorySlotType_;
	ItemType ItemType_;
	PotionType PotionType_;
	InventoryItemState ItemState_;
	MONSTERNAME MonsterName_;

	bool IsInvenOn_;
	bool DragStartSound_;
	bool DragEndSound_;

	int Index_;
	int SlotIndex_;
	
	float HPAmount_;
	float MPAmount_;
	MouseSlot* MouseSlot_;

//private:
	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* MouseRenderer_;
	GameEngineUIRenderer* MouseAnimationRenderer_;
	GameEngineUIRenderer* MouseSlotRenderer_;
	ContentsFont* ItemCountFont_;

	GameEngineCollision* Collision_;
	GameEngineCollision* MouseCollision_;
};

