#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
	inline InventoryItemType GetInventoryItemType()
	{
		return InventoryItemType_;
	}

	inline void SetInventoryItemType(InventoryItemType _InventoryItemType)
	{
		InventoryItemType_ = _InventoryItemType;
	}

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	MONSTERNAME MonsterName_;

protected:
	InventoryItemType InventoryItemType_;
	PortionItemType PortionItemType_;

	bool IsInvenOn;


private:
	GameEngineUIRenderer* Renderer_;
	GameEngineCollision* Collision_;
};

