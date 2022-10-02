#pragma once
#include "ShopItem.h"

// ���� :
class ShopNpcItem : public ShopItem
{
public:
	// constrcuter destructer
	ShopNpcItem();
	~ShopNpcItem();

	// delete Function
	ShopNpcItem(const ShopNpcItem& _Other) = delete;
	ShopNpcItem(ShopNpcItem&& _Other) noexcept = delete;
	ShopNpcItem& operator=(const ShopNpcItem& _Other) = delete;
	ShopNpcItem& operator=(ShopNpcItem&& _Other) noexcept = delete;

public:
	inline GameEngineUIRenderer* GetSelectShopItemRenderer()
	{
		return SelectShopItemRenderer_;
	}

	void CollisionCheck() override;
	void SelectCheck() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* Renderer_;
};

