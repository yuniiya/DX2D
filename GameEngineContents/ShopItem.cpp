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
		SetItemName("�������� �ٱ�");
		SetItemCost(300);
	}
	break;
	case ItemType::ITEM_WHITERABBIT:
	{
		SetItemName("Ŭ�ι�");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_BROWNRABBIT:
	{
		SetItemName("ȫ�繫");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SCOR:
	{
		SetItemName("������ ��ħ");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SAND:
	{
		SetItemName("���� ��ġ");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_SPARKER:
	{
		SetItemName("���� ����");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_FREEZER:
	{
		SetItemName("������ �۰���");
		SetItemCost(300);
	}
		break;
	case ItemType::ITEM_HP300:
	{
		SetItemName("�Ͼ� ����");
		SetItemCost(96);
	}
		break;
	case ItemType::ITEM_HP4000:
	{
		SetItemName("��� ��� ġ��");
		SetItemCost(450);
	}
		break;
	case ItemType::ITEM_HP5000:
	{
		SetItemName("������ ����");
		SetItemCost(560);
	}
		break;
	case ItemType::ITEM_MP300:
	{
		SetItemName("���� ������");
		SetItemCost(186);
	}
		break;
	case ItemType::ITEM_MP4000:
	{
		SetItemName("������ �̽�");
		SetItemCost(810);
	}
		break;
	case ItemType::ITEM_MP5000:
	{
		SetItemName("Ȳȥ�� �̽�");
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
	ItemCostFont_->GetNormalFontRenderer()->SetText(ItemCostFont_->GetText() + " �޼�");
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

