#include "PreCompile.h"
#include "Inventory.h"

Inventory::Inventory() 
	: Inventory_(nullptr)
	, IsInvenOn(false)
	, Item_1(nullptr)
	, Item_2(nullptr)
	, Item_3(nullptr)
	, Item_4(nullptr)
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
	Item_1->SetTexture("Item2.png", 1);
	Item_1->SetPivot(PIVOTMODE::LEFTTOP);
	Item_1->ScaleToTexture();

	Item_1->Off();

	Item_2 = CreateComponent<GameEngineTextureRenderer>();
	Item_2->SetTexture("Item2_Rabbit1.png");
	Item_2->SetPivot(PIVOTMODE::LEFTTOP);
	Item_2->ScaleToTexture();
	Item_2->Off();

	Item_3 = CreateComponent<GameEngineTextureRenderer>();
	Item_3->SetTexture("Item2_Rabbit2.png");
	Item_3->SetPivot(PIVOTMODE::LEFTTOP);
	Item_3->ScaleToTexture();
	Item_3->Off();

	Item_4 = CreateComponent<GameEngineTextureRenderer>();
	Item_4->SetTexture("Item_Sand2.png");
	Item_4->SetPivot(PIVOTMODE::LEFTTOP);
	Item_4->ScaleToTexture();
	Item_4->Off();
}

void Inventory::Update(float _DeltaTime)
{
	float4 CamPos_ = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	Inventory_->GetTransform().SetLocalPosition(float4{ CamPos_.x - 400.f, CamPos_.y + 308.f });

	GetInventoryPosition();
	InventoryOnOffCheck();

	if (true == IsInvenOn)
	{
		Item_1->GetTransform().SetLocalPosition({ Position_.x + 15.f, Position_.y - 50.f });	//	15 60 100
		//Item_2->GetTransform().SetLocalPosition({ Position_.x + 60.f, Position_.y - 55.f });
		//Item_3->GetTransform().SetLocalPosition({ Position_.x + 100.f, Position_.y - 55.f });
		//Item_4->GetTransform().SetLocalPosition({ Position_.x + 180.f, Position_.y - 55.f });
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
		}
	}
}

