#pragma once
#include <GameEngineCore/GameEngineActor.h>
//#include "Inventory.h"

// 설명 :
class GameEngineTextureRenderer;
class ContentsFont;
class ShopNpcItem;
class ShopMyItem;
class ShopItem;
class Shop : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop();
	~Shop();

	// delete Function
	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;

public:
	inline GameEngineUIRenderer* GetShopRenderer()
	{
		return ShopRenderer_;
	}

	void PushShopNpcItem(ItemType _ItemType);

	void ShopOn();
	bool IsShopOn_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

protected:
	void CollisionCheck();
	void CategoryCollisionCheck();
	void ButtonCollisionCheck();
	void CategoryOnCheck();
	void MyShopCategoryCheck();
	void ShopOff();
	void ShopItemCollisionCheck();
	void DealItem();
	void BuyItem();
	void SellItem();

protected:
	// 플레이어 아이템 목록
	std::vector<ShopMyItem*> ShopMyItemsList_Potion;	// 소비
	std::vector<ShopMyItem*> ShopMyItemsList_Etc;		// 기타
	std::vector<ShopMyItem*> ShopMyItemsList_None;		// 장비, 캐시 등 안쓰는 인벤토리

	// 판매하는 아이템 목록
	std::vector<ShopNpcItem*> ShopItemsList_;				

private:
	GameEngineUIRenderer* ShopRenderer_;
	GameEngineUIRenderer* Button_;
	GameEngineUIRenderer* ExitButton_;
	GameEngineUIRenderer* BuyButton_;
	GameEngineUIRenderer* SellButton_;

	GameEngineUIRenderer* Category_1;
	GameEngineUIRenderer* Category_2;
	GameEngineUIRenderer* Category_3;
	GameEngineUIRenderer* Category_4;
	GameEngineUIRenderer* Category_5;

	GameEngineCollision* ExitButtonCol_;
	GameEngineCollision* BuyButtonCol_;
	GameEngineCollision* SellButtonCol_;

	GameEngineCollision* CategoryCollision_1;
	GameEngineCollision* CategoryCollision_2;
	GameEngineCollision* CategoryCollision_3;
	GameEngineCollision* CategoryCollision_4;
	GameEngineCollision* CategoryCollision_5;

	ContentsFont* CurMesoFont_;

private:
	bool IsCategoryOn_1;
	bool IsCategoryOn_2;
	bool IsCategoryOn_3;
	bool IsCategoryOn_4;
	bool IsCategoryOn_5;

	bool IsClick_;
	bool IsSellButtonClick_;
	bool IsBuyButtonClick_;

	float4 StartPosition_;
	int PlayerMeso_;
	int Count_;
};

