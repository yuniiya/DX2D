#include "PreCompile.h"
#include "ShopItem.h"

ShopItem::ShopItem()
	: ItemNameFont_(nullptr)
	, ItemCostFont_(nullptr)
{
}

ShopItem::~ShopItem() 
{
}

void ShopItem::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	Renderer_->Off();

	ItemCountFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemCountFont_->SetFontType(FontType::Normal);
	//ItemCountFont_->GetNoramlFontRenderer()->SetText(std::to_string(ItemState_.Count_));
	//ItemCountFont_->SetTextSize(17.f);
	//ItemCountFont_->On();

	ItemNameFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemNameFont_->SetFontType(FontType::Normal);
	//ItemNameFont_->GetNoramlFontRenderer()->SetText(ItemState_.Name_);
	//ItemNameFont_->SetTextSize(17.f);
	//ItemNameFont_->On();

	ItemCostFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemCostFont_->SetFontType(FontType::Normal);
	//ItemCostFont_->GetNoramlFontRenderer()->SetText(std::to_string(ItemState_.Cost_));
	//ItemCostFont_->SetTextSize(17.f);
	//ItemCostFont_->On();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({ 147.f, 28.f });
	Collision_->ChangeOrder((int)GAMEOBJGROUP::SLOTUI);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 130.f
		, Renderer_->GetTransform().GetLocalPosition().y - 80.f});
}

void ShopItem::Update(float _DeltaTime)
{
}

