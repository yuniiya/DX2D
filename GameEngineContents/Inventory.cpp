#include "PreCompile.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "Item.h"
#include "GameEngineCore/GameEngineFontRenderer.h"

Inventory* Inventory::MainInventory_ = nullptr;

Inventory::Inventory() 
	: Inventory_(nullptr)
	, IsInvenOn(false)
	, HeaderCollision_(nullptr)
	, StartPosition_(0.f)
	, Position_(0.f)
	, Capacity_(24)
	, ItemSlotCount_(0)
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
	, IsCategoryOn_2(true)
	, IsCategoryOn_3(false)
	, IsCategoryOn_4(false)
	, IsCategoryOn_5(false)
	, CurMesoFont_(nullptr)
	, PlayerMeso_(Player::MainPlayer_->GetPlayerMeso())
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	// Rednerer //
	Inventory_ = CreateComponent<GameEngineUIRenderer>();
	Inventory_->SetTexture("Inventory.png");
	Inventory_->SetPivot(PIVOTMODE::LEFTTOP);
	Inventory_->ScaleToTexture();

	Inventory_->GetTransform().SetLocalPosition({ -390.f, 320.f, (int)ZOrder::UI });
	Inventory_->Off();

	Category_1 = CreateComponent<GameEngineUIRenderer>();
	Category_1->SetTexture("Bt_Inven0-0.png");
	Category_1->GetTransform().SetLocalScale({179.f * 1.1f, 17.f});
	Category_1->SetPivot(PIVOTMODE::LEFTTOP);
	Category_1->GetTransform().SetLocalPosition({ -375.f, 293.f, (int)ZOrder::UI});
	Category_1->Off();

	Category_2 = CreateComponent<GameEngineUIRenderer>();
	Category_2->SetTexture("Bt_Inven1-0.png");
	Category_2->GetTransform().SetLocalScale({ 179.f * 1.1f, 17.f});
	Category_2->SetPivot(PIVOTMODE::LEFTTOP);
	Category_2->GetTransform().SetLocalPosition({ -375.f, 293.f,(int)ZOrder::UI });
	Category_2->Off();

	Category_3 = CreateComponent<GameEngineUIRenderer>();
	Category_3->SetTexture("Bt_Inven2-0.png");
	Category_3->GetTransform().SetLocalScale({ 179.f * 1.1f, 17.f});
	Category_3->SetPivot(PIVOTMODE::LEFTTOP);
	Category_3->GetTransform().SetLocalPosition({ -375.f, 293.f,(int)ZOrder::UI });
	Category_3->Off();

	Category_4 = CreateComponent<GameEngineUIRenderer>();
	Category_4->SetTexture("Bt_Inven3-0.png");
	Category_4->GetTransform().SetLocalScale({ 179.f * 1.1f, 17.f });
	Category_4->SetPivot(PIVOTMODE::LEFTTOP);
	Category_4->GetTransform().SetLocalPosition({ -375.f, 293.f,(int)ZOrder::UI });
	Category_4->Off();

	Category_5 = CreateComponent<GameEngineUIRenderer>();
	Category_5->SetTexture("Bt_Inven4-0.png");
	Category_5->GetTransform().SetLocalScale({ 179.f * 1.1f, 17.f });
	Category_5->SetPivot(PIVOTMODE::LEFTTOP);
	Category_5->GetTransform().SetLocalPosition({ -375.f, 293.f,(int)ZOrder::UI });
	Category_5->Off();

	CurMesoFont_ = CreateComponent<GameEngineFontRenderer>();
	CurMesoFont_->SetRenderingOrder((int)ZOrder::FONT);
	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	CurMesoFont_->SetSize(13.5f);
	CurMesoFont_->SetScreenPostion({
		  -(Inventory_->GetTransform().GetLocalPosition().x + 30.f)
		, Inventory_->GetTransform().GetLocalPosition().y + 25.f});
	CurMesoFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	CurMesoFont_->Off();

	// Collision //
	CategoryCollision_1 = CreateComponent<GameEngineCollision>();
	CategoryCollision_1->SetUIDebugCamera();
	CategoryCollision_1->GetTransform().SetLocalScale({ 10.f, 15.f });
	CategoryCollision_1->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_1->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x + 17.f, Category_1->GetTransform().GetLocalPosition().y - 10.f});
	CategoryCollision_1->Off();

	CategoryCollision_2 = CreateComponent<GameEngineCollision>();
	CategoryCollision_2->SetUIDebugCamera();
	CategoryCollision_2->GetTransform().SetLocalScale({ 10.f, 15.f });
	CategoryCollision_2->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_2->GetTransform().SetLocalPosition({ (Category_1->GetTransform().GetLocalPosition().x + 17.f) + 32.f, Category_1->GetTransform().GetLocalPosition().y - 10.f });
	CategoryCollision_2->Off();

	CategoryCollision_3 = CreateComponent<GameEngineCollision>();
	CategoryCollision_3->SetUIDebugCamera();
	CategoryCollision_3->GetTransform().SetLocalScale({ 10.f, 15.f });
	CategoryCollision_3->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_3->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x + 17.f + 65.f, Category_1->GetTransform().GetLocalPosition().y - 10.f });
	CategoryCollision_3->Off();

	CategoryCollision_4 = CreateComponent<GameEngineCollision>();
	CategoryCollision_4->SetUIDebugCamera();
	CategoryCollision_4->GetTransform().SetLocalScale({ 10.f, 15.f });
	CategoryCollision_4->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_4->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x + 17.f + 97.f, Category_1->GetTransform().GetLocalPosition().y - 10.f });
	CategoryCollision_4->Off();

	CategoryCollision_5 = CreateComponent<GameEngineCollision>();
	CategoryCollision_5->SetUIDebugCamera();
	CategoryCollision_5->GetTransform().SetLocalScale({ 10.f, 15.f });
	CategoryCollision_5->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_5->GetTransform().SetLocalPosition({ Category_1->GetTransform().GetLocalPosition().x + 17.f + 130.f, Category_1->GetTransform().GetLocalPosition().y - 10.f });
	CategoryCollision_5->Off();

	HeaderCollision_ = CreateComponent<GameEngineCollision>();
	HeaderCollision_->SetUIDebugCamera();
	HeaderCollision_->GetTransform().SetLocalScale({ 190.f, 15.f });
	HeaderCollision_->ChangeOrder(GAMEOBJGROUP::SLOTUI);
	HeaderCollision_->GetTransform().SetLocalPosition({ Inventory_->GetTransform().GetLocalPosition().x + 95.f, Inventory_->GetTransform().GetLocalPosition().y - 11.f});
	HeaderCollision_->Off();

