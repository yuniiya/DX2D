#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class GameEngineFontRenderer;
class Item;
class InventoryItem;
class Inventory : public GameEngineActor
{
public:
	static Inventory* MainInventory_;

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

	inline GameEngineFontRenderer* GetMesoFontRenderer()
	{
		return CurMesoFont_;
	}

	std::vector<InventoryItem*> GetInventoryListPotion()
	{
		return InventoryItemsList_Potion;
	}
	std::vector<InventoryItem*> GetInventoryListEtc()
	{
		return InventoryItemsList_Etc;
	}

	void PushItem(Item* _Item);

	bool IsInvenOn;
	bool IsCategoryOn_1;
	bool IsCategoryOn_2;
	bool IsCategoryOn_3;
	bool IsCategoryOn_4;
	bool IsCategoryOn_5;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;

protected:
	void CollisionCheck();
	void InventoryItemCollisionCheck();
	void InventoryOnOffCheck();
	void CategoryOnCheck();

private:
	float4 Position_;
	float4 StartPosition_;

private:
	GameEngineUIRenderer* Inventory_;

	GameEngineUIRenderer* Category_1;
	GameEngineUIRenderer* Category_2;
	GameEngineUIRenderer* Category_3;
	GameEngineUIRenderer* Category_4;
	GameEngineUIRenderer* Category_5;

	GameEngineFontRenderer* CurMesoFont_;

private:
	GameEngineCollision* Collision_;
	GameEngineCollision* HeaderCollision_;
	GameEngineCollision* CategoryCollision_1;
	GameEngineCollision* CategoryCollision_2;
	GameEngineCollision* CategoryCollision_3;
	GameEngineCollision* CategoryCollision_4;
	GameEngineCollision* CategoryCollision_5;

private:
	std::vector<InventoryItem*> InventoryItemsList_Potion;	// 소비
	std::vector<InventoryItem*> InventoryItemsList_Etc;		// 기타
	std::vector<InventoryItem*> InventoryItemsList_None;	// 장비, 캐시 등 안쓰는 인벤토리

private:
	int Capacity_;
	int ItemSlotCount_;

	int PlayerMeso_;
};

