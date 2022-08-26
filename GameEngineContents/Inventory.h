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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	void CollisionCheck();
	void InventoryOnOffCheck();

private:
	bool IsInvenOn;

	float4 Position_;
	float4 StartPosition_;

private:
	GameEngineTextureRenderer* Inventory_;
	
	GameEngineTextureRenderer* Item_1;
	GameEngineTextureRenderer* Item_2;
	GameEngineTextureRenderer* Item_3;
	GameEngineTextureRenderer* Item_4;
	GameEngineTextureRenderer* Item_5;

private:
	GameEngineCollision* HeaderCollision_;

	GameEngineCollision* Collision_1;
	GameEngineCollision* Collision_2;
	GameEngineCollision* Collision_3;
	GameEngineCollision* Collision_4;
	GameEngineCollision* Collision_5;
	GameEngineCollision* Collision_6;
	GameEngineCollision* Collision_7;
	GameEngineCollision* Collision_8;

private:
	int Capacity_;
	int ItemCount_;
};

