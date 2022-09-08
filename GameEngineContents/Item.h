#pragma once
#include <GameEngineCore/GameEngineActor.h>

struct ItemState
{
	ItemType ItemType_;
	int Count_;
	int Price_;
};

class GameEngineTextureRenderer;
class Item : public GameEngineActor
{
	friend Inventory;

public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

public:
	virtual void TimeAttackStart();
	virtual void TimeAttackUpdate(GameEngineTextureRenderer* _Renderer);
	virtual void UpDownMove();
	virtual void PickUpItem(GameEngineTextureRenderer* _Renderer);
	virtual void PickUpItemCheck(GameEngineTextureRenderer* _Renderer);

	inline virtual float4 GetItemPosition()
	{
		return GetTransform().GetLocalPosition();
	}

	inline ItemType GetItemType()
	{
		return ItemState_.ItemType_;
	}

	inline InventorySlotType GetSlotType()
	{
		return SlotType_;
	}

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

	inline void SetItemType(ItemType _ItemType)
	{
		ItemState_.ItemType_ = _ItemType;
	}

	inline void SetSlotType(InventorySlotType _SlotType)
	{
		SlotType_ = _SlotType;
	}

	inline void SetMonsterName(MONSTERNAME _MonsterName)
	{
		MonsterName_ = _MonsterName;
	}

	void RendererTypeSetting();
	void PotionRendererTypeSetting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	bool IsCreate;
	bool IsPick;

	float Time_;
	float MoveTime_;
	float PickTime_;
	float4 MoveDir_;

public:
	MONSTERNAME MonsterName_;
	ItemState ItemState_;
	InventorySlotType SlotType_;

private:
	GameEngineTextureRenderer* Renderer_;

//	GameEngineCollision* Collision_;

};

