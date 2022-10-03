#include "PreCompile.h"
#include "Shop.h"
#include "Mouse.h"
#include "ShopItem.h"
#include "ShopMyItem.h"
#include "Player.h"
#include "Inventory.h"
#include "Item.h"
#include "ShopNpcItem.h"

Shop::Shop() 
	: ShopRenderer_(nullptr)
	, ExitButton_(nullptr)
	, BuyButton_(nullptr)
	, SellButton_(nullptr)
	, ExitButtonCol_(nullptr)
	, BuyButtonCol_(nullptr)
	, SellButtonCol_(nullptr)
	, Button_(nullptr)
	, IsClick_(false)
	, Category_1(nullptr)
	, Category_2(nullptr)
	, Category_3(nullptr)
	, Category_4(nullptr)
	, Category_5(nullptr)
	, CategoryCollision_1(nullptr)
	, CategoryCollision_2(nullptr)
	, CategoryCollision_3(nullptr)
	, CategoryCollision_4(nullptr)
	, CategoryCollision_5(nullptr)
	, IsCategoryOn_1(false)
	, IsCategoryOn_2(false)
	, IsCategoryOn_3(true)
	, IsCategoryOn_4(false)
	, IsCategoryOn_5(false)
	, IsShopOn_(false)
	, StartPosition_(0.f)
	, CurMesoFont_(nullptr)
	, PlayerMeso_(0)
	, Count_(0)
	, IsSellButtonClick_(false)
	, IsBuyButtonClick_(false)
	, IsBuyNewItem_(false)
{
}

Shop::~Shop() 
{
}

