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
	ShopItem::Start();

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	Renderer_->Off();
}

void ShopNpcItem::Update(float _DeltaTime)
{
}

