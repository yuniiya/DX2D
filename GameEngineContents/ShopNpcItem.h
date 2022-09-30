#pragma once
#include "ShopItem.h"

// Ό³Έν :
class ShopNpcItem : ShopItem
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

