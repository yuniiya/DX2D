#include "PreCompile.h"
#include "Inventory.h"
#include "Item.h"

Inventory::Inventory() 
	: Inventory_(nullptr)
	, IsInvenOn(false)
	, Item_1(nullptr)
	, Item_2(nullptr)
	, Item_3(nullptr)
	, Item_4(nullptr)
	, Item_5(nullptr)
	, HeaderCollision_(nullptr)
	, Collision_1(nullptr)
	, Collision_2(nullptr)
	, Collision_3(nullptr)
	, Collision_4(nullptr)
	, Collision_5(nullptr)
	, Collision_6(nullptr)
	, Collision_7(nullptr)
	, Collision_8(nullptr)
	, StartPosition_(0.f)
	, Position_(0.f)
	, Capacity_(24)
	, ItemCount_(0)
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	Inventory_ = CreateComponent<GameEngineTextureRenderer>();
	Inventory_->SetTexture("Inventory.png");
	Inventory_->SetPivot(PIVOTMODE::LEFTTOP);
	Inventory_->ScaleToTexture();
	//Inventory_->Off();


	Item_1 = CreateComponent<GameEngineTextureRenderer>();
	Item_1->SetTexture("Item2.png", 0);
	Item_1->SetPivot(PIVOTMODE::LEFTTOP);
	Item_1->GetTransform().SetLocalScale({ 128.f, 128.f });
	//Item_1->Off();

	Item_2 = CreateComponent<GameEngineTextureRenderer>();
	Item_2->SetTexture("Item2.png", 1);
	Item_2->SetPivot(PIVOTMODE::LEFTTOP);
	Item_2->GetTransform().SetLocalScale({ 128.f, 128.f });
//	Item_2->Off();

	Item_3 = CreateComponent<GameEngineTextureRenderer>();
	Item_3->SetTexture("Item2.png", 2);
	Item_3->SetPivot(PIVOTMODE::LEFTTOP);
	Item_3->GetTransform().SetLocalScale({ 128.f, 128.f });;
//	Item_3->Off();

	Item_4 = CreateComponent<GameEngineTextureRenderer>();
	Item_4->SetTexture("Item2.png", 3);
	Item_4->SetPivot(PIVOTMODE::LEFTTOP);
	Item_4->GetTransform().SetLocalScale({ 128.f, 128.f });
//	Item_4->Off();

	Item_5 = CreateComponent<GameEngineTextureRenderer>();
	Item_5->SetTexture("Item2.png", 4);
	Item_5->SetPivot(PIVOTMODE::LEFTTOP);
	Item_5->GetTransform().SetLocalScale({ 128.f, 128.f });
//	Item_5->Off();


	// Collision //
	Collision_1 = CreateComponent<GameEngineCollision>();
	Collision_1->GetTransform().SetLocalScale({ 38.f, 37.f });
	Collision_1->ChangeOrder(GAMEOBJGROUP::UI);
//	Collision_1->Off();

	Collision_2 = CreateComponent<GameEngineCollision>();
	Collision_2->GetTransform().SetLocalScale({ 38.f, 37.f });
	Collision_2->ChangeOrder(GAMEOBJGROUP::UI);
//	Collision_2->Off();

	Collision_3 = CreateComponent<GameEngineCollision>();
	Collision_3->GetTransform().SetLocalScale({ 38.f, 37.f });
	Collision_3->ChangeOrder(GAMEOBJGROUP::UI);
//	Collision_3->Off();

	Collision_4 = CreateComponent<GameEngineCollision>();
	Collision_4->GetTransform().SetLocalScale({ 38.f, 37.f });
	Collision_4->ChangeOrder(GAMEOBJGROUP::UI);
//	Collision_4->Off();


	IsInvenOn = true;

	//StartPosition_ = float4({ 2751.f, -317.f });	// ½½·Ô ½ÃÀÛ Æ÷Áö¼Ç

	//float4 Pos = StartPosition_;

	//for (int i = 0; i < 24; ++i)
	//{
	//	if (i != 0 && 0 == i % 4)
	//	{
	//		//	Pos.y = Startition_.y - 44.f;
	//		Pos.y -= 44.f;

	//		Pos.x = StartPosition_.x;
	//	}

	//	Pos.x += 44.f;
	//	ItemCount_ += 1;

	//	Item* ItemActor = GetLevel()->CreateActor<Item>();
	//	ItemActor->SetItemType(ItemType::INVENTORY);
	//	ItemActor->MonsterName_ = MONSTERNAME::BrownRabbit;
	//	ItemActor->GetTransform().SetLocalPosition({ Pos });
	//}
}

void Inventory::Update(float _DeltaTime)
{
	float4 CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	Inventory_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 400.f, CamPos_.y + 308.f });

	InventoryOnOffCheck();

	if (true == IsInvenOn)
	{
		GetInventoryPosition();
		//StartPosition_ = float4{ Position_.x - 49.f, Position_.y + 13.f };
		StartPosition_ = float4{ Position_.x - 87.f, Position_.y - 145.f };

		if (ItemCount_ < 24)	// ³× Ä­
		{
			float4 Pos = StartPosition_;

			for (int i = 0; i < 24; ++i)
			{
				if (i != 0 && 0 == i % 4)
				{

					Pos.y -= 43.f;
					Pos.x = StartPosition_.x;
				}

				Pos.x += 43.f;
				ItemCount_ += 1;

				Item* ItemActor = GetLevel()->CreateActor<Item>();
				ItemActor->SetItemType(ItemType::INVENTORY);
				ItemActor->MonsterName_ = MONSTERNAME::BrownRabbit;
				ItemActor->GetTransform().SetLocalPosition({ Pos });
			}
		}

		//Item_1->GetTransform().SetLocalPosition({ StartPosition_.x, StartPosition_.y });
		//Item_2->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f, StartPosition_.y });
		//Item_3->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f * 2.f, StartPosition_.y });
		//Item_4->GetTransform().SetLocalPosition({ StartPosition_.x + 44.f * 3.f, StartPosition_.y });
		//Item_5->GetTransform().SetLocalPosition({ StartPosition_.x, StartPosition_.y - 44.f});

		//Collision_1->GetTransform().SetLocalPosition({ Item_1->GetTransform().GetLocalPosition().x + 80.f, Item_1->GetTransform().GetLocalPosition().y - 80.f });
		//Collision_2->GetTransform().SetLocalPosition({ Item_2->GetTransform().GetLocalPosition().x + 80.f, Item_1->GetTransform().GetLocalPosition().y - 80.f });
		//Collision_3->GetTransform().SetLocalPosition({ Item_3->GetTransform().GetLocalPosition().x + 80.f, Item_1->GetTransform().GetLocalPosition().y - 80.f });
		//Collision_4->GetTransform().SetLocalPosition({ Item_4->GetTransform().GetLocalPosition().x + 80.f, Item_1->GetTransform().GetLocalPosition().y - 80.f });
	}


}

void Inventory::CollisionCheck()
{

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

			Item_1->On();
			Item_2->On();
			Item_3->On();
			Item_4->On();
			Item_5->On();

			Collision_1->On();
			Collision_2->On();
			Collision_3->On();
			Collision_4->On();

		}
		else
		{
			GameEngineSound::SoundPlayOneShot("MenuUp.mp3");
			IsInvenOn = false;
			Inventory_->Off();

			Item_1->Off();
			Item_2->Off();
			Item_3->Off();
			Item_4->Off();
			Item_5->Off();

			Collision_1->Off();
			Collision_2->Off();
			Collision_3->Off();
			Collision_4->Off();
		}
	}
}