//	IsInvenOn = true;
	GetInventoryPosition();
	StartPosition_ = float4{ Position_.x - 90.f, Position_.y + 10.f, (int)ZOrder::UI };

	float4 Pos = StartPosition_;
	for (int i = 0; i < 24; ++i)
	{
		if (i != 0 && 0 == i % 4)
		{
			Pos.y -= 43.f;
			Pos.x = StartPosition_.x;
		}

		Pos.x += 43.f;
		ItemSlotCount_ += 1;

		InventoryItem* ItemActor = GetLevel()->CreateActor<InventoryItem>();
		ItemActor->GetTransform().SetLocalPosition({ Pos });
		InventoryItemsList_.push_back(ItemActor);
	}

}

void Inventory::Update(float _DeltaTime)
{
	InventoryOnOffCheck();
	CollisionCheck();

	
	//PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	//CurMesoFont_->SetText(std::to_string(PlayerMeso_), "돋움");
	
	if (true == IsInvenOn)
	{
		if (true == IsCategoryOn_1)
		{
			IsCategoryOn_2 = false;
			IsCategoryOn_3 = false;
			IsCategoryOn_4 = false;
			IsCategoryOn_5 = false;
		}
		else if (true == IsCategoryOn_2)
		{
			IsCategoryOn_1 = false;
			IsCategoryOn_3 = false;
			IsCategoryOn_4 = false;
			IsCategoryOn_5 = false;
		}
		else if (true == IsCategoryOn_3)
		{
			IsCategoryOn_1 = false;
			IsCategoryOn_2 = false;
			IsCategoryOn_4 = false;
			IsCategoryOn_5 = false;
		}
		else if (true == IsCategoryOn_4)
		{
			IsCategoryOn_1 = false;
			IsCategoryOn_2 = false;
			IsCategoryOn_3 = false;
			IsCategoryOn_5 = false;
		}
		else if (true == IsCategoryOn_5)
		{
			IsCategoryOn_1 = false;
			IsCategoryOn_2 = false;
			IsCategoryOn_3 = false;
			IsCategoryOn_4 = false;
		}
	}


}   

