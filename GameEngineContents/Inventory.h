#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
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
	float4 ItemPosition_;

private:
	GameEngineTextureRenderer* Inventory_;
	
	GameEngineTextureRenderer* Item_1;
	GameEngineTextureRenderer* Item_2;
	GameEngineTextureRenderer* Item_3;
	GameEngineTextureRenderer* Item_4;
	GameEngineTextureRenderer* Item_5;
};

