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

void ShopItem::SetShopItemInfo(ItemType _ItemType)
{
	switch (_ItemType)
	{
	case ItemType::ITEM_CACTUS:
	{
		SetItemName("선인장의 줄기");
		SetItemCost(300);
	}
	break;
	case ItemType::ITEM_WHITERABBIT:
	{
		SetItemName("클로버");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_BROWNRABBIT:
	{
		SetItemName("홍당무");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SCOR:
	{
		SetItemName("전갈의 독침");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SAND:
	{
		SetItemName("나무 망치");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SPARKER:
	{
		SetItemName("물개 가죽");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_FREEZER:
	{
		SetItemName("물개의 송곳니");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_HP300:
	{
		SetItemName("하얀 포션");
		SetItemCost(96);
	}
		break;
	case ItemType::ITEM_HP4000:
	{
		SetItemName("살살 녹는 치즈");
		SetItemCost(450);
	}
		break;
	case ItemType::ITEM_HP5000:
	{
		SetItemName("순록의 우유");
		SetItemCost(560);
	}
		break;
	case ItemType::ITEM_MP300:
	{
		SetItemName("마나 엘릭서");
		SetItemCost(186);
	}
		break;
	case ItemType::ITEM_MP4000:
	{
		SetItemName("새벽의 이슬");
		SetItemCost(810);
	}
		break;
	case ItemType::ITEM_MP5000:
	{
		SetItemName("황혼의 이슬");
		SetItemCost(1020);
	}
		break;
	case ItemType::ITEM_QUEST:
		break;
	default:
		break;
	}

	ItemNameFont_->On();
	ItemCostFont_->On();
	ItemNameFont_->GetNormalFontRenderer()->SetText(ItemState_.Name_);
	ItemCostFont_->GetNormalFontRenderer()->SetText(std::to_string(ItemState_.Cost_));
	ItemCostFont_->SetComma();
	ItemCostFont_->GetNormalFontRenderer()->SetText(ItemCostFont_->GetText() + " 메소");
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
	ItemCountFont_->SetTextSize(13.f);
	//ItemCountFont_->On();

	ItemNameFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemNameFont_->SetFontType(FontType::Normal);
	ItemNameFont_->SetTextSize(13.f);
	//ItemNameFont_->On();

	ItemCostFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	ItemCostFont_->SetFontType(FontType::Normal);
	ItemCostFont_->SetTextSize(13.f);
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

