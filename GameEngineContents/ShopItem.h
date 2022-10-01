#pragma once
#include "InventoryItem.h"

// Ό³Έν :
class ShopItem : public InventoryItem
{
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

public:
	inline ContentsFont* GetItemNameFont()
	{
		return ItemNameFont_;
	}

	inline ContentsFont* GetItemCostFont()
	{
		return ItemCostFont_;
	}

	//inline void SetItemNameFont()
	//{

	//}

	//inline void SetItemCostFont(ContentsFont* _ItemCostFont)
	//{
	//	ItemCostFont_ = _ItemCostFont;
	//}

	void SetShopItemInfo(ItemType _ItemType);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	ContentsFont* ItemNameFont_;
	ContentsFont* ItemCostFont_;

};