void Shop::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	/// Renderer
	ShopRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopRenderer_->SetTexture("ShopUI.png");
	ShopRenderer_->ScaleToTexture();
	ShopRenderer_->GetTransform().SetLocalPosition({ 0.f, 0.f,(int)ZOrder::UI });
	//ShopRenderer_->Off();

	Category_1 = CreateComponent<GameEngineUIRenderer>();
	Category_1->SetTexture("Category_0-0.png");
	Category_1->ScaleToTexture();
	Category_1->GetTransform().SetLocalPosition({ 116.f, 95.f, (int)ZOrder::UI });
	//Category_1->Off();

	Category_2 = CreateComponent<GameEngineUIRenderer>();
	Category_2->SetTexture("Category_1-0.png");
	Category_2->ScaleToTexture();
	Category_2->GetTransform().SetLocalPosition({ 116.f, 95.f,(int)ZOrder::UI });
	//Category_2->Off();

	Category_3 = CreateComponent<GameEngineUIRenderer>();
	Category_3->SetTexture("Category_2-0.png");
	Category_3->ScaleToTexture();
	Category_3->GetTransform().SetLocalPosition({ 116.f, 95.f,(int)ZOrder::UI });
	//Category_3->Off();

	Category_4 = CreateComponent<GameEngineUIRenderer>();
	Category_4->SetTexture("Category_3-0.png");
	Category_4->ScaleToTexture();
	Category_4->GetTransform().SetLocalPosition({ 116.f, 95.f,(int)ZOrder::UI });
	//Category_4->Off();

	Category_5 = CreateComponent<GameEngineUIRenderer>();
	Category_5->SetTexture("Category_4-0.png");
	Category_5->ScaleToTexture();
	Category_5->GetTransform().SetLocalPosition({ 116.f, 95.f,(int)ZOrder::UI });
	//Category_5->Off();

	ExitButton_ = CreateComponent<GameEngineUIRenderer>();
	ExitButton_->SetTexture("Shop.BtExit.normal.0.png");
	ExitButton_->ScaleToTexture();
	ExitButton_->GetTransform().SetLocalPosition({ -45.f, 145.f,(int)ZOrder::UI });

	BuyButton_ = CreateComponent<GameEngineUIRenderer>();
	BuyButton_->SetTexture("Shop.BtBuy.normal.0.png");
	BuyButton_->ScaleToTexture();
	BuyButton_->GetTransform().SetLocalPosition({ -45.f, 125.f,(int)ZOrder::UI });

	SellButton_ = CreateComponent<GameEngineUIRenderer>();
	SellButton_->SetTexture("Shop.BtSell.normal.0.png");
	SellButton_->ScaleToTexture();
	SellButton_->GetTransform().SetLocalPosition({ 188.f, 122.f,(int)ZOrder::UI });

	/// Collision
	CategoryCollision_1 = CreateComponent<GameEngineCollision>();
	CategoryCollision_1->SetUIDebugCamera();
	CategoryCollision_1->GetTransform().SetLocalScale({ 22.f, 15.f });
	CategoryCollision_1->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_1->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_1->Off();

	CategoryCollision_2 = CreateComponent<GameEngineCollision>();
	CategoryCollision_2->SetUIDebugCamera();
	CategoryCollision_2->GetTransform().SetLocalScale({ 22.f, 15.f });
	CategoryCollision_2->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_2->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 45.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_2->Off();

	CategoryCollision_3 = CreateComponent<GameEngineCollision>();
	CategoryCollision_3->SetUIDebugCamera();
	CategoryCollision_3->GetTransform().SetLocalScale({ 22.f, 15.f });
	CategoryCollision_3->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_3->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 90.f, Category_1->GetTransform().GetLocalPosition().y});
	//CategoryCollision_3->Off();

	CategoryCollision_4 = CreateComponent<GameEngineCollision>();
	CategoryCollision_4->SetUIDebugCamera();
	CategoryCollision_4->GetTransform().SetLocalScale({ 22.f, 15.f });
	CategoryCollision_4->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_4->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 135.f, Category_1->GetTransform().GetLocalPosition().y});
	//CategoryCollision_4->Off();

	CategoryCollision_5 = CreateComponent<GameEngineCollision>();
	CategoryCollision_5->SetUIDebugCamera();
	CategoryCollision_5->GetTransform().SetLocalScale({ 22.f, 15.f });
	CategoryCollision_5->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_5->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 180.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_5->Off();


	ExitButtonCol_ = CreateComponent<GameEngineCollision>();
	ExitButtonCol_->SetUIDebugCamera();
	ExitButtonCol_->GetTransform().SetLocalScale({ 40.f, 7.f });
	ExitButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	ExitButtonCol_->GetTransform().SetLocalPosition({ ExitButton_->GetTransform().GetLocalPosition().x, ExitButton_->GetTransform().GetLocalPosition().y + 5.f});
	//ExitButtonCol_->Off();

	BuyButtonCol_ = CreateComponent<GameEngineCollision>();
	BuyButtonCol_->SetUIDebugCamera();
	BuyButtonCol_->GetTransform().SetLocalScale({ 40.f, 7.f });
	BuyButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	BuyButtonCol_->GetTransform().SetLocalPosition({ BuyButton_->GetTransform().GetLocalPosition().x, BuyButton_->GetTransform().GetLocalPosition().y - 5.f});
	//BuyButtonCol_->Off();

	SellButtonCol_ = CreateComponent<GameEngineCollision>();
	SellButtonCol_->SetUIDebugCamera();
	SellButtonCol_->GetTransform().SetLocalScale({ 40.f, 7.f });
	SellButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	SellButtonCol_->GetTransform().SetLocalPosition({ SellButton_->GetTransform().GetLocalPosition().x, SellButton_->GetTransform().GetLocalPosition().y + 5.f});
	//SellButtonCol_->Off();

	CurMesoFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	CurMesoFont_->GetNormalFontRenderer()->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	CurMesoFont_->GetNormalFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetComma();
	CurMesoFont_->GetNormalFontRenderer()->SetScreenPostion({ 800.f, 172.f});
	CurMesoFont_->SetTextSize(13.5f);
	//CurMesoFont_->GetNoramlFontRenderer()->Off();

	// 소비창
	StartPosition_ = float4({ -51.f, 180.f, (int)ZOrder::UI });
	float4 Pos = StartPosition_;
	for (int i = 0; i < 9; ++i)
	{
		if (i != 0 && 0 == i % 1)
		{
			Pos.y -= 42.f;
		}

		ShopMyItem* ItemActor = GetLevel()->CreateActor<ShopMyItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos });
		ShopMyItemsList_Potion.push_back(ItemActor);
	}

	// 기타창
	Pos = StartPosition_;	for (int i = 0; i < 9; ++i)
	{
		if (i != 0 && 0 == i % 1)
		{
			Pos.y -= 42.f;
		}

		ShopMyItem* ItemActor = GetLevel()->CreateActor<ShopMyItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos });
		ShopMyItemsList_Etc.push_back(ItemActor);
	}

	// None
	Pos = StartPosition_;
	for (int i = 0; i < 9; ++i)
	{
		if (i != 0 && 0 == i % 1)
		{
			Pos.y -= 42.f;
		}

		ShopMyItem* ItemActor = GetLevel()->CreateActor<ShopMyItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos });
		ShopMyItemsList_None.push_back(ItemActor);
	}

	{
		Pos = float4({ -285.f, 180.f, (int)ZOrder::UI });
		for (int i = 0; i < 9; ++i)
		{
			if (i != 0 && 0 == i % 1)
			{
				Pos.y -= 42.f;
			}

			ShopNpcItem* ItemActor = GetLevel()->CreateActor<ShopNpcItem>();
			ItemActor->GetTransform().SetLocalPosition({ Pos });
			ShopItemsList_.push_back(ItemActor);
		}
	}

	PushShopNpcItem(ItemType::ITEM_HP300);
	PushShopNpcItem(ItemType::ITEM_MP100);
	PushShopNpcItem(ItemType::ITEM_MP300);
	PushShopNpcItem(ItemType::ITEM_HP2000);
	PushShopNpcItem(ItemType::ITEM_MP2000);
	PushShopNpcItem(ItemType::ITEM_HP4000);
	PushShopNpcItem(ItemType::ITEM_HP5000);
	PushShopNpcItem(ItemType::ITEM_MP4000);
	PushShopNpcItem(ItemType::ITEM_MP5000);
}

