#include "PreCompile.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "Item.h"
#include "GameEngineCore/GameEngineFontRenderer.h"
#include "Mouse.h"
#include "MouseSlot.h"
#include "ContentsFont.h"

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
	, Collision_(nullptr)
	, IsCategoryOn_1(false)
	, IsCategoryOn_2(false)
	, IsCategoryOn_3(true)
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
//	Inventory_->SetRenderingOrder((int)GAMEOBJGROUP::UI);
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

	/*CurMesoFont_ = CreateComponent<GameEngineFontRenderer>();
	CurMesoFont_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	CurMesoFont_->SetSize(13.5f);
	CurMesoFont_->SetScreenPostion({
		  -(Inventory_->GetTransform().GetLocalPosition().x + 30.f)
		, Inventory_->GetTransform().GetLocalPosition().y + 25.f});
	CurMesoFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	CurMesoFont_->Off();*/

	CurMesoFont_ = GetLevel()->CreateActor<ContentsFont>(GAMEOBJGROUP::FONT);
	CurMesoFont_->GetNoramlFontRenderer()->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
	CurMesoFont_->GetNoramlFontRenderer()->SetText(std::to_string(PlayerMeso_));
	CurMesoFont_->SetComma();
	CurMesoFont_->GetNoramlFontRenderer()->SetScreenPostion({
		  -(Inventory_->GetTransform().GetLocalPosition().x + 60.f)
		, Inventory_->GetTransform().GetLocalPosition().y + 25.f });
	CurMesoFont_->SetTextSize(13.5f);
	CurMesoFont_->On();
	CurMesoFont_->GetNoramlFontRenderer()->Off();


	// Collision //
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({ Inventory_->GetTransform().GetLocalScale()});
	Collision_->GetTransform().SetLocalPosition({
		Inventory_->GetTransform().GetLocalPosition().x + Inventory_->GetTransform().GetLocalScale().x / 2.f
		, Inventory_->GetTransform().GetLocalPosition().y - Inventory_->GetTransform().GetLocalScale().y / 2.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::INVENTORY);
	Collision_->Off();

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

	GetInventoryPosition();
	StartPosition_ = float4{ Position_.x - 90.f, Position_.y + 10.f, (int)ZOrder::UI };
	
	// º“∫Ò√¢
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
		InventoryItemsList_Potion.push_back(ItemActor);
	}

	// ±‚≈∏√¢
	Pos = StartPosition_;
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
		InventoryItemsList_Etc.push_back(ItemActor);
	}

	// None
	Pos = StartPosition_;
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
		InventoryItemsList_None.push_back(ItemActor);
	}

}

void Inventory::Update(float _DeltaTime)
{
	InventoryOnOffCheck();
	CollisionCheck();
	CategoryOnCheck();

	//CurMesoFont_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void Inventory::LevelStartEvent()
{
	CurMesoFont_->GetNoramlFontRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
}

void Inventory::LevelEndEvent()
{
	//InventoryItemsList_Etc;
}

void Inventory::CollisionCheck()
{ 
	if (nullptr == Mouse::MainMouse_)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (true == Mouse::MainMouse_->GetMouseSlot()->IsHold_)
		{
			return;
		}

		//if (true == HeaderCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		//{
		//	GetTransform().SetLocalPosition(dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetTransform().GetLocalPosition());
		//}

		if (true == CategoryCollision_1->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
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
	
	InventoryItemCollisionCheck();
}

void Inventory::InventoryItemCollisionCheck()
{
	// ============== ∏∂øÏΩ∫ ≈¨∏Ø ==============// 
	// º“∫Ò√¢
	if (true == IsCategoryOn_2)
	{
		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			if (true == InventoryItemsList_Potion[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
			{
				InventoryItemsList_Potion[i]->CollisionCheck();
				InventoryItemsList_Potion[i]->SetSlotIndex((int)i);

				break;
			}
		}
	}
	// ±‚≈∏√¢
	if (true == IsCategoryOn_3)
	{
		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			if (true == InventoryItemsList_Etc[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
			{
				InventoryItemsList_Etc[i]->CollisionCheck();
				InventoryItemsList_Etc[i]->SetSlotIndex((int)i);

				break;
			}

		}
	}
}

void Inventory::InventoryOnOffCheck()
{
	if ("LOGIN" == GetLevel()->GetNameCopy()
		|| "SELECT" == GetLevel()->GetNameCopy()
		|| "TITLE" == GetLevel()->GetNameCopy())
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Inventory"))
	{
		if (false == IsInvenOn)
		{
			GameEngineSound::SoundPlayOneShot("MenuDown.mp3");
			IsInvenOn = true;
			Inventory_->On();
			Collision_->On();
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

			CurMesoFont_->GetNoramlFontRenderer()->On();
		//	CurMesoFont_->SetComma();

			// º“∫Ò√¢¿Ã ƒ—¡≥¿ª ∂ß -> º“∫Ò√¢∏∏ On«œ∞Ì ¥Ÿ∏•∞« ¥Ÿ Off
			if (true == IsCategoryOn_2)
			{
				for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Potion[i]->GetRenderer()->On();
					InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->On();
					InventoryItemsList_Potion[i]->GetCollision()->On();
				}

				for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Etc[i]->GetRenderer()->Off();
					InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Etc[i]->GetCollision()->Off();
				}

				for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_None[i]->GetRenderer()->Off();
					InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_None[i]->GetCollision()->Off();
				}
			}
			else if (true == IsCategoryOn_3)
			{
				for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Etc[i]->GetRenderer()->On();
					InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->On();
					InventoryItemsList_Etc[i]->GetCollision()->On();
				}

				for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Potion[i]->GetRenderer()->Off();
					InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Potion[i]->GetCollision()->Off();
				}

				for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_None[i]->GetRenderer()->Off();
					InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_None[i]->GetCollision()->Off();
				}

			}
			else
			{
				for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_None[i]->GetRenderer()->On();
					InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->On();
					InventoryItemsList_None[i]->GetCollision()->On();
				}

				for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Etc[i]->GetRenderer()->Off();
					InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Etc[i]->GetCollision()->Off();
				}

				for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
				{
					// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
					if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Potion[i]->GetRenderer()->Off();
					InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Potion[i]->GetCollision()->Off();
				}
			}
		

		
		}
		else
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			IsInvenOn = false;
			Inventory_->Off();
			Collision_->Off();
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

			CurMesoFont_->GetNoramlFontRenderer()->Off();

			if (true == IsCategoryOn_2)
			{
				for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
				{
					if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Potion[i]->GetRenderer()->Off();
					InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Potion[i]->GetCollision()->Off();
				}
			}
			else if (true == IsCategoryOn_3)
			{
				for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
				{
					if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_Etc[i]->GetRenderer()->Off();
					InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Etc[i]->GetCollision()->Off();
				}
			}
			else
			{
				for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
				{
					if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
					{
						continue;
					}

					InventoryItemsList_None[i]->GetRenderer()->Off();
					InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_None[i]->GetCollision()->Off();
				}
			}
		
		}
	}
}

