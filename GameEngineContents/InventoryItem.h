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
		ItemType_ = _ItemType;
	}

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	//inline void SetInventoryItemType(InventoryItemType _InventoryItemType)
	//{
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

