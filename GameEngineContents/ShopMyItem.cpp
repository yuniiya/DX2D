#include "PreCompile.h"
#include "ShopMyItem.h"

ShopMyItem::ShopMyItem() 
{
}

ShopMyItem::~ShopMyItem() 
{
}

void ShopMyItem::Start()
{
	SelectMyItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
	SelectMyItemRenderer_->SetTexture("MySelect.png");
	SelectMyItemRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	SelectMyItemRenderer_->ScaleToTexture();
	SelectMyItemRenderer_->GetTransform().SetLocalPosition({ 96.f, -60.f,(int)ZOrder::UI });
	SelectMyItemRenderer_->Off();
	ShopItem::Start();
}

void ShopMyItem::Update(float _DeltaTime)
{
}

void ShopMyItem::CollisionCheck()
{
	if (nullptr == Collision_)
	{
		return;
	}
	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		IsSelect_ = true;
		SelectMyItemRenderer_->On();
	}
}

void ShopMyItem::SelectCheck()
{
	if (true == IsSelect_)
	{
		IsSelect_ = false;
		SelectMyItemRenderer_->Off();
	}
}

