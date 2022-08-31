#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class InventorySlotType
{
	SLOT_PORTION,
	SLOT_ETC,

	MAX,
};

class GameEngineTextureRenderer;
class Item;
class InventoryItem;
class Inventory : public GameEngineActor
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

public:
	inline float4 GetInventoryPosition()
	{
		Position_ = Inventory_->GetTransform().GetLocalPosition();
		return Position_;
	}

	std::vector<Item*> GetItemList_()
	{
		return ItemsList_;
	}

	std::vector<Item*> ItemsList_;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	void CollisionCheck();
	void InventoryOnOffCheck();

private:
	bool IsInvenOn;
	bool HasItem;

	float4 Position_;
	float4 StartPosition_;

private:
	GameEngineUIRenderer* Inventory_;

	GameEngineUIRenderer* Category_1;
	GameEngineUIRenderer* Category_2;
	GameEngineUIRenderer* Category_3;
	GameEngineUIRenderer* Category_4;
	GameEngineUIRenderer* Category_5;

private:
	GameEngineCollision* HeaderCollision_;

	GameEngineCollision* CategoryCollision_1;
	GameEngineCollision* CategoryCollision_2;
	GameEngineCollision* CategoryCollision_3;
	GameEngineCollision* CategoryCollision_4;
	GameEngineCollision* CategoryCollision_5;


	GameEngineCollision* Collision_1;
	GameEngineCollision* Collision_2;
	GameEngineCollision* Collision_3;
	GameEngineCollision* Collision_4;
	GameEngineCollision* Collision_5;
	GameEngineCollision* Collision_6;
	GameEngineCollision* Collision_7;
	GameEngineCollision* Collision_8;

private:
	std::vector<InventoryItem*> InventoryItemsList_;
	Item* Item_;

private:
	int Capacity_;
	int ItemSlotCount_;
};

