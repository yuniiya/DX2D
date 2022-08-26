#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ItemType
{
	MONSTERDROP,
	INVENTORY,

	MAX,
};

enum class InventoryItemType
{
	ITEM_CACTUS,
	ITEM_RABBIT1,
	ITEM_RABBIT2,
	ITEM_SCOR,
	ITEM_SAND,
	ITEM_SPARKER,
	ITEM_FREEZER,

	MAX,
};

enum class PortionItemType
{
	HP,
	MP,

	MAX,
};


class GameEngineTextureRenderer;
class Item : public GameEngineActor
{
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

	void ItemRendererUpdate();

	inline virtual float4 GetItemPosition()
	{
		return GetTransform().GetLocalPosition();
	}

	inline InventoryItemType GetInventoryItemType()
	{
		return InventoryItemType_;
	}

	inline void SetItemType(ItemType _ItemType)
	{
		ItemType_ = _ItemType;
	}

	inline void SetInventoryItemType(InventoryItemType _InventoryItemType)
	{
		InventoryItemType_ = _InventoryItemType;
	}

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	bool IsCreate;
	bool IsPick;

	float Time_;
	float MoveTime_;
	float PickTime_;
	float4 MoveDir_;

public:
	MONSTERNAME MonsterName_;

	ItemType ItemType_;
	InventoryItemType InventoryItemType_;
	PortionItemType PortionItemType_;


private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;


};

