#pragma once
#include "ShopItem.h"

// Ό³Έν :
class ShopMyItem : public ShopItem
{
public:
	// constrcuter destructer
	ShopMyItem();
	~ShopMyItem();

	// delete Function
	ShopMyItem(const ShopMyItem& _Other) = delete;
	ShopMyItem(ShopMyItem&& _Other) noexcept = delete;
	ShopMyItem& operator=(const ShopMyItem& _Other) = delete;
	ShopMyItem& operator=(ShopMyItem&& _Other) noexcept = delete;

public:
	inline GameEngineUIRenderer* GetSelectMyItemRenderer()
	{
		return SelectMyItemRenderer_;
	}

	void CollisionCheck() override;
	void SelectCheck() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

