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

	inline int GetShopItemCount()
	{
		return ItemState_.Count_;
	}
	//inline ContentsFont* GetItemCountFont()
	//{
	//	return ItemCountFont_;
	//}

	inline ContentsFont* GetShopItemCountFont()
	{
		return ShopItemCountFont_;
	}

	inline void SetShopItemCount(int _Count)
	{
		ItemState_.Count_ = _Count;

		ShopItemCountFont_->GetNormalFontRenderer()->SetText(std::to_string(_Count));
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
	ContentsFont* ShopItemCountFont_;

};

