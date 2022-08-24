#include "PreCompile.h"
#include "Inventory.h"

Inventory::Inventory() 
	: Inventory_(nullptr)
	, IsInvenOn(false)
	, Item_1(nullptr)
	, Item_2(nullptr)
	, Item_3(nullptr)
	, Item_4(nullptr)
	, Item_5(nullptr)
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
	Inventory_->Off();


//	GameEngineTexture::Find("Item2.png");


	Item_1 = CreateComponent<GameEngineTextureRenderer>();
	Item_1->SetTexture("Item2.png", 0);
	Item_1->SetPivot(PIVOTMODE::LEFTTOP);
	Item_1->GetTransform().SetLocalScale({ 128.f, 128.f });
	Item_1->Off();

	Item_2 = CreateComponent<GameEngineTextureRenderer>();
	Item_2->SetTexture("Item2.png", 1);
	Item_2->SetPivot(PIVOTMODE::LEFTTOP);
	Item_2->GetTransform().SetLocalScale({ 128.f, 128.f });
	Item_2->Off();

	Item_3 = CreateComponent<GameEngineTextureRenderer>();
	Item_3->SetTexture("Item2.png", 2);
	Item_3->SetPivot(PIVOTMODE::LEFTTOP);
	Item_3->GetTransform().SetLocalScale({ 128.f, 128.f });;
	Item_3->Off();

	Item_4 = CreateComponent<GameEngineTextureRenderer>();
	Item_4->SetTexture("Item2.png", 3);
	Item_4->SetPivot(PIVOTMODE::LEFTTOP);
	Item_4->GetTransform().SetLocalScale({ 128.f, 128.f });
	Item_4->Off();

	Item_5 = CreateComponent<GameEngineTextureRenderer>();
	Item_5->SetTexture("Item2.png", 4);
	Item_5->SetPivot(PIVOTMODE::LEFTTOP);
	Item_5->GetTransform().SetLocalScale({ 128.f, 128.f });
	Item_5->Off();
}

void Inventory::Update(float _DeltaTime)
{
	float4 CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	Inventory_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 400.f, CamPos_.y + 308.f });

	GetInventoryPosition();
	InventoryOnOffCheck();

	if (true == IsInvenOn)
	{
		ItemPosition_ = float4{ Position_.x - 49.f, Position_.y + 13.f };

		Item_1->GetTransform().SetLocalPosition({ ItemPosition_.x, ItemPosition_.y });	
		Item_2->GetTransform().SetLocalPosition({ ItemPosition_.x + 44.f, ItemPosition_.y });
		Item_3->GetTransform().SetLocalPosition({ ItemPosition_.x + 88.f, ItemPosition_.y });
		Item_4->GetTransform().SetLocalPosition({ ItemPosition_.x + 132.f, ItemPosition_.y });
		Item_5->GetTransform().SetLocalPosition({ ItemPosition_.x, ItemPosition_.y - 44.f});

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
		}
	}
}