void Shop::Update(float _DeltaTime)
{
	MyShopCategoryCheck();
	CollisionCheck();
	ShopItemCollisionCheck();
	DealItem();
}

void Shop::LevelStartEvent()
{
	CurMesoFont_->GetNormalFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
}

void Shop::CollisionCheck()
{
	ButtonCollisionCheck();
	CategoryCollisionCheck();
	CategoryOnCheck();
}

void Shop::CategoryCollisionCheck()
{
	if (nullptr == Mouse::MainMouse_)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (true == CategoryCollision_1->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			IsCategoryOn_1 = true;

			if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Category_1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Category_2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Category_3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Category_4-0.png");
				IsCategoryOn_5 = false;
			}

		}
		else if (true == CategoryCollision_2->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			IsCategoryOn_2 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Category_0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Category_2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Category_3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Category_4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_3->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			IsCategoryOn_3 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Category_0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Category_1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Category_3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Category_4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_4->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			IsCategoryOn_4 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Category_0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Category_1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Category_2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Category_4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_5->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			IsCategoryOn_5 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Category_0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Category_1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Category_2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Category_3-0.png");
				IsCategoryOn_4 = false;
			}
		}
	}




}

void Shop::ButtonCollisionCheck()
{
	if (true == ExitButtonCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			ExitButton_->SetTexture("Shop.BtExit.pressed.0.png");
			IsShopOn_ = false;
			ShopOff();
		
		}
		else
		{
			ExitButton_->SetTexture("Shop.BtExit.mouseOver.0.png");
		}
	}
	else
	{
		ExitButton_->SetTexture("Shop.BtExit.normal.0.png");
	}


	if (true == SellButtonCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			IsSellButtonClick_ = true;
			IsClick_ = true;
			SellButton_->SetTexture("Shop.BtSell.pressed.0.png");
		}
		else if(true == GameEngineInput::GetInst()->IsFree("LeftMouse") && false == IsClick_)
		{
			SellButton_->SetTexture("Shop.BtSell.mouseOver.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsClick_)
		{
			IsSellButtonClick_ = false;
			IsClick_ = false;
		}
	}
	else
	{
		SellButton_->SetTexture("Shop.BtSell.normal.0.png");
	}


	if (true == BuyButtonCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			IsBuyButtonClick_ = true;
			IsClick_ = true;
			BuyButton_->SetTexture("Shop.BtBuy.pressed.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsFree("LeftMouse") && false == IsClick_)
		{
			BuyButton_->SetTexture("Shop.BtBuy.mouseOver.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsClick_)
		{
			IsBuyButtonClick_ = false;
			IsClick_ = false;
		}
	}
	else
	{
		BuyButton_->SetTexture("Shop.BtBuy.normal.0.png");
	}


}

void Shop::CategoryOnCheck()
{
	//if (false == IsInvenOn)
	//{
	//	return;
	//}

	if (true == IsCategoryOn_1)
	{
		Category_1->SetTexture("Category_0-1.png");
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;
	}
	else if (true == IsCategoryOn_2)
	{
		Category_2->SetTexture("Category_1-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;

	}
	else if (true == IsCategoryOn_3)
	{
		Category_3->SetTexture("Category_2-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;

	}
	else if (true == IsCategoryOn_4)
	{
		Category_4->SetTexture("Category_3-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_5 = false;
	}
	else if (true == IsCategoryOn_5)
	{
		Category_5->SetTexture("Category_4-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;
	}
}

void Shop::MyShopCategoryCheck()
{
	if (true == IsCategoryOn_2)
	{
		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->On();
			ShopMyItemsList_Potion[i]->GetCollision()->On();
			ShopMyItemsList_Potion[i]->GetItemNameFont()->GetNormalFontRenderer()->On();
			ShopMyItemsList_Potion[i]->GetItemCostFont()->GetNormalFontRenderer()->On();
			ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
			ShopMyItemsList_Etc[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_None[i]->GetRenderer()->Off();
			ShopMyItemsList_None[i]->GetCollision()->Off();
		}
	}
	else if (true == IsCategoryOn_3)
	{
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->On();
			ShopMyItemsList_Etc[i]->GetCollision()->On();
			ShopMyItemsList_Etc[i]->GetItemNameFont()->GetNormalFontRenderer()->On();
			ShopMyItemsList_Etc[i]->GetItemCostFont()->GetNormalFontRenderer()->On();
			ShopMyItemsList_Etc[i]->GetShopItemCountFont()->GetNormalFontRenderer()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetCollision()->Off();
			ShopMyItemsList_Potion[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_None[i]->GetRenderer()->Off();
			ShopMyItemsList_None[i]->GetCollision()->Off();
		}

	}
	else
	{
		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_None[i]->GetRenderer()->On();
			ShopMyItemsList_None[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
			ShopMyItemsList_Etc[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			// 빈 칸은 건너뛴다
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetCollision()->Off();
			ShopMyItemsList_Potion[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}
	}
}

void Shop::ShopOff()
{
	for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
	{
		if (ShopMyItemsList_Potion[i]->GetItemType() != ItemType::MAX)
		{
			ShopMyItemsList_Potion[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}
		ShopMyItemsList_Potion[i]->GetCollision()->Off();
		ShopMyItemsList_Potion[i]->GetSelectMyItemRenderer()->Off();
		ShopMyItemsList_Potion[i]->SetItemType(ItemType::MAX);
	}

	for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
	{
		if (ShopMyItemsList_Etc[i]->GetItemType() != ItemType::MAX)
		{
			ShopMyItemsList_Etc[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
		}
		ShopMyItemsList_Etc[i]->GetCollision()->Off();
		ShopMyItemsList_Etc[i]->GetSelectMyItemRenderer()->Off();
		ShopMyItemsList_Etc[i]->SetItemType(ItemType::MAX);
	}

	for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
	{
		ShopMyItemsList_None[i]->GetCollision()->Off();
		ShopMyItemsList_None[i]->GetSelectMyItemRenderer()->Off();
	}

	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		// 빈 칸은 건너뛴다
		if (ItemType::MAX == ShopItemsList_[i]->GetItemType())
		{
			continue;
		}
		ShopItemsList_[i]->GetSelectShopItemRenderer()->Off();
		ShopItemsList_[i]->GetRenderer()->Off();
		ShopItemsList_[i]->GetCollision()->Off();
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();

	}

	CurMesoFont_->GetNormalFontRenderer()->Off();
	Off();
}

void Shop::ShopItemCollisionCheck()
{
	// 소비창
	if (true == IsCategoryOn_2)
	{
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			ShopMyItemsList_Etc[i]->SelectCheck();
		}
		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			ShopMyItemsList_None[i]->SelectCheck();
		}

		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			if (true == ShopMyItemsList_Potion[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D)
				 && true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
			{
				for (size_t j = 0; j < ShopItemsList_.size(); j++)
				{
					ShopMyItemsList_Potion[j]->SelectCheck();
				}

				ShopMyItemsList_Potion[i]->CollisionCheck();

				break;
			}
		}
	}
	// 기타창
	else if (true == IsCategoryOn_3)
	{
		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			ShopMyItemsList_Potion[i]->SelectCheck();
		}
		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			ShopMyItemsList_None[i]->SelectCheck();
		}

		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			if (true == ShopMyItemsList_Etc[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D)
				&& true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
			{
				for (size_t j = 0; j < ShopMyItemsList_Etc.size(); j++)
				{
					ShopMyItemsList_Etc[j]->SelectCheck();
				}

				ShopMyItemsList_Etc[i]->CollisionCheck();

				break;
			}

		}
	}
	else
	{
		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			ShopMyItemsList_Potion[i]->SelectCheck();
		}
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			ShopMyItemsList_Etc[i]->SelectCheck();
		}
		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			ShopMyItemsList_None[i]->SelectCheck();
		}
	}


	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		if (true == ShopItemsList_[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D)
			&& true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			for (size_t j = 0; j < ShopItemsList_.size(); j++)
			{
				ShopItemsList_[j]->SelectCheck();
			}

			ShopItemsList_[i]->CollisionCheck();

			break;
		}

	}
}

void Shop::DealItem()
{
	BuyItem();
	SellItem();
	MyItemListUpdate();
}

void Shop::BuyItem()
{
	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		if (true == ShopItemsList_[i]->IsSelect_)
		{
			if (true == IsBuyButtonClick_)
			{
				// 1) 메소 차감
				if (Player::MainPlayer_->GetPlayerMeso() < ShopItemsList_[i]->GetItemCost())
				{
					return;
				}

				Player::MainPlayer_->UsePlayerMeso(ShopItemsList_[i]->GetItemCost());
				PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
				CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
				CurMesoFont_->SetComma();
				IsBuyButtonClick_ = false;

				// 2) 인벤토리에 구매한 아이템 추가
				Item* ItemActor = GetLevel()->CreateActor<Item>(GAMEOBJGROUP::ITEM);
				ItemActor->SetItemType(ShopItemsList_[i]->GetItemType());
				ItemActor->MonsterName_ = MONSTERNAME::None;
				ItemActor->PotionRendererTypeSetting();
				Inventory::MainInventory_->PushItem(ItemActor);

				// 소비창이 이미 켜져 있으면 바로 업데이트
				if (true == IsCategoryOn_2)
				{
					// 3) 상점에 구매한 아이템 새로 업데이트 -> 문제 : 소비창이 아닌 다른 창 켜져있으면 렌더러 한 번 깜빡임
					for (size_t j = 0; j < ShopMyItemsList_Potion.size(); j++)
					{
						if (ItemType::MAX == Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType())
						{
							continue;
						}

						ShopMyItemsList_Potion[Count_]->SetItemType(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType());
						ShopMyItemsList_Potion[Count_]->SetShopItemInfo(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType());
						ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
							ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
							-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 422.f });
						ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
							ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
							-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 438.f });

						ShopMyItemsList_Potion[Count_]->SetShopItemCount(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetCount());
						ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetText(std::to_string(ShopMyItemsList_Potion[Count_]->GetCount()));
						ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetScreenPostion({
							ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 701.f,
							-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 439.f });

						ShopMyItemsList_Potion[Count_]->GetRenderer()->On();
						ShopMyItemsList_Potion[Count_]->GetCollision()->On();
						ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->On();
						ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->On();
						//	ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->On();

						++Count_;
					}

					Count_ = 0;

				}
				else // 소비창 외 다른 창이 켜져 있을 경우 -> MyItemListUpdate();
				{
					IsBuyNewItem_ = true;
				}

			}

		}
	}
}