void Inventory::CollisionCheck()
{ 
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (true == CategoryCollision_1->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			Category_1->SetTexture("Bt_Inven0-1.png");
			IsCategoryOn_1 = true;

			if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Bt_Inven1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Bt_Inven2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Bt_Inven3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Bt_Inven4-0.png");
				IsCategoryOn_5 = false;
			}

		}
		else if (true == CategoryCollision_2->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			Category_2->SetTexture("Bt_Inven1-1.png");
			IsCategoryOn_2 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Bt_Inven0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Bt_Inven2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Bt_Inven3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Bt_Inven4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_3->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			Category_3->SetTexture("Bt_Inven2-1.png");
			IsCategoryOn_3 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Bt_Inven0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Bt_Inven1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Bt_Inven3-0.png");
				IsCategoryOn_4 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Bt_Inven4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_4->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			Category_4->SetTexture("Bt_Inven3-1.png");
			IsCategoryOn_4 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Bt_Inven0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Bt_Inven1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Bt_Inven2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_5)
			{
				Category_5->SetTexture("Bt_Inven4-0.png");
				IsCategoryOn_5 = false;
			}
		}
		else if (true == CategoryCollision_5->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			Category_5->SetTexture("Bt_Inven4-1.png");
			IsCategoryOn_5 = true;

			if (true == IsCategoryOn_1)
			{
				Category_1->SetTexture("Bt_Inven0-0.png");
				IsCategoryOn_1 = false;
			}
			else if (true == IsCategoryOn_2)
			{
				Category_2->SetTexture("Bt_Inven1-0.png");
				IsCategoryOn_2 = false;
			}
			else if (true == IsCategoryOn_3)
			{
				Category_3->SetTexture("Bt_Inven2-0.png");
				IsCategoryOn_3 = false;
			}
			else if (true == IsCategoryOn_4)
			{
				Category_4->SetTexture("Bt_Inven3-0.png");
				IsCategoryOn_4 = false;
			}
		}

	}
	
}

void Inventory::InventoryOnOffCheck()
{
	if (true == GameEngineInput::GetInst()->IsDown("Inventory"))
	{
		if (false == IsInvenOn)
		{
			GameEngineSound::SoundPlayOneShot("MenuDown.mp3");
			IsInvenOn = true;
			Inventory_->On();

			Category_1->On();
			Category_2->On();
			Category_3->On();
			Category_4->On();
			Category_5->On();

			CategoryCollision_1->On();
			CategoryCollision_2->On();
			CategoryCollision_3->On();
			CategoryCollision_4->On();
			CategoryCollision_5->On();
			HeaderCollision_->On();

			CurMesoFont_->On();

			for (size_t i = 0; i < InventoryItemsList_.size(); i++)
			{
				// 빈 칸은 건너뛴다
				if (ItemType::MAX == InventoryItemsList_[i]->GetItemType())
				{
					continue;
				}

				InventoryItemsList_[i]->GetRenderer()->On();
				InventoryItemsList_[i]->GetFontRenderer()->On();

			}
	
		}
		else
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			IsInvenOn = false;
			Inventory_->Off();

			Category_1->Off();
			Category_2->Off();
			Category_3->Off();
			Category_4->Off();
			Category_5->Off();

			CategoryCollision_1->Off();
			CategoryCollision_2->Off();
			CategoryCollision_3->Off();
			CategoryCollision_4->Off();
			CategoryCollision_5->Off();
			HeaderCollision_->Off();

			CurMesoFont_->Off();

			for (size_t i = 0; i < InventoryItemsList_.size(); i++)
			{
				if (ItemType::MAX ==InventoryItemsList_[i]->GetItemType())
				{
					continue;
				}

				InventoryItemsList_[i]->GetRenderer()->Off();
				InventoryItemsList_[i]->GetFontRenderer()->Off();
			}
		}
	}
}

void Inventory::PushItem(Item* _Item)
{
	for (size_t i = 0; i < InventoryItemsList_.size(); i++)
	{
		// 같은 아이템이 있다 -> 개수 증가
		if (_Item->GetItemType() == InventoryItemsList_[i]->GetItemType())
		{
			InventoryItemsList_[i]->SetCount(InventoryItemsList_[i]->GetCount() + 1);
			InventoryItemsList_[i]->GetFontRenderer()->SetScreenPostion({
			  InventoryItemsList_[i]->GetTransform().GetLocalPosition().x + 727.f
			, -InventoryItemsList_[i]->GetTransform().GetLocalPosition().y + 440.f});
			float4 aa = InventoryItemsList_[i]->GetFontRenderer()->GetScreenPostion();
			InventoryItemsList_[i]->ItemCountFontUpdate();

			break;
		}
		// 아이템이 있는 칸이다 -> 다음 칸으로 넘어간다
		if (ItemType::MAX != InventoryItemsList_[i]->GetItemType())
		{
			continue;
		}

		InventoryItemsList_[i]->SetItemType(_Item->GetItemType());	// 칸에 아이템을 채워넣고 -> for문 멈춘다
		InventoryItemsList_[i]->SetCount(InventoryItemsList_[i]->GetCount() + 1);	// 개수는 1개
		InventoryItemsList_[i]->GetFontRenderer()->SetScreenPostion({
			  InventoryItemsList_[i]->GetTransform().GetLocalPosition().x + 727.f
			, -InventoryItemsList_[i]->GetTransform().GetLocalPosition().y + 440.f });
		InventoryItemsList_[i]->ItemCountFontUpdate();

		if (false == IsInvenOn)
		{
			InventoryItemsList_[i]->GetRenderer()->Off();
			InventoryItemsList_[i]->GetFontRenderer()->Off();
		}
		break;
	}
}


