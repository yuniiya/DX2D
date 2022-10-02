#include "PreCompile.h"
#include "ShopNpcItem.h"

ShopNpcItem::ShopNpcItem() 
{
}

ShopNpcItem::~ShopNpcItem() 
{
}

void ShopNpcItem::Start()
{
	SelectShopItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
	SelectShopItemRenderer_->SetTexture("ShopSelect.png");
	SelectShopItemRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	SelectShopItemRenderer_->ScaleToTexture();
	SelectShopItemRenderer_->GetTransform().SetLocalPosition({ 99.f, -60.f,(int)ZOrder::UI });
	SelectShopItemRenderer_->Off();

	ShopItem::Start();
}

void ShopNpcItem::Update(float _DeltaTime)
{
}

void ShopNpcItem::CollisionCheck()
{
	if (nullptr == Collision_)
	{
		return;
	}
	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		IsSelect_ = true;
		SelectShopItemRenderer_->On();
	}
}

void ShopNpcItem::SelectCheck()
{
	if (true == IsSelect_)
	{
		IsSelect_ = false;
		SelectShopItemRenderer_->Off();
	}
}