void Inventory::CategoryOnCheck()
{
	// ¿Œ∫•≈‰∏Æ∞° ƒ—¡Æ ¿÷¥¬ ªÛ≈¬ø°º≠∏∏ √º≈©
	if (false == IsInvenOn)
	{
		return;
	}

	if (true == IsCategoryOn_1)
	{
		Category_1->SetTexture("Bt_Inven0-1.png");
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;

		for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_None[i]->GetRenderer()->On();
			InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->On();
			InventoryItemsList_None[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->GetRenderer()->Off();
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Potion[i]->GetCollision()->Off();
		}
		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->GetRenderer()->Off();
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Etc[i]->GetCollision()->Off();
		}

	}
	else if (true == IsCategoryOn_2)
	{
		Category_2->SetTexture("Bt_Inven1-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;

		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->GetRenderer()->On();
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->On();
			InventoryItemsList_Potion[i]->GetCollision()->On();
		}
		for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_None[i]->GetRenderer()->Off();
			InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_None[i]->GetCollision()->Off();
		}

		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->GetRenderer()->Off();
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Etc[i]->GetCollision()->Off();
		}
	}
	else if (true == IsCategoryOn_3)
	{
		Category_3->SetTexture("Bt_Inven2-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_4 = false;
		IsCategoryOn_5 = false;

		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->GetRenderer()->On();
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->On();
			InventoryItemsList_Etc[i]->GetCollision()->On();
		}
		for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_None[i]->GetRenderer()->Off();
			InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_None[i]->GetCollision()->Off();
		}

		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->GetRenderer()->Off();
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Potion[i]->GetCollision()->Off();
		}
	}
	else if (true == IsCategoryOn_4)
	{
		Category_4->SetTexture("Bt_Inven3-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_5 = false;

		for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_None[i]->GetRenderer()->On();
			InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->On();
			InventoryItemsList_None[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->GetRenderer()->Off();
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Potion[i]->GetCollision()->Off();
		}
		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->GetRenderer()->Off();
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Etc[i]->GetCollision()->Off();
		}
	}
	else if (true == IsCategoryOn_5)
	{
		Category_5->SetTexture("Bt_Inven4-1.png");
		IsCategoryOn_1 = false;
		IsCategoryOn_2 = false;
		IsCategoryOn_3 = false;
		IsCategoryOn_4 = false;

		for (size_t i = 0; i < InventoryItemsList_None.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_None[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_None[i]->GetRenderer()->On();
			InventoryItemsList_None[i]->GetContensFont()->GetNoramlFontRenderer()->On();
			InventoryItemsList_None[i]->GetCollision()->On();
		}

		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->GetRenderer()->Off();
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Potion[i]->GetCollision()->Off();
		}
		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∫Û ƒ≠¿∫ ∞«≥ ∂⁄¥Ÿ
			if (ItemType::MAX == InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->GetRenderer()->Off();
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
			InventoryItemsList_Etc[i]->GetCollision()->Off();
		}
	}
}

