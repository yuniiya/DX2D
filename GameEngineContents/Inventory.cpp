#include "PreCompile.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "Item.h"

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
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	//MainInventory_ = this;

	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

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

	CategoryCollision_1 = CreateComponent<GameEngineCollision>();
	CategoryCollision_1->GetTransform().SetLocalScale({ 17.f, 17.f });
	CategoryCollision_1->ChangeOrder(GAMEOBJGROUP::UI);
	CategoryCollision_1->GetTransform().SetLocalPosition({3008.f, -750.f});

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
	//	ItemActor->SetItemType(ItemType::ITEM_WHITERABBIT);
		InventoryItemsList_.push_back(ItemActor);
		//ItemActor->Off();
	}

}

void Inventory::Update(float _DeltaTime)
{
	InventoryOnOffCheck();
	CollisionCheck();
	
	if (true == IsInvenOn)
	{
		//GetInventoryPosition();
		//StartPosition_ = float4{ Position_.x - 90.f, Position_.y + 10.f};

		//if (false == ItemsList_.empty())
		//{
		//	/*	std::vector<Item*>::iterator StartIter = ItemsList_.begin();

		//		for (StartIter; StartIter != ItemsList_.end(); ++StartIter)
		//		{
		//			int a = 0;
		//		}*/

		//	for (size_t i = 0; i < ItemsList_.size(); i++)
		//	{
		//		InventoryItem* ItemActor = GetLevel()->CreateActor<InventoryItem>();
		//		ItemActor->SetItemType(ItemsList_[i]->GetItemType());
		//		ItemActor->GetTransform().SetLocalPosition({ StartPosition_ });
		//	}
		//}

		//if (ItemSlotCount_ < 24)	// 네 칸
		//{
		//	float4 Pos = StartPosition_;

		//	for (int i = 0; i < 24; ++i)
		//	{
		//		if (i != 0 && 0 == i % 4)
		//		{
		//			Pos.y -= 43.f;
		//			Pos.x = StartPosition_.x;
		//		}

		//		Pos.x += 43.f;
		//		ItemSlotCount_ += 1;

		//		InventoryItem* ItemActor = GetLevel()->CreateActor<InventoryItem>();
		//		ItemActor->SetItemType(ItemType::ITEM_BROWNRABBIT);
		//		ItemActor->GetTransform().SetLocalPosition({ Pos });
		//	}
		//}


		//Item_1->GetTransform().SetLocalPosition({ StartPosition_.x, StartPosition_.y });
		//Item_2->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f, StartPosition_.y });
		//Item_3->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f * 2.f, StartPosition_.y });
		//Item_4->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f * 3.f, StartPosition_.y });
		//Item_5->GetTransform().SetLocalPosition({ StartPosition_.x, StartPosition_.y - 44.f});
	}


}   

void Inventory::CollisionCheck()
{ 
	if (true == CategoryCollision_1->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			Category_1->SetTexture("Bt_Inven0-1.png");
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

			//CategoryCollision_1->On();
			//CategoryCollision_2->On();
			//CategoryCollision_3->On();
			//CategoryCollision_4->On();
			//CategoryCollision_5->On();
	
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

			//CategoryCollision_1->Off();
			//CategoryCollision_2->Off();
			//CategoryCollision_3->Off();
			//CategoryCollision_4->Off();
			//CategoryCollision_5->Off();
		}
	}
}

void Inventory::PushItem(Item* _Item)
{
	for (size_t i = 0; i < InventoryItemsList_.size(); i++)
	{
		// 아이템이 있는 칸이다 -> 다음 칸으로 넘어간다
		if (ItemType::MAX != InventoryItemsList_[i]->GetItemType())
		{
			continue;
		}

		InventoryItemsList_[i]->SetItemType(_Item->GetItemType());	// 칸에 아이템을 채워넣고 -> for문 멈춘다
		break;
	}
}


