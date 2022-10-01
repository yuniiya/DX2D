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
	SellButtonCol_->GetTransform().SetLocalScale({ 40.f, 10.f });
	SellButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	SellButtonCol_->GetTransform().SetLocalPosition({ SellButton_->GetTransform().GetLocalPosition().x, SellButton_->GetTransform().GetLocalPosition().y });
	//SellButtonCol_->Off();

	CurMesoFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	CurMesoFont_->GetNormalFontRenderer()->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	CurMesoFont_->GetNormalFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetComma();
	CurMesoFont_->GetNormalFontRenderer()->SetScreenPostion({ 800.f, 172.f});
	CurMesoFont_->SetTextSize(13.5f);
	CurMesoFont_->On();
	//CurMesoFont_->GetNoramlFontRenderer()->Off();

	// º“∫Ò√¢
	StartPosition_ = float4({ -51.f, 180.f, (int)ZOrder::UI });
	float4 Pos = StartPosition_;
	for (int i = 0; i < 9; ++i)
	{
		if (i != 0 && 0 == i % 1)
		{
			Pos.y -= 43.f;
		}

		ShopMyItem* ItemActor = GetLevel()->CreateActor<ShopMyItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos });
		ShopMyItemsList_Potion.push_back(ItemActor);
	}

	// ±‚≈∏√¢
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
			Pos.y -= 43.f;
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
	PushShopNpcItem(ItemType::ITEM_MP300);
	PushShopNpcItem(ItemType::ITEM_HP4000);
	PushShopNpcItem(ItemType::ITEM_HP5000);
	PushShopNpcItem(ItemType::ITEM_MP4000);
	PushShopNpcItem(ItemType::ITEM_MP5000);
}

void Shop::Update(float _DeltaTime)
{
	MyShopCategoryCheck();
	CollisionCheck();
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
			IsClick_ = true;
			SellButton_->SetTexture("Shop.BtSell.pressed.0.png");
		}
		else if(true == GameEngineInput::GetInst()->IsFree("LeftMouse") && false == IsClick_)
		{
			SellButton_->SetTexture("Shop.BtSell.mouseOver.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsClick_)
		{
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
			IsClick_ = true;
			BuyButton_->SetTexture("Shop.BtBuy.pressed.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsFree("LeftMouse") && false == IsClick_)
		{
			BuyButton_->SetTexture("Shop.BtBuy.mouseOver.0.png");
		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsClick_)
		{
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
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->On();
			ShopMyItemsList_Potion[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
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
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->On();
			ShopMyItemsList_Etc[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetCollision()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
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
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_None[i]->GetRenderer()->On();
			ShopMyItemsList_None[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
		}

		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetCollision()->Off();
		}
	}
}

void Shop::ShopOff()
{
	CurMesoFont_->GetNormalFontRenderer()->Off();

	if (true == IsCategoryOn_2)
	{
		for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
		{
			if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Potion[i]->GetRenderer()->Off();
			ShopMyItemsList_Potion[i]->GetCollision()->Off();
		}
	}
	else if (true == IsCategoryOn_3)
	{
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
		}
	}
	else
	{
		for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
		{
			if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			ShopMyItemsList_Etc[i]->GetRenderer()->Off();
			ShopMyItemsList_Etc[i]->GetCollision()->Off();
		}
	}

	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		ShopItemsList_[i]->GetRenderer()->Off();
		ShopItemsList_[i]->GetCollision()->Off();
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->Off();
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->Off();
	}

	Off();
}

void Shop::PushShopNpcItem(ItemType _ItemType)
{
	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		if (ShopItemsList_[i]->GetItemType() != ItemType::MAX)
		{
			continue;
		}

		ShopItemsList_[i]->SetItemType(_ItemType);	// ƒ≠ø° æ∆¿Ã≈€¿ª √§øˆ≥÷∞Ì -> forπÆ ∏ÿ√·¥Ÿ
		ShopItemsList_[i]->SetShopItemInfo(_ItemType);
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopItemsList_[i]->GetTransform().GetLocalPosition().x + 745.f,
			-ShopItemsList_[i]->GetTransform().GetLocalPosition().y + 422.f});
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->SetScreenPostion({
			ShopItemsList_[i]->GetTransform().GetLocalPosition().x + 762.f,
			-ShopItemsList_[i]->GetTransform().GetLocalPosition().y + 438.f});

		break;
	}


	//ShopItemsList_[i]->SetCount(ShopItemsList_[i]->GetCount() + 1);	// ∞≥ºˆ¥¬ 1∞≥