void Inventory::PushItem(Item* _Item)
{
	// 1) æ∆¿Ã≈€¿Ã º“∫Ò ≈∏¿‘¿Ã∂Û∏È
	if (InventorySlotType::SLOT_POTION == _Item->GetSlotType())
	{
		for (size_t i = 0; i < InventoryItemsList_Potion.size(); i++)
		{
			// ∞∞¿∫ æ∆¿Ã≈€¿Ã ¿÷¥Ÿ -> ∞≥ºˆ ¡ı∞°
			if (_Item->GetItemType() == InventoryItemsList_Potion[i]->GetItemType())
			{
				InventoryItemsList_Potion[i]->SetCount(InventoryItemsList_Potion[i]->GetCount() + 1);
				InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->SetScreenPostion({
				  InventoryItemsList_Potion[i]->GetTransform().GetLocalPosition().x + 700.f
				, -InventoryItemsList_Potion[i]->GetTransform().GetLocalPosition().y + 440.f });
				//InventoryItemsList_Potion[i]->ItemCountFontUpdate();

				if (false == IsInvenOn)
				{
					InventoryItemsList_Potion[i]->GetRenderer()->Off();
					InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Potion[i]->GetCollision()->Off();

					break;
				}

				break;
			}
			// æ∆¿Ã≈€¿Ã ¿÷¥¬ ƒ≠¿Ã¥Ÿ -> ¥Ÿ¿Ω ƒ≠¿∏∑Œ ≥—æÓ∞£¥Ÿ
			if (ItemType::MAX != InventoryItemsList_Potion[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Potion[i]->SetItemType(_Item->GetItemType());	// ƒ≠ø° æ∆¿Ã≈€¿ª √§øˆ≥÷∞Ì -> forπÆ ∏ÿ√·¥Ÿ
			InventoryItemsList_Potion[i]->SetCount(InventoryItemsList_Potion[i]->GetCount() + 1);	// ∞≥ºˆ¥¬ 1∞≥
			InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->SetScreenPostion({
				  InventoryItemsList_Potion[i]->GetTransform().GetLocalPosition().x + 700.f
				, -InventoryItemsList_Potion[i]->GetTransform().GetLocalPosition().y + 440.f });
			//InventoryItemsList_Potion[i]->ItemCountFontUpdate();

			if (false == IsInvenOn)
			{
				InventoryItemsList_Potion[i]->GetRenderer()->Off();
				InventoryItemsList_Potion[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
				InventoryItemsList_Potion[i]->GetCollision()->Off();
			}
			break;
		}
	}
	else if (InventorySlotType::SLOT_ETC == _Item->GetSlotType())	// 2) æ∆¿Ã≈€¿Ã ±‚≈∏ ≈∏¿‘¿Ã∂Û∏È
	{
		for (size_t i = 0; i < InventoryItemsList_Etc.size(); i++)
		{
			// ∞∞¿∫ æ∆¿Ã≈€¿Ã ¿÷¥Ÿ -> ∞≥ºˆ ¡ı∞°
			if (_Item->GetItemType() == InventoryItemsList_Etc[i]->GetItemType())
			{
				InventoryItemsList_Etc[i]->SetCount(InventoryItemsList_Etc[i]->GetCount() + 1);
				InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->SetScreenPostion({
				  InventoryItemsList_Etc[i]->GetTransform().GetLocalPosition().x + 700.f
				, -InventoryItemsList_Etc[i]->GetTransform().GetLocalPosition().y + 440.f });
			//	InventoryItemsList_Etc[i]->ItemCountFontUpdate();

				if (false == IsInvenOn)
				{
					InventoryItemsList_Etc[i]->GetRenderer()->Off();
					InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
					InventoryItemsList_Etc[i]->GetCollision()->Off();

					break;
				}
				break;
			}
			// æ∆¿Ã≈€¿Ã ¿÷¥¬ ƒ≠¿Ã¥Ÿ -> ¥Ÿ¿Ω ƒ≠¿∏∑Œ ≥—æÓ∞£¥Ÿ
			if (ItemType::MAX != InventoryItemsList_Etc[i]->GetItemType())
			{
				continue;
			}

			InventoryItemsList_Etc[i]->SetItemType(_Item->GetItemType());	// ƒ≠ø° æ∆¿Ã≈€¿ª √§øˆ≥÷∞Ì -> forπÆ ∏ÿ√·¥Ÿ
			InventoryItemsList_Etc[i]->SetCount(InventoryItemsList_Etc[i]->GetCount() + 1);	// ∞≥ºˆ¥¬ 1∞≥
			InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->SetScreenPostion({
				  InventoryItemsList_Etc[i]->GetTransform().GetLocalPosition().x + 700.f
				, -InventoryItemsList_Etc[i]->GetTransform().GetLocalPosition().y + 440.f });
			//InventoryItemsList_Etc[i]->ItemCountFontUpdate();

			if (false == IsInvenOn)
			{
				InventoryItemsList_Etc[i]->GetRenderer()->Off();
				InventoryItemsList_Etc[i]->GetContensFont()->GetNoramlFontRenderer()->Off();
				InventoryItemsList_Etc[i]->GetCollision()->Off();
			}
			break;
		}
	}
}


