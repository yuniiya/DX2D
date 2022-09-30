#include "PreCompile.h"
#include "Shop.h"
#include "Mouse.h"

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
	CategoryCollision_1->GetTransform().SetLocalScale({ 18.f, 15.f });
	CategoryCollision_1->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_1->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_1->Off();

	CategoryCollision_2 = CreateComponent<GameEngineCollision>();
	CategoryCollision_2->SetUIDebugCamera();
	CategoryCollision_2->GetTransform().SetLocalScale({ 18.f, 15.f });
	CategoryCollision_2->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_2->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 45.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_2->Off();

	CategoryCollision_3 = CreateComponent<GameEngineCollision>();
	CategoryCollision_3->SetUIDebugCamera();
	CategoryCollision_3->GetTransform().SetLocalScale({ 18.f, 15.f });
	CategoryCollision_3->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_3->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 90.f, Category_1->GetTransform().GetLocalPosition().y});
	//CategoryCollision_3->Off();

	CategoryCollision_4 = CreateComponent<GameEngineCollision>();
	CategoryCollision_4->SetUIDebugCamera();
	CategoryCollision_4->GetTransform().SetLocalScale({ 18.f, 15.f });
	CategoryCollision_4->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_4->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 135.f, Category_1->GetTransform().GetLocalPosition().y});
	//CategoryCollision_4->Off();

	CategoryCollision_5 = CreateComponent<GameEngineCollision>();
	CategoryCollision_5->SetUIDebugCamera();
	CategoryCollision_5->GetTransform().SetLocalScale({ 18.f, 15.f });
	CategoryCollision_5->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_5->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x - 92.f + 180.f, Category_1->GetTransform().GetLocalPosition().y });
	//CategoryCollision_5->Off();


	ExitButtonCol_ = CreateComponent<GameEngineCollision>();
	ExitButtonCol_->SetUIDebugCamera();
	ExitButtonCol_->GetTransform().SetLocalScale({ 40.f, 15.f });
	ExitButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	ExitButtonCol_->GetTransform().SetLocalPosition({ ExitButton_->GetTransform().GetLocalPosition().x, ExitButton_->GetTransform().GetLocalPosition().y });
	//ExitButtonCol_->Off();

	BuyButtonCol_ = CreateComponent<GameEngineCollision>();
	BuyButtonCol_->SetUIDebugCamera();
	BuyButtonCol_->GetTransform().SetLocalScale({ 40.f, 15.f });
	BuyButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	BuyButtonCol_->GetTransform().SetLocalPosition({ BuyButton_->GetTransform().GetLocalPosition().x, BuyButton_->GetTransform().GetLocalPosition().y });
	//BuyButtonCol_->Off();

	SellButtonCol_ = CreateComponent<GameEngineCollision>();
	SellButtonCol_->SetUIDebugCamera();
	SellButtonCol_->GetTransform().SetLocalScale({ 40.f, 15.f });
	SellButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	SellButtonCol_->GetTransform().SetLocalPosition({ SellButton_->GetTransform().GetLocalPosition().x, SellButton_->GetTransform().GetLocalPosition().y });
	//SellButtonCol_->Off();

}

void Shop::Update(float _DeltaTime)
{
	CollisionCheck();
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
			Off();
			//AllOff();
		}
		else
		{
			ExitButton_->SetTexture("Shop.BtExit.mouseOver.0.png");
		}
	}i
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

void Shop::AllOff()
{
	IsShopOn_ = false;

	ShopRenderer_->Off();
	Category_1->Off();
	Category_2->Off();
	Category_3->Off();
	Category_4->Off();
	Category_5->Off();
	ExitButton_->Off();
	BuyButton_->Off();
	SellButton_->Off();

	CategoryCollision_1->Off();
	CategoryCollision_2->Off();
	CategoryCollision_3->Off();
	CategoryCollision_4->Off();
	CategoryCollision_5->Off();
	ExitButtonCol_->Off();
	BuyButtonCol_->Off();
	SellButtonCol_->Off();
}

void Shop::AllOn()
{
	IsShopOn_ = true;

	ShopRenderer_->On();
	Category_1->On();
	Category_2->On();
	Category_3->On();
	Category_4->On();
	Category_5->On();
	ExitButton_->On();
	BuyButton_->On();
	SellButton_->On();

	CategoryCollision_1->On();
	CategoryCollision_2->On();
	CategoryCollision_3->On();
	CategoryCollision_4->On();
	CategoryCollision_5->On();
	ExitButtonCol_->On();
	BuyButtonCol_->On();
	SellButtonCol_->On();
}
