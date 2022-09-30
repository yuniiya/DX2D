#include "PreCompile.h"
#include "Shop.h"

Shop::Shop() 
	: ShopRenderer_(nullptr)
{
}

Shop::~Shop() 
{
}

void Shop::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	ShopRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopRenderer_->SetTexture("ShopUI.png");
	ShopRenderer_->ScaleToTexture();
	//ShopRenderer_->Off();
}

void Shop::Update(float _DeltaTime)
{
}

void Shop::CollisionCheck()
{
}