//ShopItemsList_[i]->GetContensFont()->GetNoramlFontRenderer()->SetScreenPostion({
//	  ShopItemsList_[i]->GetTransform().GetLocalPosition().x + 700.f
//	, -ShopItemsList_[i]->GetTransform().GetLocalPosition().y + 440.f });
}

void Shop::ShopOn()
{
	for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
	{
		if (ItemType::ITEM_QUEST == Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_Etc[i]->SetItemType(Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType());
	}

	for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
	{

		ShopMyItemsList_Potion[i]->SetItemType(Inventory::MainInventory_->GetInventoryListPotion()[i]->GetItemType());
	}

	CurMesoFont_->GetNormalFontRenderer()->On();

	for (size_t i = 0; i < ShopMyItemsList_Potion.size(); i++)
	{
		// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
		if (ItemType::MAX == ShopMyItemsList_Potion[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_Potion[i]->GetRenderer()->On();
		ShopMyItemsList_Potion[i]->GetCollision()->On();
	}
	for (size_t i = 0; i < ShopMyItemsList_Etc.size(); i++)
	{
		// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
		if (ItemType::MAX == ShopMyItemsList_Etc[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_Etc[i]->GetRenderer()->On();
		ShopMyItemsList_Etc[i]->GetCollision()->On();
	}
	for (size_t i = 0; i < ShopMyItemsList_None.size(); i++)
	{
		// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
		if (ItemType::MAX == ShopMyItemsList_None[i]->GetItemType())
		{
			continue;
		}

		ShopMyItemsList_None[i]->GetRenderer()->On();
		ShopMyItemsList_None[i]->GetCollision()->On();
	}

	for (size_t i = 0; i < ShopItemsList_.size(); i++)
	{
		// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
		if (ItemType::MAX == ShopItemsList_[i]->GetItemType())
		{
			continue;
		}

		ShopItemsList_[i]->GetRenderer()->On();
		ShopItemsList_[i]->GetCollision()->On();
		ShopItemsList_[i]->GetItemNameFont()->GetNormalFontRenderer()->On();
		ShopItemsList_[i]->GetItemCostFont()->GetNormalFontRenderer()->On();
	}

	On();
}

void Shop::AllOff()
{
	IsShopOn_ = false;

	//ShopRenderer_->Off();
	//Category_1->Off();
	//Category_2->Off();
	//Category_3->Off();
	//Category_4->Off();
	//Category_5->Off();
	//ExitButton_->Off();
	//BuyButton_->Off();
	//SellButton_->Off();

	//CategoryCollision_1->Off();
	//CategoryCollision_2->Off();
	//CategoryCollision_3->Off();
	//CategoryCollision_4->Off();
	//CategoryCollision_5->Off();
	//ExitButtonCol_->Off();
	//BuyButtonCol_->Off();
	//SellButtonCol_->Off();
}

void Shop::AllOn()
{
	IsShopOn_ = true;

	//ShopRenderer_->On();
	//Category_1->On();
	//Category_2->On();
	//Category_3->On();
	//Category_4->On();
	//Category_5->On();
	//ExitButton_->On();
	//BuyButton_->On();
	//SellButton_->On();

	//CategoryCollision_1->On();
	//CategoryCollision_2->On();
	//CategoryCollision_3->On();
	//CategoryCollision_4->On();
	//CategoryCollision_5->On();
	//ExitButtonCol_->On();
	//BuyButtonCol_->On();
	//SellButtonCol_->On();

	
}