void Shop::SellItem()
{
	// 소비 아이템
	if (true == IsCategoryOn_2)
	{
		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			if (true == ShopMyItemsList_Potion[i]->IsSelect_)
			{
				if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
				{
					ShopMyItemsList_Potion[i]->IsSelect_ = false;
					return;
				}

				if (true == IsSellButtonClick_)
				{
					// 1) 메소 증가
					Player::MainPlayer_->AddPlayerMeso(ShopMyItemsList_Potion[i]->GetItemCost());
					PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
					CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
					CurMesoFont_->SetComma();
					IsSellButtonClick_ = false;

					// 2) 판매한 아이템 인벤토리에서 제외
					for (size_t j = 0; j < Inventory::MainInventory_->GetInventoryListPotion().size(); j++)
					{
						// 판매하는 아이템 타입과 같은 아이템이 있는지 검사
						if (ShopMyItemsList_Potion[i]->GetItemType() == Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType())
						{
							Inventory::MainInventory_->GetInventoryListPotion()[j]->SetCount(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetCount() - 1);

							break;
						}
					}
		
					// 3) 판매한 아이템 내 상점에서 제외
					ShopMyItemsList_Potion[i]->SetShopItemCount(ShopMyItemsList_Potion[i]->GetCount() - 1);
	

					//// 4) 판매한 아이템 위쪽에 빈 칸이 있는지 검사
					//for (size_t j = i - 1; j < ShopMyItemsList_Potion.size(); j++)
					//{
					//	// 이전 아이템이 빈 칸이 아니i다
					//	if (ItemType::MAX != ShopMyItemsList_Potion[j]->GetItemType())
					//	{
					//		continue;
					//	}

					//	// 이전 아이템이 빈 칸이다 -> j(이전 아이템)을 i로 교체, 
					//	ShopMyItemsList_Potion[Count_]->SetItemType(ShopMyItemsList_Potion[j]->GetItemType());
					//	ShopMyItemsList_Potion[Count_]->SetShopItemInfo(ShopMyItemsList_Potion[j]->GetItemType());
					//	// 이름
					//	ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
					//		ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
					//		-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 422.f });
					//	// 가격
					//	ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
					//		ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
					//		-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 438.f });
					//	// 개수
					//	ShopMyItemsList_Potion[Count_]->SetShopItemCount(ShopMyItemsList_Potion[j]->GetCount());
					//	ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetText(std::to_string(ShopMyItemsList_Potion[Count_]->GetCount()));
					//	ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetScreenPostion({
					//		ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 701.f,
					//		-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 439.f });

					//	ShopMyItemsList_Potion[Count_]->GetRenderer()->On();
					//	ShopMyItemsList_Potion[Count_]->GetCollision()->On();
					//	ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->On();
					//	ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->On();
					//	//	ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->On();

					//	++Count_;
					//}

					//Count_ = 0;


					if (ShopMyItemsList_Potion[i]->GetCount() <= 0)
					{
						ShopMyItemsList_Potion[i]->SetItemType(ItemType::MAX);
						ShopMyItemsList_Potion[i]->GetCollision()->Off();
						ShopMyItemsList_Potion[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Potion[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Potion[i]->GetSelectMyItemRenderer()->Off();

						break;
					}
				}
			}
		}
	}	// 기타 아이템
	else if (true == IsCategoryOn_3)
	{
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			if (true == ShopMyItemsList_Etc[i]->IsSelect_)
			{
				if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
				{
					ShopMyItemsList_Etc[i]->IsSelect_ = false;
					return;
				}

				if (true == IsSellButtonClick_)
				{
					// 1) 메소 증가
					Player::MainPlayer_->AddPlayerMeso(ShopMyItemsList_Etc[i]->GetItemCost());
					PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
					CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
					CurMesoFont_->SetComma();
					IsSellButtonClick_ = false;

					// 2) 판매한 아이템 인벤토리에서 제외
					for (size_t j = 0; j < Inventory::MainInventory_->GetInventoryListEtc().size(); j++)
					{
						// 판매하는 아이템 타입과 같은 아이템이 있는지 검사
						if (ShopMyItemsList_Etc[i]->GetItemType() == Inventory::MainInventory_->GetInventoryListEtc()[j]->GetItemType())
						{
							Inventory::MainInventory_->GetInventoryListEtc()[j]->SetCount(Inventory::MainInventory_->GetInventoryListEtc()[j]->GetCount() - 1);

							break;
						}
					}
					// 3) 판매한 아이템 내 상점에서 제외
					ShopMyItemsList_Etc[i]->SetShopItemCount(ShopMyItemsList_Etc[i]->GetCount() - 1);

					if (ShopMyItemsList_Etc[i]->GetCount() <= 0)
					{
						ShopMyItemsList_Etc[i]->SetItemType(ItemType::MAX);
						ShopMyItemsList_Etc[i]->GetCollision()->Off();
						ShopMyItemsList_Etc[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Etc[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Etc[i]->GetShopItemCountFont()->GetNormalFontRenderer()->Off();
						ShopMyItemsList_Etc[i]->GetSelectMyItemRenderer()->Off();

						break;
					}

				}
			}

		}
	}

}

void Shop::MyItemListUpdate()
{
	// 다른 창이 켜져있을 때 아이템을 구매한 상황 저장 
	if (false == IsBuyNewItem_)
	{
		return;
	}

	if (true == IsCategoryOn_2)
	{
		for (size_t j = 0; j < ShopMyItemsList_Potion.size(); j++)
		{
			if (ItemType::MAX == Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[Count_]->SetItemType(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType());
			ShopMyItemsList_Potion[Count_]->SetShopItemInfo(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetItemType());
			ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
				ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
				-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 422.f });
			ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
				ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
				-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 438.f });

			ShopMyItemsList_Potion[Count_]->SetShopItemCount(Inventory::MainInventory_->GetInventoryListPotion()[j]->GetCount());
			ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetText(std::to_string(ShopMyItemsList_Potion[Count_]->GetCount()));
			ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetScreenPostion({
				ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 701.f,
				-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 439.f });

			ShopMyItemsList_Potion[Count_]->GetRenderer()->On();
			ShopMyItemsList_Potion[Count_]->GetCollision()->On();
			ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->On();
			ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->On();
			//	ShopMyItemsList_Potion[i]->GetShopItemCountFont()->GetNormalFontRenderer()->On();

			++Count_;
		}

		Count_ = 0;
		IsBuyNewItem_ = false;
	}
}

void Shop::ShopOn()
{
	for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
	{
		if (ItemType::ITEM_QUEST == Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType()
			|| ItemType::MAX == Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_Etc[Count_]->SetItemType(Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType());
		ShopMyItemsList_Etc[Count_]->SetShopItemInfo(Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType());
		ShopMyItemsList_Etc[Count_]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().y + 422.f });
		ShopMyItemsList_Etc[Count_]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().y + 438.f });

		ShopMyItemsList_Etc[Count_]->SetShopItemCount(Inventory::MainInventory_->GetInventoryListEtc()[i]->GetCount());
		ShopMyItemsList_Etc[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetText(std::to_string(ShopMyItemsList_Etc[Count_]->GetCount()));
		ShopMyItemsList_Etc[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().x + 701.f,
			-ShopMyItemsList_Etc[Count_]->GetTransform().GetLocalPosition().y + 439.f });



		ShopMyItemsList_Etc[Count_]->GetRenderer()->On();
		ShopMyItemsList_Etc[Count_]->GetCollision()->On();
		ShopMyItemsList_Etc[Count_]->GetItemNameFont()->GetNormalFontRenderer()->On();
		ShopMyItemsList_Etc[Count_]->GetItemCostFont()->GetNormalFontRenderer()->On();

		++Count_;

	}

	Count_ = 0;

	for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
	{
		if (ItemType::MAX == Inventory::MainInventory_->GetInventoryListPotion()[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_Potion[Count_]->SetItemType(Inventory::MainInventory_->GetInventoryListPotion()[i]->GetItemType());
		ShopMyItemsList_Potion[Count_]->SetShopItemInfo(Inventory::MainInventory_->GetInventoryListPotion()[i]->GetItemType());
		ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 422.f });
		ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 438.f });

		ShopMyItemsList_Potion[Count_]->SetShopItemCount(Inventory::MainInventory_->GetInventoryListPotion()[i]->GetCount());
		ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetText(std::to_string(ShopMyItemsList_Potion[Count_]->GetCount()));
		ShopMyItemsList_Potion[Count_]->GetShopItemCountFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().x + 701.f,
			-ShopMyItemsList_Potion[Count_]->GetTransform().GetLocalPosition().y + 439.f });

		ShopMyItemsList_Potion[Count_]->GetRenderer()->On();
		ShopMyItemsList_Potion[Count_]->GetCollision()->On();
		ShopMyItemsList_Potion[Count_]->GetItemNameFont()->GetNormalFontRenderer()->On();
		ShopMyItemsList_Potion[Count_]->GetItemCostFont()->GetNormalFontRenderer()->On();

		++Count_;
	}

	Count_ = 0;

	for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
	{
		// 빈 칸은 건너뛴다
		if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_None[i]->GetRenderer()->On();
	}

	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		// 빈 칸은 건너뛴다
		if (ItemType::MAX == ShopItemsList_[i]->GetItemType())
		{
			continue;
		}

		ShopItemsList_[i]->GetRenderer()->On();
		ShopItemsList_[i]->GetCollision()->On();
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->On();
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->On();
	}

	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetComma();
	CurMesoFont_->GetNormalFontRenderer()->On();
	CurMesoFont_->On();
	On();

}


void Shop::PushShopNpcItem(ItemType _ItemType)
{
	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		if (ShopItemsList_[i]->GetItemType() != ItemType::MAX)
		{
			continue;
		}

		ShopItemsList_[i]->SetItemType(_ItemType);	// 칸에 아이템을 채워넣고 -> for문 멈춘다
		ShopItemsList_[i]->SetShopItemInfo(_ItemType);
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopItemsList_[i]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopItemsList_[i]->GetTransform().GetLocalPosition().y + 422.f });
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopItemsList_[i]->GetTransform().GetLocalPosition().x + 762.f,
			-ShopItemsList_[i]->GetTransform().GetLocalPosition().y + 438.f });
		ShopItemsList_[i]->GetRenderer()->Off();
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();


		break;
	}
}

